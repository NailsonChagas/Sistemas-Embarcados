## 1. Inicialização e Boot Process

**Reset Handler → Main Function:**
```c
// No arquivo startup_stm32f103c8tx.s
Reset_Handler:
    // Inicializa .data (variáveis inicializadas)
    // Limpa .bss (variáveis não inicializadas = 0)
    // Chama SystemInit()
    BL      SystemInit
    // Chama main()
    BL      main
    BX      LR
```

**Seções de memória:**
- **.data**: Variáveis globais inicializadas
- **.bss**: Variáveis globais não inicializadas (zeradas)
- **.heap**: Memória dinâmica
- **.stack**: Pilha da aplicação

## 2. Alocação de Memória

**Alocação estática (recomendada para sistemas embarcados):**
```c
// Alocação de arrays estáticos
uint32_t vetor[32];          // 32 elementos de 32 bits
uint8_t buffer[1024];        // 1KB buffer
float dados_sensor[100];     // Array de floats

// Alocação em memórias específicas
__attribute__((section(".ccmram"))) uint32_t fast_data[64];
__attribute__((section(".sram2"))) uint8_t backup_data[256];
```

## 3. Copiar Função da Flash para RAM

**Método 1: Manual com memcpy**
```c
#include <string.h>

// Função original
uint16_t mult(uint16_t a, uint16_t b) {
    return a * b;
}

// Buffer na RAM
__attribute__((aligned(4))) uint32_t ram_function_buffer[32];

// Copiar função para RAM
void copy_function_to_ram() {
    // Tamanho estimado da função (ajustar conforme necessidade)
    size_t function_size = 28;
    memcpy(ram_function_buffer, (void*)mult, function_size);
}

// Chamar função na RAM
typedef uint16_t (*mult_func_t)(uint16_t, uint16_t);

void use_ram_function() {
    mult_func_t mult_ram = (mult_func_t)ram_function_buffer;
    uint16_t result = mult_ram(4, 7);
}
```

**Método 2: Usando Linker Script (Recomendado)**

**No linker script (.ld):**
```ld
MEMORY
{
    FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 64K
    RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 20K
    CCMRAM (xrw)    : ORIGIN = 0x10000000, LENGTH = 8K
    SRAM2 (xrw)     : ORIGIN = 0x2001C000, LENGTH = 4K
}

SECTIONS
{
    .text :
    {
        *(.text*)
    } > FLASH
    
    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        *(.RamFunc)        /* Funções para RAM */
        *(.RamFunc*)
        . = ALIGN(4);
        _edata = .;
    } > RAM AT > FLASH
    
    .ccmram :
    {
        . = ALIGN(4);
        _sccmram = .;
        *(.ccmram)
        *(.ccmram*)
        . = ALIGN(4);
        _eccmram = .;
    } > CCMRAM AT > FLASH
}
```

**No código C:**
```c
// Função que será colocada na RAM
__attribute__((section(".RamFunc"))) 
uint16_t fast_mult(uint16_t a, uint16_t b) {
    return a * b;
}

// Função que será colocada na CCMRAM
__attribute__((section(".ccmram"))) 
void critical_function(void) {
    // Código crítico de tempo
}
```

## 4. Inicialização no Startup

**No startup_stm32*.s:**
```assembly
; Copiar .data da FLASH para RAM
ldr r0, =_sdata
ldr r1, =_edata
ldr r2, =_sidata
movs r3, #0
b LoopCopyDataInit

CopyDataInit:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4

LoopCopyDataInit:
    adds r4, r0, r3
    cmp r4, r1
    bcc CopyDataInit

; Copiar .ccmram da FLASH para CCMRAM
ldr r0, =_sccmram
ldr r1, =_eccmram
ldr r2, =_siccmram
movs r3, #0
b LoopCopyCcmramInit

CopyCcmramInit:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4

LoopCopyCcmramInit:
    adds r4, r0, r3
    cmp r4, r1
    bcc CopyCcmramInit
```

## 5. Configuração de Stack/Heap em Memórias Especiais

**No linker script:**
```ld
/* Pilha na CCMRAM para melhor performance */
_estack = ORIGIN(CCMRAM) + LENGTH(CCMRAM);

/* Heap na SRAM2 */
_heap_end = ORIGIN(SRAM2) + LENGTH(SRAM2);
```

## 6. Verificação do Tamanho de Funções

**Usando map file:**
- Compilar com `-Wl,-Map=output.map`
- Procurar pelo nome da função no arquivo .map
- Verificar o tamanho em bytes

**Exemplo de saída no .map:**
```
mult            0x08000234    0x1c  Code  RO            mult.o
```
