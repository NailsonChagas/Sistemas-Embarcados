### **1) Definição de sistema e sistemas embarcados**

**Pergunta:**
Defina o que é um sistema. O que diferencia um sistema embarcado de um sistema qualquer? Baseando-se nessa diferença, quais são as características desejadas em um sistema embarcado?

**Resposta:**
Um sistema é uma combinação de componentes que atuam em conjunto para desempenhar uma função.
Um sistema embarcado é um sistema de computação dedicado a executar funções específicas dentro de um dispositivo maior, diferindo de sistemas genéricos por seu propósito especializado.

**Características desejadas em sistemas embarcados:**

* Requisitos de desempenho específicos
* Baixo consumo de energia
* Custo otimizado
* Alta confiabilidade
* Eficiência computacional
* Tamanho reduzido (quando aplicável)
* Tempo real (em muitos casos)

---

### **2) Diferenças entre arquiteturas RISC e CISC**

**Pergunta:**
Quais são as principais diferenças das arquiteturas RISC e CISC? Qual o impacto destas diferenças no conjunto de instruções de um processador?

**Resposta:**

| **RISC**                     | **CISC**                           |
| ---------------------------- | ---------------------------------- |
| Instruções de mesmo tamanho  | Instruções de tamanho variável     |
| Instruções simples           | Instruções complexas               |
| Execução mais eficiente      | Pode demandar mais ciclos de clock |
| Pipeline mais eficiente      | Pipeline menos eficiente           |
| Programas geralmente maiores | Programas geralmente menores       |

**Impacto no conjunto de instruções:**

* **RISC**: conjunto reduzido de instruções simples e padronizadas
* **CISC**: conjunto amplo de instruções complexas e especializadas
* **Tendência atual**: processadores híbridos que combinam características de ambas arquiteturas

---

### **3) Protothreads**

**Pergunta:**
Explique o princípio de funcionamento das protothreads. Que limitação existe no uso de switch/case dentro de uma protothread? É possível utilizar a API das protothreads dentro de funções que serão chamadas por uma protothread? Se sim, como isso é possível. Por que as variáveis dentro de uma protothread precisam ser declaradas com o keyword `static`? Finalmente, comente sobre as principais vantagens de se utilizar protothreads quando comparado ao laço infinito tradicional.

**Resposta:**
Ainda não respondida.

---

### **4) Pilha (stack) em sistemas computacionais**

**Pergunta:**
A pilha (stack) de um sistema computacional é uma das regiões de memória mais importantes para o desenvolvimento de uma aplicação. Comente: quais são os principais usos da pilha, em que tipo de memória é implementada a pilha e aonde a pilha fica nessa memória, como definimos o tamanho da pilha e o que é estouro de pilha.

**Resposta:**
Ainda não respondida.

---

### **5) Máquina de estados com ponteiros de funções**

**Pergunta:**
Descreva a implementação de uma máquina de estados finitos através de ponteiros de funções. Como podemos criar múltiplas instâncias de uma máquina de estados utilizando essa metodologia de projeto? Caso ache necessário, realize a explicação através de um exemplo.

**Resposta:**
Ainda não respondida.

---

### **6) Eficiência energética em processadores**

**Pergunta:**
É possível afirmar que ao optar por um determinado processador de baixo consumo, com menor poder computacional, para uma dada aplicação, será obtida melhor eficiência energética do que com um processador de maior poder computacional? Comente, explicando o porquê de chegar nessa conclusão. Complemente sua resposta dissertando sobre os motivos de nem sempre podermos utilizar os modos de menor consumo de energia disponíveis em um processador para determinadas aplicações.

**Resposta:**
Por ter baixo poder computacional, ele talvez leve mais ciclos de clock e, assim, mesmo sendo de baixo consumo, pode acabar gastando mais energia do que um processador de desempenho maior, que conseguiria terminar a atividade mais rápido e, em seguida, entrar em modo de baixo consumo.

Ou seja, a eficiência energética não depende apenas do consumo instantâneo do processador, mas também do tempo total em que ele permanece ativo para concluir a tarefa.

Além disso, nem sempre é possível utilizar os modos de menor consumo de energia, pois muitas aplicações exigem tempo real, latência mínima ou resposta imediata a eventos externos.

---

### **7) Sistemas foreground/background, cooperativos e preemptivos**

**Pergunta:**
Comente sobre as diferenças existentes entre sistemas foreground/background, cooperativos e preemptivos quanto ao cumprimento de restrições temporais/determinismo e operação das rotinas de tratamento de interrupções. Se possível, utilize exemplos. Ainda, explique o conceito de preempção.

**Resposta:**

**Superlaço (foreground/background/baremetal):**

* Programa principal em loop de repetição
* Interrupções tratam eventos assíncronos
* Evento assíncrono: não pode ser previsto (não depende do código executado no momento)
* Evento síncrono: pode ser previsto (depende do código executado no momento)

**Núcleo RTOS Cooperativo:**

* Tarefas devem liberar explicitamente o controle da CPU
* Baixa latência em interrupções
* Permite uso de funções não reentrantes
* Tempo de resposta limitado pela tarefa mais lenta
* Menor preocupação com recursos compartilhados
* Tarefas de alta prioridade podem esperar por tarefas de menor prioridade

