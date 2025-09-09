# Manual: Gerenciamento de Memória no STM32G474RETx
Baseado no exemplo do professor.

## 1. Por que separar a RAM em setores?

A separação da RAM em setores distintos oferece várias vantagens em sistemas embarcados:

### Vantagens:
- **Desempenho**: A CCM RAM (Core Coupled Memory) possui acesso mais rápido pelo núcleo Cortex-M4, ideal para funções críticas e dados frequentemente acessados
- **Consumo de energia**: Diferentes bancos de memória podem ser gerenciados separadamente para eficiência energética
- **Organização**: Separação lógica entre dados de diferentes propósitos (stack, heap, dados críticos)
- **Concorrência**: Acesso simultâneo a diferentes bancos de memória através de barramentos distintos

### Restrições:
- A CCM RAM não é acessível por periféricos DMA
- Cada banco de memória tem tamanho fixo definido pelo hardware
- Requer configuração específica no linker script e código

## 2. Setores de RAM no STM32G474RETx

O STM32G474RETx possui três regiões de memória RAM distintas:

- **RAM Principal**: 80KB em 0x20000000 (acessível por CPU e DMA)
- **SRAM2**: 16KB em 0x20014000 (acessível por CPU e DMA)  
- **CCMRAM**: 32KB em 0x10000000 (acessível apenas pelo núcleo Cortex-M4)

## 3. Alterações no Linker Script e Startup File

### No Linker Script (STM32G474RETX_FLASH.ld):

```ld
MEMORY
{
  RAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 80K
  SRAM2  (xrw)    : ORIGIN = 0x20014000,   LENGTH = 16K
  CCMRAM (xrw)    : ORIGIN = 0x10000000,   LENGTH = 32K
  FLASH   (rx)    : ORIGIN = 0x8000000,   LENGTH = 512K
}

SECTIONS
{
  /* Seção para dados inicializados na CCMRAM */
  .ccm :
  {
    . = ALIGN(4);
    _sccm = .;
    *(.ccm)           /* Seções .ccm */
    *(.ccm*)          /* Seções .ccm* */
    *(.ccmRamFunc)    /* Funções em CCMRAM */
    *(.ccmRamFunc*)   /* Funções em CCMRAM */
    . = ALIGN(4);
    _eccm = .;
  } >CCMRAM AT> FLASH

  /* Seção para dados não inicializados na SRAM2 */
  .sr2bss :
  {
    _ssr2bss = .;
    __sr2bss_start__ = _ssr2bss;
    *(.sr2bss)
    *(.sr2bss*)
    . = ALIGN(4);
    _esr2bss = .;
    __sr2bss_end__ = _esr2bss;
  } >SRAM2
}
```

### No Arquivo de Startup (startup_stm32g474retx.s):

O arquivo de startup (`startup_stm32g474retx.s`) é responsável pela inicialização básica do microcontrolador após um reset. Ele executa em assembly e prepara o ambiente para a execução do código C.

#### Fluxo Principal do Reset Handler

```assembly
Reset_Handler:
  /* 1. Configuração do Stack Pointer */
  ldr   r0, =_estack
  mov   sp, r0          /* Define o ponteiro de stack para o topo da RAM */

  /* 2. Inicialização do Sistema de Clock */
  bl    SystemInit      /* Chama a função de inicialização do clock */

  /* 3. Cópia de dados inicializados para as diferentes memórias RAM */
  /* 4. Limpeza de seções BSS (dados não inicializados) */
  /* 5. Chamada de construtores C++ e entrada no main() */
```

#### Detalhamento das Operações de Memória

##### 3.1 Cópia de Dados para RAM Principal
```assembly
/* Copia dados da Flash para a RAM principal (.data section) */
ldr r0, =_sdata        /* r0 = endereço inicial da RAM principal */
ldr r1, =_edata        /* r1 = endereço final da RAM principal */  
ldr r2, =_sidata       /* r2 = endereço dos dados iniciais na Flash */
movs r3, #0            /* r3 = contador (0) */
b   LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]     /* Carrega dado da Flash (endereço = r2 + r3) */
  str r4, [r0, r3]     /* Armazena na RAM (endereço = r0 + r3) */
  adds r3, r3, #4      /* Incrementa contador em 4 bytes */

LoopCopyDataInit:
  adds r4, r0, r3      /* r4 = endereço atual na RAM */
  cmp r4, r1           /* Compara com endereço final */
  bcc CopyDataInit     /* Se não chegou ao final, continua copiando */
```

