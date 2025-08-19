# **Sistemas Embarcados**
O foco principal da disciplina será programação concorrente e **RTOS** (*Real-Time Operating System*).

**Observação:** Semáforos não resolvem problemas de acesso a **seções críticas**, apenas realizam sincronização.

## 1. O que é um sistema embarcado?
**Sistema:** combinação de componentes que atuam para desempenhar uma função.

Um **sistema embarcado** é um sistema de computação dedicado a executar funções específicas dentro de um dispositivo maior.
Ele é projetado para atender requisitos de desempenho, consumo de energia, custo e confiabilidade, normalmente com recursos de hardware e software otimizados.

Exemplos:
- Controladores automotivos (injeção eletrônica, ABS, airbag)
- Equipamentos médicos (monitores cardíacos, bombas de infusão)
- Eletrônicos de consumo (smart TVs, câmeras digitais)
- Dispositivos IoT (sensores industriais, automação residencial)

## 2. Tecnologias utilizadas em sistemas embarcados
- **Arquiteturas de instruções:** CISC e RISC
- **Memórias:** Flash, SRAM e SDRAM
    - Eficiência energética
    - Desempenho
    - Robustez
- **Periféricos:** A/D, D/A, displays, etc.
- **RTOS:** programação concorrente, interrupções, drivers, etc.
    - FreeRTOS
    - Zephyr
- **Linguagens:** C/C++, MicroPython, Rust/Embassy

## 3. Linux embarcado vs Linux tradicional
- **Linux embarcado**
    - Adaptado para rodar em hardware com recursos limitados (baixo consumo de memória e processamento)
    - Kernel customizado com apenas os drivers e módulos necessários
    - Geralmente sem interface gráfica ou com interface simplificada
    - Exemplos: OpenWrt (roteadores), Raspbian Lite (Raspberry Pi), Buildroot, Yocto Project

- **Linux tradicional**
    - Voltado para computadores e servidores com maior capacidade de processamento
    - Kernel completo com amplo suporte a hardware e funcionalidades
    - Interface gráfica rica e suporte a múltiplos aplicativos simultâneos
    - Exemplos: Ubuntu, Fedora, Debian
