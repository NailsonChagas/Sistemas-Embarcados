### **1) Definição de sistema e sistemas embarcados**

**Pergunta:**
Defina o que é um sistema. O que diferencia um sistema embarcado de um sistema qualquer? Baseando-se nessa diferença, quais são as características desejadas em um sistema embarcado?

**Resposta:**
Um sistema é uma combinação de componentes que atuam em conjunto para desempenhar uma função.
Um sistema embarcado é um sistema composto por elementos computacionais colaborativos destinados a executar funções específicas, diferindo de sistemas genéricos por seu propósito especializado.

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

### SLIDE SISTEMAS EMBARCADOS
| **CISC**                                                                 | **RISC**                                                                 |
| ------------------------------------------------------------------------ | ------------------------------------------------------------------------ |
| Ênfase em *hardware*                                                     | Ênfase em *software*                                                     |
| Inclui instruções complexas com execução em múltiplos ciclos de clock     | Poucas instruções com execução em um ciclo de clock                      |
| Operações com memória incluídas nas instruções                           | LOAD e STORE são instruções exclusivas para acesso à memória             |
| Códigos pequenos com alta taxa de ciclos por segundo                     | Poucos ciclos por segundo, códigos maiores                               |
| Maior quantidade de transistores para armazenamento de instruções complexas | Ocupa mais transistores em registradores                                 |



**Impacto no conjunto de instruções:**

* **RISC**: conjunto reduzido de instruções simples e padronizadas
* **CISC**: conjunto amplo de instruções complexas e especializadas
* **Tendência atual**: processadores híbridos que combinam características de ambas arquiteturas

---

### **3) Protothreads**

**Pergunta:**
Explique o princípio de funcionamento das protothreads. Que limitação existe no uso de `switch/case` dentro de uma protothread? É possível utilizar a API das protothreads dentro de funções que serão chamadas por uma protothread? Se sim, como isso é possível? Por que as variáveis dentro de uma protothread precisam ser declaradas com o keyword `static`? Finalmente, comente sobre as principais vantagens de se utilizar protothreads quando comparado ao laço infinito tradicional.

**Resposta:**
Protothreads são uma técnica que simula threads por meio de máquinas de estados, utilizando macros e o retorno da linha onde as instruções de espera são chamadas. Essa abordagem oferece baixo consumo de memória e maior simplicidade, tornando o desenvolvimento mais prático em sistemas que não se pode usar threads reais.

Não é possível utilizar a API das protothreads dentro de funções chamadas por uma protothread, pois as macros de espera (`PT_WAIT_UNTIL`, por exemplo) geram instruções `case`. Caso essas macros sejam usadas dentro de funções, o `case` seria inserido em um `switch` incorreto.

Precisam ser declaradas com o keyword `static`, pois, sem isso, seus valores seriam perdidos ao final de cada chamada da função dentro do laço principal (`main loop`). 

A principal vantagem de se utilizar protothreads em comparação com o laço infinito tradicional é que o código se torna mais **organizado, modular e legível**, dispensando a necessidade de implementar manualmente várias máquinas de estado explícitas. Não disperdiçar energia com loops infinitos, emular concorrencia

**Exemplo simplificado de funcionamento:**

```c
typedef struct {
  uint32_t lc; // Armazena o estado (linha em que parou) da protothread
} pt;

// Inicia o estado da máquina como 0
#define PT_INIT(pt) (pt)->lc = 0

// Cria o switch da máquina de estados, começando sempre no case 0
#define PT_BEGIN(pt) switch((pt)->lc) { case 0:

// Espera até que a condição seja verdadeira
#define PT_WAIT_UNTIL(pt, condition) \
  (pt)->lc = __LINE__; \
  case __LINE__: \
  if(!(condition)) return 0

// Fecha o switch, reseta o estado e indica que terminou
#define PT_END(pt) } \
  (pt)->lc = 0; \
  return 2
```

---

### **4) Pilha (stack) em sistemas computacionais**

