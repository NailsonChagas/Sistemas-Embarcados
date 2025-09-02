# Eficiência Energética

* Eficiência energética e custo são muito importantes na escolha do microprocessador a ser utilizado no desenvolvimento de um produto.
* Quando há apenas lógica, o tempo de processamento não se difere tanto, mas cálculos matemáticos complexos demoram mais.
* Colocar o processador em modo de baixo consumo quando não precisa fazer contas (exemplo: intervalo entre ações de controle).
* A eficiência energética do processador pode ser encontrada em tabelas em **mW/DMIPS**.

  * **mW/DMIPS** significa quantos miliwatts o processador consome para executar 1 milhão de instruções Dhrystone por segundo (DMIPS).
  * É um parâmetro que permite comparar eficiência entre diferentes arquiteturas: quanto menor o valor, mais eficiente.
* Processadores mais robustos tendem a ser menos eficientes energeticamente.
* Microcontroladores geralmente consomem menos de 1 W.
* Importante checar o consumo de corrente do microcontrolador em diferentes modos de operação (ativo, idle, sleep, deep sleep).

---

# Densidade de Código

* **Densidade** é compilar o mesmo código para diferentes micros e comparar o tamanho do executável.
* Todas as arquiteturas modernas possuem otimizações para aumentar a densidade de código (exemplo: instruções de 16 bits em processadores de 32 bits – como no Thumb da ARM).
* Como memória é cara, processadores que geram código mais compacto permitem gastar menos memória e reduzir o custo do produto.
* O compilador afeta mais o tamanho dos executáveis do que a arquitetura em si, portanto a escolha do compilador é muito importante.

---

# Memória em Sistemas Embarcados

## Mapa de Memória

* Representa como as diferentes memórias (SRAM, FLASH, periféricos, registradores) estão organizadas no espaço de endereços do processador.

## Conexões de Memória

* Definem como os diferentes tipos de memória estão ligados ao barramento e à CPU, impactando desempenho e latência.

## SRAM

* Não precisa de refresh.
* Cada bit = 6 transistores.
* Mantém valor enquanto houver energia.
* Relativamente insensível a distúrbios elétricos.
* Consome menos energia.
* Memória usada dentro do microcontrolador por conta da estabilidade e baixo consumo.

## SDRAM

* 1 bit = 1 transistor + 1 capacitor.
* Valores devem ser recarregados a cada 10–100 ms (ciclos de refresh).
* Mais sensível a ruído elétrico (por depender de capacitores).
* Mais lenta e mais barata que SRAM.
* Consome mais energia que SRAM.
* Sensível à temperatura (afeta estabilidade e consumo).
* Usada para expandir memória do microcontrolador (exemplo: rodar Linux, armazenar frame buffer de display).

## FLASH

* Consome mais energia que RAM.
* Memória onde o programa é gravado (não volátil).
* Menor desempenho que RAM devido ao tempo de acesso típico (tempo necessário para recuperar uma instrução ou dado).
* Se a frequência da CPU for maior que a da FLASH, o processador precisa esperar pelos dados, desperdiçando ciclos de clock.

### Estratégias para mitigar limitações:

1. **Wait states**: ciclos de espera inseridos durante o acesso à FLASH.

   * São atrasos controlados no pipeline para sincronizar a velocidade da memória com a CPU.
2. **Copiar código crítico para RAM**:

   * Proporciona desempenho máximo (exemplo: rotinas de controle, filtros digitais).
   * É caro porque usa RAM, que é limitada.
   * No ESP32, interrupções são executadas na RAM; no STM32, colocar a rotina de interrupção na RAM aumenta o desempenho.
3. **Cache de instruções**:

   * ST e outros fabricantes usam bancos extras de FLASH e SRAM para pré-carregar instruções.
   * Permite que enquanto um banco fornece dados, outro já esteja carregando o próximo bloco.
   * Problema: falta de determinismo em saltos (condicionais, funções, “goto”), porque a instrução seguinte pode não estar no cache.

     * **Branch trace buffer** ajuda prevendo saltos e armazenando histórico, diminuindo penalidades.
   * Ainda assim, execução em cache é mais lenta que em RAM.
   * Cache encarece porque é feito em SRAM.

---

## Barramentos e Arquiteturas

* **Barramentos matriciais**: interconexões internas modernas que permitem múltiplos acessos concorrentes entre CPU, DMA e periféricos.
* Mesmo que o código não faça distinção entre RAMs, restrições físicas podem impedir acessos simultâneos.
* **Harvard vs Von Neumann**:

  * Harvard: separa barramento de instruções e dados → mais desempenho.
  * Von Neumann: usa único barramento → pode gerar gargalos.
* **CCMRAM (Core Coupled Memory)**: RAM ligada diretamente ao núcleo, usada para código ou dados que exigem máximo desempenho.
* **DMA (Direct Memory Access)**: permite que periféricos leiam/escrevam em memória sem passar pela CPU, liberando processamento.
* Como colocar algo em RAM específica (exemplo STM32): via atributos no compilador/linker script.
* Para desempenho máximo:
  * Código crítico na **CCMRAM**.
  * Dados principais na **RAM**.
  * DMA utilizando outra área de RAM independente.
