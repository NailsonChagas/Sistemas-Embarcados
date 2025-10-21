# Escalonadores

O **escalonador** é o software responsável por **decidir qual tarefa ganha o processador** em determinado momento.

Existem diferentes **políticas de escalonamento**, que definem **como** o escalonador irá funcionar.

## Escalonadores em Sistemas Embarcados vs. Computadores

Não há diferença conceitual entre o escalonador de um **sistema embarcado** e o de um **computador**.
A diferença está **nas restrições** e **nas metas de projeto**, como previsibilidade temporal, consumo de energia e uso de recursos.

## Escalonamento em RTOS

Em **sistemas de tempo real (RTOS)**, os algoritmos de escalonamento podem ser:

* **Estáticos:** parâmetros definidos **durante o projeto** do sistema.
* **Dinâmicos:** parâmetros podem ser **alterados em tempo de execução** (*run time*).

## Tipos de Escalonadores

* **Algoritmos offline:** definem a escala **durante o projeto**, sem tomar decisões enquanto o sistema roda.
* **Classificações possíveis:**

  * **Offline estático**
  * **Online estático**
  * **Online dinâmico**

## Escolha do Escalonador

Para decidir qual escalonador utilizar, é preciso compreender a **carga das tarefas** — ou seja, o tempo necessário para processá-las.

* A **carga pode variar** para uma mesma tarefa.
* É necessário determinar a **condição de pior caso** (*worst case*), isto é, a maior carga possível.
* Uma **carga estática** é quando o pior caso é conhecido.
* Para **projetos de tempo real**, as cargas devem ser **estáticas**.

## Tarefas Periódicas e Aperiódicas

* Uma **tarefa aperiódica** ocorre quando a taxa de ativação **não permite a execução completa** do evento anterior.
  → Isso inviabiliza o projeto de sistemas de tempo real.
* Em **sistemas de tempo real**, **todas as tarefas devem ser periódicas**.

## Sistemas Cooperativos

Em sistemas **cooperativos**, a **tarefa mais prioritária** é a que **mais perde o prazo** caso algo dê errado, pois depende da liberação das tarefas de menor prioridade.

## Abordagens de Escalonamento

### 1. Garantia em Tempo de Projeto

*(Mais comum em sistemas de tempo real)*

* A **carga máxima de cada tarefa** é conhecida.
* O processador deve estar preparado para **executar todas as tarefas no pior caso**.

#### Tipos:

* **Executivo cíclico:** ativa ciclicamente as tarefas segundo uma escala pré-definida.

* **Prioridades fixas:** cada tarefa tem um grau de prioridade que define sua ordem de execução.

  * Há **filas de pronto** para cada nível de prioridade.
  * Quando há várias tarefas com a mesma prioridade, é usado um **escalonador secundário** para decidir a ordem.
  * Utilizado em casos específicos, como **servidores em microcontroladores**.
  * Difere do cooperativo: aqui, **a tarefa de menor prioridade** é a que **pode perder o prazo**.

* **Taxa Monotônica (Rate Monotonic):**

  * Melhor algoritmo entre os de **prioridades fixas**, mas depende de **premissas**:

    * As tarefas devem ser **periódicas e independentes**.
    * O **deadline** de cada tarefa ≤ seu **período**.
    * O **pior tempo de execução** deve ser **conhecido e constante**.
    * O **tempo de troca de contexto** é assumido como **nulo** (*não é real*).
    * **Nenhuma tarefa tem *release jitter*** (*variação no momento de ativação* — o que não ocorre na prática, pois interrupções e atrasos de hardware geram jitter).

  **Observação:** quanto **menor o período** da tarefa, **maior sua prioridade**.
  Em geral, **operações de I/O** têm alta prioridade, pois possuem **taxa de chegada alta**.

### 2. Garantia em Tempo de Execução

* As decisões são tomadas **durante a execução**.
* **Não é adequada para sistemas de tempo real**, mas pode ser usada em sistemas comuns.

### 3. Garantia de Melhor Esforço (*Best Effort*)

* O sistema faz o **melhor possível** dentro das condições atuais.
* **Não deve ser usada em tempo real.**

## Considerações de Projeto

* **Muita preempção** (interrupção de tarefas em andamento) consome **muito tempo do processador** com **trocas de contexto**.
* O **quantum** (tempo máximo de execução de uma tarefa antes da troca) é geralmente igual ao **passo do sistema**.

  * Exemplo: se o passo é **1 ms**, idealmente nenhuma tarefa deve demorar mais de **1 ms**.
  * Exceder o passo do sistema **degrada o comportamento temporal**, gerando **atrasos acumulados**.

## Desempenho do Sistema Operacional

O **desempenho de um sistema operacional** está diretamente relacionado ao seu **escalonador**.
O projeto do escalonador deve considerar a **aplicação do sistema**:

* Um OS voltado à **experiência do usuário** prioriza **responsividade**.
* Um OS para **sistemas embarcados** prioriza **previsibilidade temporal** e **confiabilidade**.