**Pergunta:**
A pilha (stack) de um sistema computacional é uma das regiões de memória mais importantes para o desenvolvimento de uma aplicação. Comente: quais são os principais usos da pilha, em que tipo de memória é implementada a pilha e aonde a pilha fica nessa memória, como definimos o tamanho da pilha e o que é estouro de pilha.

**Resposta:**
A pilha é usada para armazenar variáveis locais, parametros, endereços de retorno e contexto de funções. Normalmente é implementada na RAM, crescendo ou decrescendo a partir de um endereço pré-definido. O tamanho da pilha é definido na configuração do sistema (linker). O estouro de pilha ocorre quando o espaço reservado é excedido, sobrescrevendo outras áreas da memória e causando falhas na aplicação.

---

### **5) Máquina de estados com ponteiros de funções**

**Pergunta:**
Descreva a implementação de uma máquina de estados finitos através de ponteiros de funções. Como podemos criar múltiplas instâncias de uma máquina de estados utilizando essa metodologia de projeto? Caso ache necessário, realize a explicação através de um exemplo.

**Resposta:**
Uma máquina de estados finitos implementada com ponteiros de funções é aquela em que cada estado é representado por uma função. Para estruturar essa máquina, cria-se uma struct chamada `SM`, que contém, no mínimo, um array com ponteiros para todas as funções correspondentes aos estados possíveis, chamado de `actions`, e um índice indicando o estado atual da máquina, chamado de `state`.

Para executar a máquina de estados, é usado uma função que recebe como parâmetros as entradas do estado e máquina de estados a ser usada. Essa função invoca, internamente, `sm->action[sm->state](sm, parâmetros)`, executando o estado atual. Caso ocorra a transição para outro estado, o índice `state` é atualizado para refletir o novo estado.

Para se criar multiplas maquinas de estado simplesmente devem ser iniciadas outras structs `SM`, como cada uma tem um `state` diferente, elas serão independentes.

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
A memória FLASH apresenta duas limitações principais em relação à RAM: maior consumo de energia e menor desempenho, devido ao seu tempo de acesso (dessincronia com o processador). Quando a frequência da CPU é superior à da FLASH, o processador precisa aguardar a conclusão do acesso, desperdiçando ciclos de clock.

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
$$
N_{\text{states}} = \left\lceil \frac{T_{\text{acesso}}}{T_{\text{clock do processador}}} - 1 \right\rceil
$$

* 30 MHz → período ≈ 33,3 ns → **0 wait states**
* 60 MHz → período ≈ 16,7 ns → **2 wait states**
* 160 MHz → período ≈ 6,25 ns → **5 wait states**

---

### **9) Funções reentrantes em sistemas preemptivos**

**Pergunta:**
Por que é importante que em sistemas operacionais preemptivos se utilize funções reentrantes? Caso não seja possível, como pode-se proteger uma função não-reentrante para o uso seguro em sistemas preemptivos?

**Resposta:**
Função reentrante é uma função que pode ser executada concorrentemente por múltiplas tarefas ou threads de forma segura, sem que uma execução interfira na outra. Em sistemas preemptivos, onde uma tarefa pode ser interrompida a qualquer momento para dar lugar a outra, utilizar funções reentrantes é essencial para evitar condições de corrida, corrupção de dados ou comportamento imprevisível.

Caso uma função não seja reentrante, é possível protegê-la utilizando mecanismos como semáforos, garantindo que apenas uma tarefa acesse a função por vez.

---

### **10) Projeto de controlador PI em ponto fixo**

**Pergunta:**
Imagine que você está implementando uma fonte de corrente controlada a partir de um conversor CC-CC. Essa fonte deve ter corrente de saída entre 0,01 e 1,0 A, sendo que o sensor de corrente utilizado tem resolução conforme a figura abaixo e está alimentado com 3,3 V. O sinal PWM utilizado no controle deve ser de 100 kHz e o processador será de ponto fixo, com 160 MHz de frequência de clock e barramento de 32 bits. O conversor A/D utilizado será de 12 bits, com referências em 0 V e 3,3 V. A técnica de controle utilizada será um PI com a seguinte característica:

