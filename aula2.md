# Mapa de Memória

Na arquitetura ARM, existe apenas um espaço de memória **endereçável até 4 GB (32 bits)**. Esse espaço único é dividido em três principais seções:

* **I/O Registers**: Área dedicada para os registradores de periféricos. O tamanho varia conforme o número de pinos e periféricos suportados pelo chip.
* **SRAM**: Memória de acesso rápido usada para variáveis de dados e pilha (*stack*). É diretamente acessada pelas instruções do microcontrolador.
* **Flash ROM**: Memória não volátil destinada ao armazenamento do programa. Também pode armazenar dados estáticos, como *look-up tables* e *strings*.

---

# SRAM

A memória **SRAM** é subdividida em regiões específicas para diferentes finalidades:

### Stack

O **Stack** é uma região de memória usada para armazenar dados temporários, como:

* variáveis locais;
* parâmetros de funções;
* valores de registradores durante chamadas de função.

Características:

* Cresce **de endereços altos para endereços baixos**.
* Gerenciado automaticamente pelo compilador e pelo processador via **SP (Stack Pointer)**.
* Manipulado em assembly ARM com instruções como `PUSH` e `POP`.

---

### Heap

O **Heap** é a região usada para **alocação dinâmica de memória em tempo de execução**.

Características:

* Cresce **de endereços baixos para endereços altos**.
* Controlado explicitamente pelo programador (ex.: `malloc` / `free`).
* Uso deve ser cauteloso em sistemas embarcados devido à **memória limitada**.

---

### Segmentos de Memória da SRAM

* **Endereço 0**

  1. **.data** → Variáveis globais inicializadas (tamanho fixo).
  2. **.bss** → Variáveis globais não inicializadas (tamanho fixo).
  3. **Heap** → Área de alocação dinâmica.
  4. **Memória livre** → Espaço entre Heap e Stack, usado como área de expansão.
  5. **Stack** → Variáveis locais, parâmetros e registradores de contexto.

* **Final da memória**

---

### Observações Importantes

* **Stack** e **Heap** crescem em **direções opostas**.
* Os limites máximos podem ser configurados no **arquivo de *linker***.
* A região **livre entre Stack e Heap** serve como **buffer de expansão**.

---

# Organização de Dados na Memória

### Endianness (Little Endian vs Big Endian)

* **Little Endian**: O **byte menos significativo (LSB)** é armazenado no endereço mais baixo.
* **Big Endian**: O **byte mais significativo (MSB)** é armazenado no endereço mais baixo.

🔹 **Por que é importante?**

* Protocolos de comunicação podem transmitir os bytes em uma ordem diferente da usada pelo processador.
* Saber o *endianness* evita erros na interpretação de dados ao enviar/receber informações entre dispositivos heterogêneos.

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
