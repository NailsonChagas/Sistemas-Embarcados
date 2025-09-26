### **10) Projeto de controlador PI em ponto fixo**

**Pergunta:**
Imagine que você está implementando uma fonte de corrente controlada a partir de um conversor CC-CC. Essa fonte deve ter corrente de saída entre 0,01 e 1,0 A, sendo que o sensor de corrente utilizado tem resolução conforme a figura abaixo e está alimentado com 3,3 V. O sinal PWM utilizado no controle deve ser de 100 kHz e o processador será de ponto fixo, com 160 MHz de frequência de clock e barramento de 32 bits. O conversor A/D utilizado será de 12 bits, com referências em 0 V e 3,3 V. A técnica de controle utilizada será um PI com a seguinte característica:

[
D_n = D_{n-1} + 0,05859 \cdot Erro_{n} - 0,00957 \cdot Erro_{n-1}
]

A referência de controle será fornecida por um potenciômetro ligado a uma fonte de 3,3 V, conectado em outro canal do conversor A/D. Utilizando base Q, projete o fator de conversão utilizado para o cálculo do valor de erro e determine uma base Q coerente para os ganhos do controlador PI e para o módulo gerador do sinal PWM. Escreva o código em C para implementar esse controlador, considerando que o valor atual do sensor de corrente encontra-se em uma variável chamada `AD_value` e que o valor adquirido do divisor resistivo se encontra em uma variável `referencia`.

**Resposta:**

**Cálculos preliminares:**

```c
/*
Conversor A/D de 12 bits: (2^12) - 1 = 4095
Resolução de corrente: 0,01 A

Fator de conversão para Q12:
corrente: round((2 * 2^12) / 4095) ≈ 2
referência: round((3 * 2^12) / 4095) ≈ 3

Relação entre clock do processador e PWM:
Freq_processador / Freq_PWM = 160e6 / 100e3 ≈ 1600
*/
```

**Implementação do controlador PI em C:**

```c
// Definição dos ganhos em ponto fixo
static uint32_t Kp_Q17     = 7680; // Kp em Q17
static uint32_t KpKi_Q17   = 1254; // Kp * Ki em Q17

// Conversão dos valores A/D para Q12
uint32_t AD_valueQ12 = AD_value * 2;
uint32_t RefQ12      = referencia * 3;

// Cálculo do erro
uint32_t curr_errQ12 = RefQ12 - AD_valueQ12;
static uint32_t last_errQ12;

// Atualização do ciclo de trabalho em Q29
static uint32_t last_duty_cycleQ29;
uint32_t curr_duty_cycleQ29 = last_duty_cycleQ29 
                              + Kp_Q17 * curr_errQ12 
                              - KpKi_Q17 * last_errQ12;

// Atualização dos estados para a próxima iteração
last_duty_cycleQ29 = curr_duty_cycleQ29;
last_errQ12        = curr_errQ12;

// Conversão para o módulo PWM (considerando fator de 1500)
duty_cycle = (curr_duty_cycleQ29 * 1500) >> 29;
```