$$
D_n = D_{n-1} + 0,05859 \cdot Erro_{n} - 0,00957 \cdot Erro_{n-1}
$$

A referência de controle será fornecida por um potenciômetro ligado a uma fonte de 3,3 V, conectado em outro canal do conversor A/D. Utilizando base Q, projete o fator de conversão utilizado para o cálculo do valor de erro e determine uma base Q coerente para os ganhos do controlador PI e para o módulo gerador do sinal PWM. Escreva o código em C para implementar esse controlador, considerando que o valor atual do sensor de corrente encontra-se em uma variável chamada `AD_value` e que o valor adquirido do divisor resistivo se encontra em uma variável `referencia`.

**Resposta:**

**Cálculos preliminares:**

```c
/*
Conversor A/D de 12 bits: (2^12) - 1 = 4095
Resolução de corrente: 0,01 A

Fator de conversão para Q12:
corrente: round((3.3 * 2^12) / 4095) = 3
referência: round((3.3 * 2^12) / 4095) = 3

Relação entre clock do processador e PWM:
Freq_processador / Freq_PWM = 160e6 / 100e3 = 1600
*/
```

**Implementação do controlador PI em C:**

```c
// Definição dos ganhos em ponto fixo
static const uint32_t Kp_Q17     = 7680; // Kp em Q17
static const uint32_t KpKi_Q17   = 1254; // Kp * Ki em Q17

// Conversão dos valores A/D para Q12
uint32_t AD_valueQ12 = AD_value * 3;
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
duty_cycle = (curr_duty_cycleQ29 * 1600) >> 29;
```


---

### **11) `static` e `volatile` em variáveis e funções**

**Pergunta:**
O que significa `static` e `volatile` para variáveis globais, locais e funções?

**Resposta:**

* **`static`**: 
  * **Variáveis locais**: deixam de ser criadas e destruídas a cada chamada da função, permanecendo ativas durante toda a execução do programa e preservando valores.
  * **Variáveis globais**: restringem escopo ao arquivo de declaração, evitando conflitos.
  * **Funções**: limitam visibilidade ao arquivo, funcionando como encapsulamento (similar a `private` em C++/Java).

* **`volatile`**: indica que o valor da variável pode mudar de forma imprevisível (hardware ou interrupções), impedindo otimizações perigosas do compilador.

  * Pode ser usado em variáveis globais ou locais.
  * Não existe o conceito de funções `volatile`.

---

### **12) Escopo de declaração de variável**

**Pergunta:**
Em que seção da memória variáveis globais/static não iniciadas vão parar? Qual seu valor inicial?
Em que seção da memória variáveis globais/static iniciadas vão parar?
Em que seção da memória variáveis locais vão parar?

**Resposta:**

* **Variáveis globais/static não iniciadas**: são alocadas na seção **BSS** da memória e possuem valor inicial **0**.
* **Variáveis globais/static iniciadas**: são alocadas na seção **DATA** da memória, recebendo o valor definido na declaração.
* **Variáveis locais**: são alocadas na **stack** (pilha). Caso não sejam inicializadas, contêm **lixo de memória**.



### **13) Processo de inicialização do microcontrolador**

**Pergunta:**
Descreva o processo de inicialização de um microcontrolador desde sua alimentação até chegar na função `main()`. Para qual região de memória o processador aponta ao ser alimentado? Que procedimentos devem ser realizados antes de ir para a função `main()`? Por que podemos dizer que a função `main()` é uma função privilegiada?

**Resposta:**
* Ao ligar: ocorre a interrupção de reset, processador começa no vetor de reset (memória de boot/flash).

* **Startup code:**

  -  Inicializa Stack Pointer (SP).

  - Copia .data da flash para RAM.

  - Zera .bss (globais não inicializadas).

  - Configurações mínimas (clock/sistema).

  - Chamada da main(): ponto de entrada do programa do usuário.

Por que privilegiada? É o início formal da aplicação, só executa após ambiente estar pronto, controla todo o fluxo do programa.