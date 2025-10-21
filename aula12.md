# Criando um Projeto com o FreeRTOS

## CMSIS (Cortex Microcontroller Software Interface Standard)

* O **CMSIS** é a **camada de abstração** do RTOS — ele fornece funções que chamam internamente as funções do próprio FreeRTOS.

* Essa camada facilita a **portabilidade** e a **integração com ferramentas ARM**, mas:

  > ⚠️ **Usa mais memória**, portanto, em sistemas com recursos limitados, pode ser melhor utilizar o **FreeRTOS diretamente**.

* **Na aula 12**, está sendo utilizada a **versão CMSIS_V1**.

  * **CMSIS_V1:** possui **7 níveis de prioridade**
  * **CMSIS_V2:** possui **31 níveis de prioridade**

## Configurações Importantes

* **ENABLE_FPU:** habilita o suporte à **Floating Point Unit (FPU)**, permitindo o uso de números de ponto flutuante (`float`).
* **USE_NEWLIB_REENTRANT:** habilita uma **versão reentrante da biblioteca padrão C (libc)**, evitando conflitos em sistemas multitarefa.

## Alocação de Memória

* O **`malloc`** do FreeRTOS é **reentrante**, ou seja, pode ser usado em várias tarefas sem causar corrupção de memória.

## Temporização e Tarefas

* Para **leituras periódicas do ADC**, é possível usar um **software timer**.

  * Caso **não** utilize software timers, será necessário **criar uma tarefa separada** para cada temporização.

### `vTaskDelayUntil()` vs `vTaskDelay()`

* **`vTaskDelay()`**: suspende a tarefa por um tempo relativo (ex.: “espere 100 ms a partir de agora”).
* **`vTaskDelayUntil()`**: suspende a tarefa até um instante absoluto no tempo, ideal para **sistemas periódicos** e **controle preciso de tempo**.

## Otimização de Memória

* É possível **habilitar ou desabilitar** funcionalidades do FreeRTOS para **reduzir o espaço ocupado na memória Flash**.

  * Exemplo: desativar recursos como *timers*, *event groups* ou *trace facilities* se não forem utilizados.

## Configuração do Timer Base (Timebase Source)

* Ao usar o FreeRTOS, configure o **Timebase Source** em **SYS**, selecionando um **timer diferente do SysTick**.

  * Isso evita conflito com o temporizador interno usado pelo kernel do FreeRTOS.