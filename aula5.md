STM32

1. como vamos para a função main?
quando um processador liga ele reseta (interrupção de reset) Reset_Handler (lidado dentro do arquivo startup_stm32f103c8tx.s)

no boot todas as variaveis globais não iniciadas ou iguais a 0 são alocadas na BSS



2. como alocar memória?
é alocado com vetores pois malloc não é feito para acesso concorrente
alocar 32bits: uint32_t vetor[32]


3. como copiar uma função da flash para RAM?
o nome de uma função é um ponteiro (ponteiro de função)
o nome de uma variavel é um ponteiro (ponteiro de variavel)

sizeof(função) retorna 4 bytes por que um ponteiro em uma computador de 32bits tem 32bits, para saber quanto uma função tem de tamanho realmete é preciso compilar o codigo e olhar o .map

void *memcpy(void *dest, const void *src, size_t count);

uitnt 32_t vetor[28/4] #28 seria o tamanho da função
uint16_t mult(uint a, uint b)
memcpy(vetor, mult, 28)

como chamar a função armazenada?

//tipo de ponteiro de uma função
typedef int (*fnc_t)(int, int);

fnc_t mult_ram = (fnc_t)vetor;
int i = mult_ram(4, 7);

em processadores ARM precisa fazer uma pequena modificação no exempo acima

isso causa um problema pois mudar a função ira mudar o tamanho e compilar com otimização ira tbm mudar o tamanho, então existe uma solução:
olhar a seção MEMORY e SECTIONS no arquivo de linker, mudar na parte SECTION a memória que é para ir. seção .data 
.data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */

  } >RAM AT> FLASH
  diz que esta na RAM mas inicia na FLASH

SRAM2 e CCMRAM precisão ser declarados na MEMORY para poderem ser usadas na SECTIONS

depois de mudar o linker precisa mudar no startup_stm32f103c8tx.s para poder iniciar os valores 

no F4 jogar a pilhar para CCMRAM acelera bastante o processador

Obs: preciso estudar o linker