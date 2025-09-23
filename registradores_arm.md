# Tabela de Registradores ARM 32-bit (ARMv7-A)

| Registrador | Nome Alternativo                       | Função Principal                                   |
| ----------- | -------------------------------------- | -------------------------------------------------- |
| **R0–R12**  | –                                      | Registradores de uso geral                         |
| **R13**     | SP (Stack Pointer)                     | Ponteiro de pilha                                  |
| **R14**     | LR (Link Register)                     | Registrador de link (armazena endereço de retorno) |
| **R15**     | PC (Program Counter)                   | Contador de programa (próxima instrução)           |
| –           | CPSR (Current Program Status Register) | Registrador de status (contém flags N, Z, C, V)    |


## Flags do CPSR (Para Instruções Condicionais)

- **N** (Negative): resultado negativo
- **Z** (Zero): resultado zero
- **C** (Carry): vai-um em adição ou empréstimo em subtração
- **V** (Overflow): transbordamento aritmético