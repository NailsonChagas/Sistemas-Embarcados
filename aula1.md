# Aula 1

## Arquitetura de Processadores

### RISC vs CISC

* **RISC (Reduced Instruction Set Computer):**

  * Instruções de mesmo tamanho, geralmente executadas em um único ciclo de clock.
  * Cada instrução ocupa exatamente uma palavra de memória.
  * Mais simples e eficiente em termos de execução, mas pode exigir mais instruções para realizar tarefas complexas.

* **VL-RISC (Variable-Length RISC):**

  * Similar ao RISC, porém com instruções de tamanhos variáveis.

* **CISC (Complex Instruction Set Computer):**

  * Instruções podem ter tamanho menor que a palavra do processador.
  * Programas tendem a ser menores em comparação ao RISC.
  * Contudo, instruções mais complexas podem demandar mais ciclos de clock.

* **Observações importantes:**

  * Atualmente, os processadores são **híbridos**, combinando características de RISC e CISC.
  * Exemplo: **x86** é CISC, mas suas instruções são convertidas em **microinstruções RISC** no nível de hardware.
  * Acesso direto à memória pode ser um problema quando há assimetria de acesso.

### Seleção de Processador

Aspectos relevantes para escolher um processador:

* Desempenho.
* Eficiência energética.
* Disponibilidade de periféricos.
* Velocidade de acesso à memória.
* Robustez (tolerância a ruído e EMI).

### Exemplos de Arquiteturas

* **RISC (principais no mercado):** ARM, PowerPC, RISC-V, MIPS.
* **CISC:** x86.
* **Uso específico:** HCS08 ainda utilizado pela sua robustez contra EMI.

> Observação: Processadores **muito robustos** geralmente não são tão eficientes energeticamente — e vice-versa. Por isso, fabricantes possuem linhas diferentes, focadas em **robustez** ou **eficiência**.

### Pipeline

* Permite dividir a execução em múltiplos estágios:
  * Exemplo de uma pipeline de 5 estágios: **Fetch → Decode → Execute → Access → Write-back**.
* Em um pipeline de 5 estágios, cada instrução percorre todos os passos, mas o processador finaliza **uma instrução por ciclo**.
* Mais etapas → maior paralelismo, porém maior complexidade e consumo de energia.

### Registradores

* Operações são feitas preferencialmente em **registradores**, evitando a limitação da velocidade da memória.
* Registrador pode ser entendido como uma **RAM estática** extremamente rápida e interna ao processador.

### ARM

* Características:

  * Não possui operações binárias de forma granular: ou manipula-se o **registro inteiro**, ou não se altera nada.
* Exemplo de instrução assembly em RISC:

  ```
  ADD R4, R3, R2
  ```

  (soma o conteúdo de R3 e R2 e armazena em R4 — sempre utilizando registradores).

### Coprocessadores

* **Coprocessador:** Unidade auxiliar que executa funções específicas para aliviar a CPU.
* **FPU (Floating Point Unit):** Unidade de ponto flutuante, acelera cálculos matemáticos complexos.
* **MPU (Memory Protection Unit):** Controla permissões de acesso à memória, garantindo segurança e isolamento.

> Exemplo: **Cortex-M4** não possui interface para coprocessador externo.

### Eletrônica de Potência e Robustez

* Ambientes com **alto ruído elétrico** exigem processadores mais robustos (por exemplo, em aplicações de eletrônica de potência).

---

## Processador Usado na Disciplina

**STM32G4 (ARM Cortex-M4):**

* Suporte a **processamento analógico e digital**.
* **DMA** (Direct Memory Access).
* **FMAC** (Filter Math Accelerator).
* **CORDIC** (coprocessador para funções trigonométricas e hiperbólicas).
* **SPI**.
* Não possui **SDIO**.