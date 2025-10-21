# Port de RTOS para ARM Cortex-M0 / M3 / M4 / M33 / M7

## Registradores

* **R0 a R7 → Low Registers**
* **R8 a R12 → High Registers**
* **R13 → MSP (Main Stack Pointer) / PSP (Process Stack Pointer)**

  > São dois registradores diferentes que compartilham o mesmo endereço.

### Diferenças entre núcleos

* A distinção entre *Low* e *High registers* faz diferença **apenas no Cortex-M0**.
* O **M0** possui instruções que funcionam **somente com os Low registers**, o que resulta em:

  * Maior tempo de troca de contexto
  * Desempenho inferior ao portar um RTOS

## Contexto salvo na pilha em uma Interrupção (ISR)

Quando ocorre uma interrupção, o núcleo ARM salva automaticamente na pilha os seguintes registradores:

```
R0, R1, R2, R3, R12, LR, PC, xPSR
```

## Pilhas do Sistema

* **PSP (Process Stack Pointer):** pilha das tarefas
* **MSP (Main Stack Pointer):** pilha do sistema

Quando se utiliza um sistema operacional (RTOS), **é essencial ter ambos os stack pointers**.

### Comparativo

* **Com apenas um SP:**
  Seria necessário garantir que nenhuma pilha estoure, já que todas as interrupções compartilhariam o mesmo espaço.

* **Com PSP e MSP:**

  * A interrupção é empilhada na pilha da tarefa onde ocorreu.
  * Uma interrupção dentro de outra interrupção vai para a **pilha do sistema (MSP)**.
  * A pilha do sistema é usada para **instalar e gerenciar tarefas** — na prática, é a pilha das interrupções.
  * A pilha da tarefa contém as variáveis locais e o contexto da própria tarefa.

> ⚠️ **Erro comum:** achar que a pilha é infinita.
> Se o sistema travar logo após iniciar, é provável que ocorreu **estouro de pilha**.

## Comportamento do Main

* A função **`main()`** é uma **thread privilegiada**, pois é executada durante a **interrupção de reset**.
* Fora do contexto do `main()`, **não é possível alterar o Stack Pointer (SP)**.
* Portanto, a execução da função `main()` acontece **dentro de uma interrupção**.

## Temporização e Interrupções

* Ter um **timer no núcleo ARM** (e não depender de periféricos específicos do fabricante) **facilita o porte de um RTOS**, pois:

  * O tempo estará sempre no mesmo registrador, independentemente do microcontrolador.

* No ARM, **a troca de contexto não ocorre em interrupções de timer**, mas sim em **interrupções de software**.

  * Assim, em um RTOS, **cada interrupção de hardware deve gerar uma interrupção de software** para realizar o *context switch*.

## Interrupções “Naked”

* Uma **interrupção naked** não realiza automaticamente o salvamento de contexto.
* Nesse tipo de interrupção, **somente os registradores disponíveis podem ser usados diretamente**, sem empilhar dados na pilha.