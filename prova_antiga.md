1) É possível afirmar que ao optar por um determinado processador de baixo consumo, com menor poder computacional, para uma dada aplicação, será obtida melhor eficiência energética do que com um processador de maior poder computacional? Comente, explicando o porquê de chegar nessa conclusão. Complemente sua resposta dissertando sobre os motivos de nem sempre podermos utilizar os modos de menor consumo de energia disponíveis em um processador para determinadas aplicações.

Resposta: Por ter baixo poder computacional, ele talvez leve mais ciclos de clock, e assim, mesmo sendo de baixo consumo, pode acabar consumindo mais energia do que um processador de desempenho maior, que conseguiria terminar a atividade mais rápido e, em seguida, entrar em modo de baixo consumo. Ou seja, a eficiência energética não depende apenas do consumo instantâneo do processador, mas também do tempo total em que ele permanece ativo para concluir a tarefa.

Além disso, nem sempre é possível utilizar os modos de menor consumo de energia disponíveis em um processador, pois muitas aplicações exigem tempo real, latência mínima ou resposta imediata a eventos externos.

2) Comente sobre as diferenças existentes entre sistemas foreground/background, cooperativos e preemptivos quanto ao cumprimento de restrições temporais / determinismo e operação das rotinas de tratamento de interrupções. Se possível, utilize exemplos. Ainda, explique o conceito de preempção.

**Superlaço (foreground/background/baremetal)**
- Programa principal em loop de repetição
- Interrupções tratam eventos assíncronos
- **Evento assíncrono**: Não pode ser previsto (não depende do código executado no momento)
- **Evento síncrono**: Pode ser previsto (depende do código executado no momento)

**Núcleo RTOS Cooperativo**
- Tarefas devem liberar explicitamente o controle da CPU
- Baixa latência em interrupções
- Permite uso de funções não reentrantes
- Tempo de resposta limitado pela tarefa mais lenta
- Menor preocupação com recursos compartilhados
- Tarefas de alta prioridade podem esperar por tarefas de menor prioridade

**Núcleo RTOS Preemptivo** (ex: escalonamento Round-robin)
- Tarefas de maior prioridade interrompem as de menor prioridade
- Tempo de execução deterministico para tarefas de alta prioridade
- Requer cuidado com funções reentrantes
- Overhead de 1 a 5% da CPU
- Consome espaço adicional de RAM e código

3) Explique o princípio de funcionamento das protothreads. Por que não é possível utilizar um switch/case dentro de uma protothread? É possível utilizar a API das protothreads dentro de funções que setão chamadas por uma protothread? Finalmente, comente sobre as principais vantagens de se utilizar protothreads quando comparado ao laço infinito tradicional.

Não sei essa a parte ainda

4) Qual é a principal limitação da memória FLASH em sistemas embarcados, quando processadores com clocks de barramento de dezenas de MHz (acima de 20 MHz) são utilizados? Que soluções podem ser aplicadas para se minimizar esta limitação? Comente sobre cada uma dessas soluções, destacando vantagens e desvantagens. Adicionalmente, considere que a memória FLASH utilizada em um microcontrolador tenha tempo de acesso de 33,3ns. Quantos wait states seriam necessários para acessar essa memória com o clock do micricontrolador em 30, 60 e 160 MHz?

A memória FLASH apresenta duas limitações principais em relação à RAM: maior consumo de energia e menor desempenho, devido ao seu tempo de acesso. Quando a frequência da CPU é superior à da FLASH, o processador precisa aguardar a conclusão do acesso, desperdiçando ciclos de clock.

Para mitigar esse problema, podem ser aplicadas algumas soluções:

* **Inserção de *wait states***: o processador aguarda ciclos extras até que a FLASH esteja pronta para fornecer dados.
  * *Vantagem*: solução simples, amplamente suportada por microcontroladores.
  * *Desvantagem*: reduz o desempenho efetivo, já que a CPU passa parte do tempo ociosa.

* **Uso de cache em SRAM**: blocos de instruções ou dados acessados recentemente são armazenados em SRAM, que possui tempo de acesso muito menor.
  * *Vantagem*: acelera significativamente o desempenho em acessos repetitivos.
  * *Desvantagem*: aumenta custo e consumo de área do chip, já que a SRAM é mais cara e ocupa mais espaço.

* **Prefetch buffer**: instruções sequenciais são buscadas da FLASH de forma antecipada, antes de a CPU solicitá-las.
  * *Vantagem*: melhora a eficiência em execuções lineares.
  * *Desvantagem*: pouco eficaz em programas com muitos desvios e ramificações.

5) No que implica utilizar o keyword static em um código desenvolvido em linguagem C, tanto para variáveis globais quanto para variáveis locais. E para funções?

Quando aplicado a variáveis locais, faz com que elas deixem de ser criadas e destruídas a cada chamada da função, passando a existir durante toda a execução do programa e preservando seu valor entre chamadas; em variáveis globais, restringe o escopo ao arquivo em que foram declaradas, evitando conflitos de nomes e impedindo acesso em outros módulos; já em funções, limita sua visibilidade ao arquivo de definição, funcionando como uma forma de encapsulamento interno (como private em C++ e Java).

6) Por que é importante que em sistemas operacionais preemptivos se utilize funções reentrantes? Caso não seja possível, como pode-se proteger uma função não-reentrante para o uso seguro em sistemas preemptivos?

7)Imagine que você está implementando uma fonte de corrente controlada a partir de um conversor CC-CC. Essa fonte deve ter corrente de saída entre 0,01 e 1,0, sendo que o sensor de corrente utilizado tem resolução conforme a figura abaixo e, está alimentado com 3,3V. O sinal PWM utilizado no controle deve ser de 100KHz e o processador utilizado será de ponto fixo, com 160MHz de frequência de clock e 32 bits de barramento. O conversor A/D utilizado será de 12 bits, com referências em 0V e 3,3V. A técnica de controle utilizada será um PI com a seguinte característica Dn = D(n-1) + 0,05859*Erro - 0,00957*Erro. A referência de controle será fornecida por um potenciômetro ligado a uma fonte de 3,3V, que estará conectado em outro canal do conversor A/D. Utilizando base Q, projete o fator de correção utilizado para o cálculo do valor de erro e determine uma base Q coerente para os ganhos do controlador PI e para o módulo gerador do sinal PWM. Escreva o código em C para implementar esse controlador, considerando que o valor atual do sensor de corrente encontra-se em uma variável chamada AD_value e que o valor adquirido do divisor resistivo se encontra em uma variável de nome referencia.