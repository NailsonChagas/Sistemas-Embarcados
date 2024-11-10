# Sistemas Embarcados
Este repositório será um compilado da minha tentativa de aprender mais sobre o desenvolvimento de sistemas embarcados.

## **Roteiro de Aprendizado:**
#### 1. **Introdução ao STM32 Nucleo-F401RE e Ambiente de Desenvolvimento**
   - **Objetivo:** Familiarizar-se com a IDE STM32CubeIDE, instalação, configuração e estrutura de um projeto.
   - **Prática:** Criar um projeto básico para piscar o LED integrado (LD2).
   - **Tópicos envolvidos:** Configuração da IDE, estrutura de projetos, conceitos básicos de microcontroladores.

#### 2. **Programação de Portas GPIO (General Purpose Input/Output)**
   - **Objetivo:** Compreender o funcionamento das portas de entrada e saída digitais.
   - **Prática:** Controlar LEDs internos e externos, manipular estados lógicos de portas.
   - **Tópicos envolvidos:** Configuração e controle de GPIO, programação de I/O digital.

#### 3. **Controle de LED com Delay**
   - **Objetivo:** Controlar LEDs usando técnicas de temporização simples (delay).
   - **Prática:** Acionar LEDs em intervalos de tempo fixos.
   - **Tópicos envolvidos:** Criação de delays, controle simples de I/O.

#### 4. **Introdução ao Uso de Interrupções**
   - **Objetivo:** Entender interrupções externas e sua aplicação para respostas rápidas a eventos.
   - **Prática:** Configurar interrupções para acionar LEDs ao pressionar um botão.
   - **Tópicos envolvidos:** NVIC, interrupções externas, debounce de botão.

#### 5. **Controle de Botões e Debouncing**
   - **Objetivo:** Aprender a trabalhar com entradas digitais, botões e técnicas de "debouncing".
   - **Prática:** Implementar debounce e controlar LEDs a partir de múltiplos botões.
   - **Tópicos envolvidos:** Resistor Pull-up/Pull-down, debounce, entradas digitais estáveis.

#### 6. **Uso de Timers no STM32**
   - **Objetivo:** Entender o funcionamento dos timers e sua aplicação em temporização.
   - **Prática:** Criar um temporizador simples para eventos periódicos, como piscar um LED em intervalos regulares.
   - **Tópicos envolvidos:** Contadores de timer, interrupções baseadas em timer.

#### 7. **PWM (Pulse Width Modulation)**
   - **Objetivo:** Gerar sinais PWM para controle de intensidade e velocidade.
   - **Prática:** Gerar PWM para controlar a intensidade de brilho de um LED ou a velocidade de um motor.
   - **Tópicos envolvidos:** Geração de PWM com timers, controle de largura de pulso.

#### 8. **Leitura de Sensores Analógicos (ADC)**
   - **Objetivo:** Usar o conversor analógico-digital para ler sinais analógicos.
   - **Prática:** Ler valores de um sensor analógico, como o LM35 (temperatura).
   - **Tópicos envolvidos:** ADC, conversão de sinal analógico para digital.
   
#### 9. Controle de Potenciômetro
   - **Objetivo:** Aprender a usar um potenciômetro para controlar variáveis em tempo real.
   - **Prática:** Ler o valor de um potenciômetro usando o ADC e controlar o brilho de um LED.
   - **Tópicos envolvidos:** Leitura analógica, controle de intensidade.

#### 10. **Sensores Digitais e Comunicação Serial (I2C, UART)**
   - **Objetivo:** Trabalhar com sensores digitais e comunicação com módulos periféricos.
   - **Prática:** Configurar um sensor DHT11/DHT22 para ler dados de temperatura e umidade.
   - **Tópicos envolvidos:** I2C, UART, protocolo de comunicação de sensores.

