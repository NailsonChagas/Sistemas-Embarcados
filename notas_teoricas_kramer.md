## Pilha, Ordenação e Armazenamento de Dados


<p align="center">
  <img src="./src/mapa_de_memoria.png" alt="Mapa de Memória">
</p>

- **Data**  
  - Armazena variáveis **globais e estáticas** com **valor inicial**.  
  - Exemplo: `int x = 5;`  

- **BSS (Block Started by Symbol)**  
  - Armazena variáveis **globais e estáticas** sem valor inicial ou inicializadas com **0** por padrão.  
  - Exemplo: `int y;`  

- **Heap**  
  - Usada para **alocação dinâmica** durante a execução (`malloc`, `calloc`, `new`).  
  - O programador deve **gerenciar a memória** (liberar quando não for mais usada).  
  - Cresce **para cima**, do endereço mais baixo para o mais alto.  



### Stack


- Região da memória utilizada para armazenar dados temporários:
  - Variáveis locais
  - Parâmetros de funções
  - Valores de registradores durante chamadas de função

- Estrutura de dados com restrição, onde os elementos só podem ser adicionados ou removidos em uma única extremidade (*top*).  
- Modo de operação: **LIFO** (*Last In, First Out*).  
- Operações principais:
  - **Push** → adição de elemento  
  - **Pop** → remoção de elemento  
- **SP (Stack Pointer)** → ponteiro que indica o topo da pilha.  
- Localizada na memória RAM, normalmente ao final da memória.  
  - O **SP** aponta para o último endereço e, conforme itens são adicionados à pilha, o endereço é **decrescido**.  
- **Estouro de pilha (Stack Overflow)**  
  - Ocorre quando são empilhados mais valores do que o espaço reservado para a pilha.  
  - Isso pode causar acesso ilegal à memória, **sobrescrevendo variáveis ou ponteiros**,  
    resultando em inconsistências de funcionamento ou comportamento indefinido do sistema.  


#### Finalidades da pilha

- Guardar a posição de retorno em um salto para **interrupção**  
- Guardar a posição de retorno ao **chamar uma função**  
- Guardar o conteúdo dos **registradores** quando usados em funções e interrupções  
- **Alocar variáveis locais**  
- **Passar parâmetros** em chamadas de função  

---

### Ordenação de dados

### Endianness (Little Endian vs Big Endian)

* **Little Endian**: O **byte menos significativo (LSB)** é armazenado no endereço mais baixo.
* **Big Endian**: O **byte mais significativo (MSB)** é armazenado no endereço mais baixo.

🔹 **Por que é importante?**

* Protocolos de comunicação podem transmitir os bytes em uma ordem diferente da usada pelo processador.
* Saber o *endianness* evita erros na interpretação de dados ao enviar/receber informações entre dispositivos heterogêneos.
* o único tipo de dado que pode não dar problema, é o **char**

---

### Alinhamento de Dados

O **alinhamento** garante que variáveis sejam armazenadas em endereços múltiplos de seu tamanho natural (ex.: uma `int32` alinhada em múltiplo de 4).

* **Vantagens**: Acesso mais rápido, já que a CPU pode ler/escrever em palavras inteiras.
* **Problemas de desalinhamento**: Acesso pode ser mais lento ou até gerar *fault* em alguns processadores ARM.

🔹 **Em C/GCC** podemos controlar isso com atributos:

* `__attribute__((packed))` → Desabilita alinhamento, deixando os dados “colados” na memória.
* `__attribute__((aligned(n)))` → Garante que o dado esteja alinhado em múltiplos de *n*.

---

### Exemplos

```c
// Estrutura com alinhamento natural
struct exemplo1 {
    char a;     // 1 byte
    int b;      // 4 bytes (provavelmente alinhado em múltiplo de 4)
};

// Estrutura "packed" (sem alinhamento)
struct exemplo2 {
    char a;
    int b;
} __attribute__((packed));

// Estrutura alinhada a 2 bytes
struct exemplo3 {
    char a;
    int b;
} __attribute__((aligned(2)));
```

* **exemplo1** pode ocupar 8 bytes devido ao *padding* automático.
* **exemplo2** ocupa 5 bytes, mas pode ser mais lento de acessar.
* **exemplo3** força alinhamento de 2 bytes, útil em protocolos ou mapeamento de hardware.

--- 

## Memórias em Sistemas Embarcados

### SDRAM e SRAM

- **SRAM - Static Random Access Memory**
  - Memória volátil
  - Não necessita de refresh
  - Cada célula de armazenamento de um bit é implementada com um circuito de 6 transistores
  - Mantém o valor enquanto houver energia
  - Relativamente insensível a distúrbios, como ruídos elétricos
  - Mais rápida, porém de maior custo que memórias do tipo DRAM
  - Custo de energia menor e estável

