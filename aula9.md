RTOS

Toda tarefa tem um laço infinito (background virtual)

Como ocorrer a instalação de uma tarefa:
- Ponteiro de função
- Contexto

Troca de contexto acontecem através de interrupções (ex: main() é chamado pela interrupção de reset)

A cada interrupção é populado e despopulado a pilha