#include <stdio.h>

// gcc ./main.c -o ./main.bin
// gcc -E main.c -o main_preprocessed.c

// --- Seção 1: Definição do Protothread e Macros de Controle ---

// A estrutura que armazena o estado do protothread.
// 'lc' (local continuation) guarda o ponto (linha de código) onde a tarefa parou.
typedef struct
{
    unsigned int lc; 
} Protothread;

// Inicializa um protothread, configurando seu estado para 0.
// É obrigatório chamar esta macro antes de executar a tarefa.
#define PT_INIT(pt) \
    (pt)->lc = 0

// Inicia a seção de código do protothread.
// Usa um 'switch' para pular para o ponto de continuação salvo.
#define PT_BEGIN(pt) \
    switch((pt)->lc) { case 0:

// "Pausa" a execução até que a condição 'c' seja verdadeira.
// Salva a linha atual ('__LINE__') como o novo estado e retorna.
// Na próxima chamada, o 'case __LINE__' faz a execução continuar daqui.
#define PT_WAIT_UNTIL(pt, c)  \
    (pt)->lc = __LINE__; \
    case __LINE__: \
        if(!(c)) return 0

// Encerra a execução do protothread.
// Reseta o estado para 0 para que possa ser reusado.
#define PT_END(pt) \
    } \
    (pt)->lc = 0; \
    return 2

// --- Seção 2: Variáveis Globais (Estado Compartilhado) ---
static Protothread pt1;
static Protothread pt2;
int i = 0; // incrementada pela tarefa1 e monitorada pela tarefa2.

// --- Seção 3: As Tarefas que estaram dentro das Protothreads ---

// Tarefa 1: Espera i ser igual a count e incrementa i.
int tarefa1(Protothread *pt, int count)
{
    PT_BEGIN(pt);

    while(1)
    {
        PT_WAIT_UNTIL(pt, i == count);
        printf("i: %i == count: %i\n", i, count);
        i += 10;
    }

    PT_END(pt);
}

// Tarefa 2: Espera até que a variável global 'i' atinja o valor target.
// mesmo que seja executada apenas uma vez, é feito a checagem a cada iteração do loop do main
int tarefa2(Protothread *pt, int target)
{
    PT_BEGIN(pt);

    PT_WAIT_UNTIL(pt, i == target); // depois de passar a primeira vez ira sempre retornar 0
    printf("TAREFA 2 passou: i == %i\n", i);

    PT_WAIT_UNTIL(pt, i == (target*2)); // nunca será chamado 
    printf("TAREFA 2 passou: i == %i * 2\n", i);
    
    PT_END(pt);
}

// --- Seção 4: O Escalonador Cooperativo (Função `main`) ---

// A função 'main' atua como um escalonador muito simples. Ela inicializa os protothreads
// e os chama repetidamente em um loop. Cada protothread coopera,
// executando um pouco de trabalho ou "pausando" para dar chance à outra tarefa.
int main(void)
{
    int counter = 0;

    PT_INIT(&pt1);
    PT_INIT(&pt2);

    while(counter != 100)
    {
        printf("--- counter: %i ---\n", counter);

        // primeira tarefa chamada na pt1.
        // Ela vai executar e parar quando a condição não for cumprida.
        tarefa1(&pt1, counter);

        // segunda tarefa chamada na pt2.
        // Ela vai executar ou esperar dependendo do valor atual de 'i'.
        tarefa2(&pt2, 30);
        
        counter++;
    }

    return 0;
}