- **SDRAM - Synchronous Dynamic Random Access Memory**
  - Cada célula armazena um bit com um transistor e um capacitor
  - Os valores devem ser recarregados periodicamente (refresh a cada 10–100 ms)
  - Sensível a distúrbios
  - Mais lenta e mais barata que as memórias SRAM
  - Aumento de consumo conforme a temperatura
  - Pode gerar falhas de segurança devido à sensibilidade a interferências

> O ideal, devido às suas vantagens, é a utilização de **SRAM** em sistemas; no entanto, seu alto custo torna inviável o uso em muitos projetos. Por isso, sistemas menos críticos frequentemente utilizam **SDRAM**, que apresenta maior capacidade e menor custo, mesmo com desempenho inferior à SRAM.

### Memória Flash

- Memórias do tipo **não volátil**
- Mantêm os dados mesmo na ausência de energia
- Utilizadas para armazenamento permanente, como firmware, sistemas embarcados e dispositivos USB
- Mais lenta que SRAM e SDRAM em leitura e escrita
- Não requer refresh, mas possuem ciclo limitado de gravação/apagamento

#### Assincronia entre processador e Flash

A Flash possui **menor desempenho e é menos eficiente que a RAM**

Quando a frequência do processador é maior que a da memória Flash, ocorre uma **assincronia entre eles**, o que compromete o desempenho do processador, que precisa aguardar a memória responder às operações de leitura ou escrita.  

Para mitigar esse problema, normalmente são utilizados três métodos:

* **Inserir wait-cycles durante o acesso à Flash**  
  - **Vantagens:**  
    - Solução de baixo custo  
    - Simples de implementar  
  - **Desvantagens:**  
    - Ainda há perda de desempenho devido à diferença de velocidade entre processador e memória  
    - Não melhora a eficiência em operações intensivas de leitura/escrita  

* **Uso de cache**  
  - **Vantagens:**  
    - Reduz significativamente o número de acessos à memória lenta  
    - Melhora consideravelmente o desempenho do processador  
  - **Desvantagens:**  
    - Aumenta a complexidade do hardware  
    - Consome mais área de memória (SRAM)  
    - Pode gerar inconsistência se o cache não for corretamente gerenciado  
    - Possui comportamento não determinístico, principalmente em aplicações de tempo real

* **Prefetching ou buffers**  
  - **Vantagens:**  
    - Permite que o processador continue executando sem esperar pela memória lenta  
    - Aumenta o throughput em leitura sequencial de dados  
  - **Desvantagens:**  
    - Implementação mais complexa  
    - Eficaz principalmente para padrões de acesso previsíveis  
    - Pode desperdiçar energia e memória se dados pré-carregados não forem utilizados

* **Copiar código da FLASH para a RAM**  
  - **Vantagens:**  
    - Desempenho máximo do sistemas  
  - **Desvantagens:**  
    - Solução de alto custo

#### Modo de aceleração de memória

Outra maneira de melhorar o desempenho é utilizar o **modo de aceleração de memória**, no qual o **barramento da memória Flash é aumentado**.  
Isso permite que o processador acesse a memória mais rapidamente, reduzindo a latência de leitura e melhorando a eficiência geral do sistema.  

- **Vantagens:**  
  - Reduz o tempo de espera do processador  
  - Melhora o desempenho em comparação ao acesso normal à Flash  

- **Desvantagens:**  
  - Pode aumentar o consumo de energia  
  - Nem todos os dispositivos suportam esse modo  
  - Limites físicos da memória podem restringir o ganho de desempenho

### EEPROM (Electrically Erasable Programmable Read-Only Memory)

- **Vantagens:**  
  - Não volátil, mantém os dados mesmo sem energia  
  - Permite regravação elétrica sem remover o chip  

- **Desvantagens:**  
  - Velocidade de escrita e leitura baixa  
  - Número limitado de ciclos de escrita (baixa durabilidade)  

---

### FlexMemory

- **Descrição:**  
  - Opção alternativa à EEPROM, geralmente combinando memória Flash e RAM  
  - Pode ser usada para armazenamento não volátil com maior flexibilidade  

- **Vantagens:**  
  - Maior capacidade de armazenamento comparado à EEPROM  
  - Possibilidade de leitura/escrita mais rápida  

- **Desvantagens:**  
  - Mais complexa e geralmente mais cara  
  - Requer controle adicional para gerenciar a parte volátil e não volátil




