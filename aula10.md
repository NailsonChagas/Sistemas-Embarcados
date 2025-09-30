### **Recurso**

Tudo aquilo que uma tarefa pode utilizar (ex.: dispositivos de I/O, variáveis, memória, periféricos).

* Recursos podem ser **compartilhados entre tarefas**.
* Cada tarefa deve obter **direito exclusivo de acesso** a um recurso compartilhado para evitar corrupção de dados.
* Operações **atômicas** não podem ser interrompidas (executadas em 1 ciclo de clock ou de forma indivisível).
* O **mutex** é usado para resolver conflitos de acesso a recursos.

---

### **Mutex x Semáforo**

* **Mutex**:

  * Inicia normalmente bloqueado (0).
  * Tem “dono”: apenas a tarefa que adquiriu o mutex pode liberá-lo.
  * Garante prioridade (herança de prioridade).
  * Uso principal: controle de **recursos compartilhados**.

* **Semáforo**:

  * Pode iniciar livre (1) ou com contagem.
  * Não possui dono: qualquer tarefa pode liberar.
  * Não garante herança de prioridade.
  * Uso principal: **sincronização entre tarefas** ou sinalização de eventos.

---

### **Inversão de Prioridades**

Ocorre quando uma tarefa de alta prioridade fica bloqueada porque uma tarefa de baixa prioridade mantém um recurso compartilhado.
Enquanto isso, tarefas de prioridade intermediária podem continuar executando, impedindo que a de baixa prioridade libere o recurso — travando a de alta prioridade.

**Soluções:**

1. **Topo de prioridade:** elevar a tarefa com acesso ao recurso à maior prioridade entre as envolvidas. → Perde a previsibilidade temporal.
2. **Herança de prioridade:** a tarefa que possui o recurso herda a prioridade da mais alta que o requisitou. → Também afeta a temporalidade.
3. **Servidor de recursos:** criar uma tarefa dedicada para gerenciar os recursos compartilhados.

   * Exemplo: o **X Server** no Linux/Unix. Ele centraliza o acesso a recursos gráficos (placa de vídeo, monitor, teclado, mouse).
   * Em vez de cada aplicação acessar diretamente o hardware, o X Server recebe as requisições e organiza o acesso.
   * Dessa forma, **múltiplos programas** podem usar os mesmos dispositivos sem conflito.
   * Essa abordagem mantém a **característica temporal** (ordem de requisições respeitada).
   * Funciona bem para recursos relativamente lentos; para recursos que exigem resposta muito rápida pode haver limitações.

---

### **Região Crítica**

Trecho de código que deve ser executado **sem interrupções**, geralmente no acesso a variáveis globais ou estruturas do SO.
Estratégia comum: **desabilitar interrupções** temporariamente.

---

### **Deadlock (Impasse)**

Situação em que a **Tarefa A espera a Tarefa B** liberar um recurso, mas a **Tarefa B também espera pela Tarefa A**, gerando bloqueio infinito.

**Soluções:**

1. Definir uma **ordem fixa de aquisição de mutex**.
2. Implementar **timeout** nas tentativas de aquisição.
3. Utilizar um **servidor de recursos** para controlar o acesso.

---

### **Overload (Sobrecarga)**

Ocorre quando o processador/RTOS **não consegue executar todas as tarefas dentro dos prazos**, devido ao uso excessivo da CPU.

**Soluções:**

1. **Otimizar o código** das tarefas.
2. **Migrar para um processador mais potente**.

---

### **Tipos de Tarefas em um RTOS**

1. **Periódicas:** executadas em intervalos regulares e previsíveis.
2. **Aperiódicas (esporádicas):** não seguem periodicidade, mas possuem um tempo mínimo entre ativações.
