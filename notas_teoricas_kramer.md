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



