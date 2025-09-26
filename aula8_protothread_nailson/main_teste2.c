#include <stdio.h>

// gcc ./main_teste.c -o ./main_teste.bin
// gcc -E main_teste.c -o main_teste_preprocessed.c


// --- Seção 1: Definição do Protothread e Macros de Controle ---
#define PT_WAIT_UNTIL(c)  \
    if(!(c)) return 0; // sempre sai da função se a condição não bater

// --- Seção 2: Variáveis Globais ---
int i = 0;

// --- Seção 3: Tarefas ---
int tarefa1(int count)
{
    while(1)
    {
        PT_WAIT_UNTIL(i == count);
        printf("i: %i == count: %i\n", i, count);
        i += 10;
    }
}

int tarefa2(int target)
{
    PT_WAIT_UNTIL(i == target);
    printf("TAREFA 2 passou: i == %i\n", i);

    PT_WAIT_UNTIL(i == (target*2));
    printf("TAREFA 2 passou: i == %i * 2\n", i);
}

// --- Seção 4: Main ---
int main(void)
{
    int counter = 0;

    while(counter != 100)
    {
        printf("--- counter: %i ---\n", counter);
        tarefa1(counter);
        tarefa2(30);
        counter++;
    }

    return 0;
}