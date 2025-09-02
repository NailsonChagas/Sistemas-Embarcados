# Notas sobre Controle Digital e Representação em Ponto Fixo (Base Q)

## Uso de Ponto Flutuante em Algoritmos Iterativos

- **Problema:** Não usar `float` em algoritmos iterativos, como algoritmos de **controle** e **filtro**.
- **Motivo:** O erro de arredondamento se acumula a cada iteração.
- **Alternativa:**
    - Usando `double` o problema é **menos pronunciado**, pois há mais precisão.
    - Usando **ponto fixo (base Q)** o problema **não ocorre**, pois nós decidimos explicitamente a precisão.

---

## Representação de Números em Base Q

### Representação de `0.1` em Q31

- Fórmula geral:
  `valor_Q = valor_real * 2^N`
  onde `N` é o número de bits da parte fracionária.

- Em **Q31**, temos 31 bits fracionários:
  `0.1 * 2^31 ≈ 214748365`

- Representação em hexadecimal (aprox):
  `0x0CCCCCCD`

---

## FFT em Q15 vs Float em Processadores de 32 bits

- FFT em **Q15** (16 bits, ponto fixo):
    - Operações de multiplicação/soma são feitas com inteiros.
    - Processadores de 32 bits executam **operações inteiras muito mais rápido** que operações em ponto flutuante (quando não há FPU).
    - Já com `float`, cada operação envolve mais ciclos de clock e maior consumo de energia.
- **Conclusão:** FFT em Q15 é **mais rápida e eficiente** em muitos processadores de 32 bits sem FPU.

---

## Conversão para Base Q

- Fórmula:
  `valor_Q = round(valor_real * 2^N)`

- Exemplo em Q15:
  `valor_real = 0.25`
  `valor_Q = 0.25 * 2^15 = 8192`

---

## Escolha da Base Q Mínima com ADC

- ADC de **10 bits**, entrada de **0 a 2.5V**, mas sistema mede **0 a 5V**.
- Resolução mínima requerida: **0.0125**.
- Precisamos garantir que a base Q tenha resolução menor que o erro permitido:
  `2^-N ≤ 0.0125`
  `N ≥ log2(1/0.0125) ≈ 7`
- Logo, **Q7 ou maior** já atende, mas geralmente se usa margens (Q15, Q31).

---

## Representar 0.2388 em Base Q

- Em Q15:
  `0.2388 * 2^15 ≈ 7826`
- Em Q31:
  `0.2388 * 2^31 ≈ 512934665`

---

## Operações em Base Q

- **Soma e Subtração:**
    - Ambos os termos devem estar na **mesma base Q**.
    - O resultado também estará nessa base.

- **Multiplicação e Divisão:**
    - Não precisam ter a mesma base Q.
    - O resultado terá base `Q = soma dos expoentes`.

- **Shifts:**
    - **Shift à direita** → diminui a base Q (divide por `2^k`).
    - **Shift à esquerda** → aumenta a base Q (multiplica por `2^k`).

---

## Ordem das Operações

- A ordem em base Q **influencia**.
- Exemplo:
  `(a * b) / c ≠ a * (b / c)`
- Primeiro multiplicar e depois dividir, pois:
    - Multiplicar aumenta a precisão.
    - Dividir antes pode causar truncamento e perda de resolução.

---

## ADC

- **Quantização:** O ADC **trunca** os valores, não arredonda.
- **Sample and Hold:** Congela o valor analógico antes da conversão.
- **Atraso:** O processo de conversão gera atraso fixo.
- Esse atraso pode ser modelado no **plano Z** como um fator `z^-n`.

---

## PWM

- O PWM pode ser modelado como a **comparação** de uma onda **dente de serra** com o valor do **duty cycle**.
- A resolução do PWM depende da quantidade de bits do registrador.

---

## Simulação

- Para simular o sistema, usar um **time step** pelo menos **100 vezes maior que a frequência do sistema**.

---

## Resolução do PWM e Ruído

- Se a resolução do PWM é baixa comparada ao controle digital:
    - O sinal de saída não consegue representar fielmente o valor calculado.
    - Isso gera **ruído e ripple** na saída do controlador.

## Converter Ação de Controle na Base Q para PWM
A conversão de uma ação de controle em base Q para um valor de PWM é realizada pela seguinte relação:

`PWM = (Frequência_do_Processador / Frequência_da_Ação_de_Controle) * (Ação_de_Controle_Q >> N)`

Onde:
-   `Frequência_do_Processador` é a frequência de clock do microcontrolador.
-   `Frequência_da_Ação_de_Controle` é a taxa de atualização do algoritmo de controle (em Hz).
-   `Ação_de_Controle_Q` é o valor calculado pelo controlador, representado na base Q (ex: Q15, Q31).
-   `N` é o número de bits fracionários da base Q utilizada (ex: 15 para Q15).
-   `>> N` é a operação de *shift* (deslocamento) à direita por `N` bits, que efetivamente converte o número de volta para sua forma inteira, removendo a representação de ponto fixo.