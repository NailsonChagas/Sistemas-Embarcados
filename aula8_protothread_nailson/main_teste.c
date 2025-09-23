#include <stdio.h>

// gcc ./main_teste.c -o ./main_teste.bin
// gcc -E main_teste.c -o main_teste_preprocessed.c


// --- Seção 1: Definição do Protothread e Macros de Controle ---

typedef struct
{
    unsigned int lc; 
} Protothread;

#define PT_INIT(pt) \
    (pt)->lc = 0

#define PT_WAIT_UNTIL(pt, c)  \
    (pt)->lc = __LINE__; \
    switch((pt)->lc) { \
    case __LINE__: \
        if(!(c)) return 0; \
    }

#define PT_END(pt) \
    (pt)->lc = 0; \
    return 2

// --- Seção 2: Variáveis Globais ---
static Protothread pt1;
static Protothread pt2;
int i = 0;

// --- Seção 3: Tarefas ---
int tarefa1(Protothread *pt, int count)
{
    while(1)
    {
        PT_WAIT_UNTIL(pt, i == count);
        printf("i: %i == count: %i\n", i, count);
        i += 10;
    }

    PT_END(pt);
}

int tarefa2(Protothread *pt, int target)
{
    PT_WAIT_UNTIL(pt, i == target);
    printf("TAREFA 2 passou: i == %i\n", i);

    PT_WAIT_UNTIL(pt, i == (target*2));
    printf("TAREFA 2 passou: i == %i * 2\n", i);
    
    PT_END(pt);
}

// --- Seção 4: Main ---
int main(void)
{
    int counter = 0;

    PT_INIT(&pt1);
    PT_INIT(&pt2);

    while(counter != 100)
    {
        printf("--- counter: %i ---\n", counter);
        tarefa1(&pt1, counter);
        tarefa2(&pt2, 30);
        counter++;
    }

    return 0;
}