##### 3.2 Cópia de Dados para CCMRAM
```assembly
/* Copia dados da Flash para a CCMRAM (.ccm section) */
ldr r0, =_sccm         /* r0 = endereço inicial da CCMRAM */
ldr r1, =_eccm         /* r1 = endereço final da CCMRAM */
ldr r2, =_siccm        /* r2 = endereço dos dados iniciais na Flash */
movs r3, #0            /* r3 = contador (0) */
b   LoopCopyccmInit

CopyccmInit:
  ldr r4, [r2, r3]     /* Carrega dado da Flash */
  str r4, [r0, r3]     /* Armazena na CCMRAM */
  adds r3, r3, #4      /* Incrementa contador */

LoopCopyccmInit:
  adds r4, r0, r3      /* Calcula endereço atual */
  cmp r4, r1           /* Verifica se chegou ao final */
  bcc CopyccmInit      /* Continua se não terminou */
```

##### 4.1 Limpeza da BSS na RAM Principal
```assembly
/* Zera a seção BSS na RAM principal (.bss section) */
ldr r2, =_sbss         /* r2 = início da seção BSS */
ldr r4, =_ebss         /* r4 = fim da seção BSS */
movs r3, #0            /* r3 = valor zero */
b   LoopFillZerobss

FillZerobss:
  str  r3, [r2]        /* Armazena 0 no endereço atual */
  adds r2, r2, #4      /* Avança para próximo endereço */

LoopFillZerobss:
  cmp r2, r4           /* Compara com endereço final */
  bcc FillZerobss      /* Continua se não terminou */
```

##### 4.2 Limpeza da BSS na SRAM2
```assembly
/* Zera a seção BSS na SRAM2 (.sr2bss section) */
ldr r2, =_ssr2bss      /* r2 = início da BSS na SRAM2 */
ldr r4, =_esr2bss      /* r4 = fim da BSS na SRAM2 */
movs r3, #0            /* r3 = valor zero */
b   LoopFillZerobss2

FillZerobss2:
  str  r3, [r2]        /* Armazena 0 */
  adds r2, r2, #4      /* Próximo endereço */

LoopFillZerobss2:
  cmp r2, r4           /* Verifica se terminou */
  bcc FillZerobss2     /* Continua se não */
```

##### 5. Finalização e Chamada do Main
```assembly
/* Chama construtores de objetos C++ (se aplicável) */
bl __libc_init_array

/* Chama a função main() da aplicação C */
bl  main

/* Loop infinito se main() retornar (não deveria acontecer) */
LoopForever:
  b LoopForever
```

#### Por que essa Inicialização é Necessária?

- Dados Inicializados (.data)
	- Variáveis com valores iniciais são armazenadas na Flash
	- Durante o startup, são copiadas para a RAM onde podem ser modificadas
	- Exemplo: `int x = 42;` → valor 42 na Flash, copiado para RAM

- Dados Não Inicializados (.bss)
	- Variáveis sem valor inicial precisam ser zeradas
	- Evita que contenham lixo de memória da execução anterior
	- Exemplo: `int y;` → deve ser 0 no início

- Memórias Especiais (CCMRAM e SRAM2)
	- Requerem tratamento separado por estarem em endereços diferentes
	- A CCMRAM oferece acesso mais rápido pelo núcleo
	- A SRAM2 pode ser usada para dados específicos ou como backup

#### Importância da Ordem das Operações
1. **Stack Pointer primeiro**: Permite uso de funções e interrupções
2. **SystemInit em seguida**: Configura clocks antes de qualquer acesso à memória
3. **Cópia de dados**: Prepara variáveis inicializadas
4. **Limpeza BSS**: Garante variáveis não inicializadas em estado conhecido
5. **Construtores C++**: Prepara objetos globais antes do main()
6. **Chamada main()**: Inicia a aplicação principal

Este processo garante que quando `main()` é chamado, todo o ambiente C está devidamente inicializado e pronto para uso.

## 4. Como Alocar Funções e Variáveis nos Setores

### Variáveis na CCMRAM:

```c
// Variável individual
__attribute__((section(".ccmdata"))) int minha_variavel;

// Array na CCMRAM
__attribute__((section(".ccmdata"))) int vetor[4096];
```

### Funções na CCMRAM:

```c
__attribute__((section(".ccmRamFunc"))) void minha_funcao_rapida(void)
{
    // Código de execução rápida
}
```

### Variáveis na SRAM2:

```c
// Variável na SRAM2
__attribute__((section(".sr2bss"))) int variavel_sram2;

// Array na SRAM2  
__attribute__((section(".sr2bss"))) int dados_sram2[1024];
```

### Funções na RAM Principal:

```c
__attribute__((section(".RamFunc"))) void funcao_em_ram(void)
{
    // Código executado na RAM principal
}
```

## 5. Considerações Importantes

1. **CCMRAM**: Ideal para funções críticas de tempo e dados frequentemente acessados
2. **SRAM1 e SRAM2**: Uso geral para stack, heap e dados convencionais. Acesso DMA
3. **Inicialização**: As seções especiais requerem tratamento específico no startup