#### 11. **Exibição de Dados em Displays LCD (I2C)**
   - **Objetivo:** Controlar displays LCD para visualização de dados.
   - **Prática:** Exibir a leitura de sensores em um display LCD.
   - **Tópicos envolvidos:** I2C, controle de displays LCD.

#### 12. **Comutação de Múltiplos Sensores e Dispositivos**
   - **Objetivo:** Gerenciar a entrada/saída de múltiplos sensores e dispositivos com multiplexação.
   - **Prática:** Ler e controlar múltiplos sensores ou LEDs em sequência.
   - **Tópicos envolvidos:** Multiplexação de sensores, gerenciamento de múltiplos dispositivos.

#### 13. **Controle de Motores e Atuadores**
   - **Objetivo:** Aprender a controlar motores DC e outros atuadores.
   - **Prática:** Controlar a velocidade de um motor DC usando PWM e um driver de motor.
   - **Tópicos envolvidos:** Drivers de motor, controle de velocidade, PWM.

#### 14. **Comunicação Serial e USB**
   - **Objetivo:** Enviar e receber dados via comunicação serial e USB.
   - **Prática:** Enviar dados de sensores para o computador via USB.
   - **Tópicos envolvidos:** USART, virtual COM port (VCP), terminal serial.

#### 15. **Comunicação sem Fio via Bluetooth (HC-05)**
   - **Objetivo:** Implementar comunicação sem fio entre o STM32 e dispositivos móveis/computadores.
   - **Prática:** Enviar dados de sensores para um computador via módulo Bluetooth HC-05.
   - **Tópicos envolvidos:** Comunicação UART, Bluetooth.

#### 16. **Introdução ao Sistema Operacional em Tempo Real (RTOS)**
   - **Objetivo:** Entender a utilização de RTOS para gerenciar múltiplas tarefas simultâneas.
   - **Prática:** Criar uma aplicação simples com FreeRTOS para controlar múltiplos LEDs.
   - **Tópicos envolvidos:** FreeRTOS, multitarefa, escalonamento de prioridades.


## **Materiais:**
| **Material**                         | **Quantidade Necessária** | **Modelo / Especificação**                         |
|--------------------------------------|---------------------------|----------------------------------------------------|
| **STM32 Nucleo-F401RE**              | 1                         |                                                    |
| **LEDs (internos e externos)**       | 5-10                      | LEDs comuns de 5mm (diversas cores)                |
| **Botões**                           | 3-5                       | Botões de pressão (push button)                    |
| **Sensores Analógicos (LM35, LDR)** | 1-2                       | LM35 LDR(Temperatura), ou outros sensores analógicos  |
| **Sensores Digitais (DHT11/DHT22)**  | 1-2                       | DHT11 ou DHT22 (Temperatura e Umidade)             |
| **Driver de Motor e Motor DC**       | 1-2                       | L298N (Driver de motor) e motor DC de 6V-12V       |
| **Display LCD (I2C)**                | 1                         | Display LCD 16x2 com interface I2C                 |
| **Módulo Bluetooth HC-05**           | 1                         | HC-05 Bluetooth Module                             |
| **Resistores**                       | Vários                    | Diversos valores (220Ω, 1kΩ, 10kΩ, etc.)           |
| **Potenciômetro**                    | 1                         | 	Potenciômetro de 10kΩ                           |
| **Fonte de Alimentação**             | 1                         | Fonte de 5V DC (Micro-USB ou 12V DC com regulador) |
| **Jumpers e Fios de Conexão**        | 1 pacote                  | Jumpers macho-macho, macho-fêmea                   |
| **Protoboard (Breadboard)**          | 1                         | Protoboard padrão (tamanho médio)                  |
| **Capacitores**                      | 2-5                       | Capacitores de 10µF, 100nF, 1µF                    |
| **Diodos (se necessário)**           | 1-2                       | 1N4007 (para proteção contra picos de corrente)    |
| **Fonte de Alimentação**             | 1                         | Fonte DC 5-12V                                     |
| **Multímetro**                       | 1                         | Multímetro digital                                 |