**Núcleo RTOS Preemptivo (ex.: escalonamento Round-robin):**

* Tarefas de maior prioridade interrompem as de menor prioridade
* Tempo de execução determinístico para tarefas de alta prioridade
* Requer cuidado com funções reentrantes
* Overhead de 1 a 5% da CPU
* Consome espaço adicional de RAM e código

---

### **8) Limitação da memória FLASH**

**Pergunta:**
Qual é a principal limitação da memória FLASH em sistemas embarcados, quando processadores com clocks de barramento de dezenas de MHz (acima de 20 MHz) são utilizados? Que soluções podem ser aplicadas para se minimizar esta limitação? Comente sobre cada uma dessas soluções, destacando vantagens e desvantagens. Adicionalmente, considere que a memória FLASH utilizada em um microcontrolador tenha tempo de acesso de 33,3ns. Quantos wait states seriam necessários para acessar essa memória com o clock do microcontrolador em 30, 60 e 160 MHz?

**Resposta:**
A memória FLASH apresenta duas limitações principais em relação à RAM: maior consumo de energia e menor desempenho, devido ao seu tempo de acesso. Quando a frequência da CPU é superior à da FLASH, o processador precisa aguardar a conclusão do acesso, desperdiçando ciclos de clock.

**Soluções possíveis:**

* **Wait states**: CPU aguarda ciclos extras até a FLASH fornecer dados.

  * *Vantagem*: simples, amplamente suportado.
  * *Desvantagem*: reduz desempenho efetivo.
* **Cache em SRAM**: blocos acessados recentemente ficam em SRAM.

  * *Vantagem*: desempenho muito melhor em acessos repetitivos.
  * *Desvantagem*: maior custo e área no chip.
* **Prefetch buffer**: busca antecipada de instruções sequenciais.

  * *Vantagem*: eficiente em execuções lineares.
  * *Desvantagem*: pouco eficaz em programas com muitos desvios.

**Cálculo dos wait states (tempo de acesso = 33,3 ns):**

* 30 MHz → período ≈ 33,3 ns → **0 wait states**
* 60 MHz → período ≈ 16,7 ns → **2 wait states**
* 160 MHz → período ≈ 6,25 ns → **5 wait states**

---

### **9) Keyword `static` em C**

**Pergunta:**
No que implica utilizar o keyword `static` em um código desenvolvido em linguagem C, tanto para variáveis globais quanto para variáveis locais. E para funções?

**Resposta:**

* **Variáveis locais**: deixam de ser criadas e destruídas a cada chamada da função, permanecendo ativas durante toda a execução do programa e preservando valores.
* **Variáveis globais**: restringem escopo ao arquivo de declaração, evitando conflitos.
* **Funções**: limitam visibilidade ao arquivo, funcionando como encapsulamento (similar a `private` em C++/Java).

---

### **10) Funções reentrantes em sistemas preemptivos**

**Pergunta:**
Por que é importante que em sistemas operacionais preemptivos se utilize funções reentrantes? Caso não seja possível, como pode-se proteger uma função não-reentrante para o uso seguro em sistemas preemptivos?

**Resposta:**
Ainda não respondida.

---

### **11) Projeto de controlador PI em ponto fixo**

**Pergunta:**
Imagine que você está implementando uma fonte de corrente controlada a partir de um conversor CC-CC. Essa fonte deve ter corrente de saída entre 0,01 e 1,0, sendo que o sensor de corrente utilizado tem resolução conforme a figura abaixo e está alimentado com 3,3V. O sinal PWM utilizado no controle deve ser de 100 kHz e o processador utilizado será de ponto fixo, com 160 MHz de frequência de clock e 32 bits de barramento. O conversor A/D utilizado será de 12 bits, com referências em 0V e 3,3V. A técnica de controle utilizada será um PI com a seguinte característica:

$$
D_n = D_{n-1} + 0,05859 \cdot Erro - 0,00957 \cdot Erro
$$

A referência de controle será fornecida por um potenciômetro ligado a uma fonte de 3,3V, conectado em outro canal do conversor A/D. Utilizando base Q, projete o fator de correção utilizado para o cálculo do valor de erro e determine uma base Q coerente para os ganhos do controlador PI e para o módulo gerador do sinal PWM. Escreva o código em C para implementar esse controlador, considerando que o valor atual do sensor de corrente encontra-se em uma variável chamada `AD_value` e que o valor adquirido do divisor resistivo se encontra em uma variável de nome `referencia`.

**Resposta:**
Ainda não respondida.

---

### **12) `static` e `volatile` em variáveis e funções**

**Pergunta:**
O que significa `static` e `volatile` para variáveis globais, locais e funções?

**Resposta:**

* **`static`**: já detalhado na questão 9.
* **`volatile`**: indica que o valor da variável pode mudar de forma imprevisível (hardware ou interrupções), impedindo otimizações perigosas do compilador.

  * Pode ser usado em variáveis globais ou locais.
  * Não existe o conceito de funções `volatile`.