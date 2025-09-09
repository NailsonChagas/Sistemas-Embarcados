# Recomendações de Escrita de Código

Em sistemas críticos existem regras a serem seguidas que variam de país a país.  
Mas, como regra geral:

- **Precedência de operações**
  - Não confiar em precedência de operações, sempre explicitar com parênteses.

- **Casts**
  - Toda vez que usar *cast*, explicitar o que está sendo assumido.
  - Conversões de ponteiro devem ter *cast* explícito.
    - **Exceção:** em funções com parâmetro `void *`, não é necessário o *cast*.

- **Estruturas de dados**
  - Montar estruturas de dados em vez de passar múltiplos parâmetros para funções.

- **Laços de repetição**
  - Não usar `for`, `while` e `loop` sem `{}`.

- **Constantes**
  - Ponteiros que não modificam o objeto apontado devem ser constantes.
  - Variáveis que não são modificadas devem ser `const`.
  - Exemplos de uso de `const`:
    - `int *p` → ponteiro para `int` (pode modificar valor e endereço).
    - `const int *p` → ponteiro para `int` constante (pode mudar o endereço, mas não o valor apontado).
    - `int const *p` → equivalente ao exemplo acima.
    - `int * const p` → ponteiro constante (não pode mudar o endereço, mas pode mudar o valor apontado).

- **Union**
  - `union` deve ser evitado se o objetivo for portabilidade.  
    - Exemplo de problema: diferenças entre **big endian** e **little endian**.

- **Bitfields**
  - Devem ser documentados.
  - São interessantes para declarar um conjunto de valores que podem ser apenas **verdadeiros** ou **falsos**.

- **Uso do HAL**
  - Algumas empresas não permitem o uso do HAL.

- **Tipos `char`**
  - `char` deve ser usado apenas para caracteres.
  - Se for usado para números, devem ser `signed char` ou `unsigned char`.

- **Funções**
  - Devem ter protótipo.
  - O protótipo deve ser visível tanto na **definição** quanto na **chamada** da função.
    - Isso porque inconsistências entre protótipo e definição geram *warnings*, não erros.

- **Operações bitwise**
  - Só podem ser usadas com variáveis `unsigned`.

- **Uso de `float`**
  - Expressões que usam `float` não devem utilizar operadores de igualdade ou desigualdade (`==`, `!=`, `<=`, `>=`).
  - Apenas comparações `>` ou `<` são permitidas.
  - Sempre identificar quando se trata de `float`:
    - Exemplo: usar `1.5f` em vez de `1.5`.

- **Alocação de memória**
  - Não usar `new` e `delete` em C++.
  - Não usar `malloc`, `realloc` e `free` em C, **a menos que sejam reimplementados**.
    - `malloc` não garante tempo de execução determinístico.
    - Existem formas de alocação determinística, mas não são padrão.

- **Garbage Collector**
  - Não deve ser utilizado.

- **Documentação**
  - Usar documentação automática.

- **Cobertura de código**
  - Sistemas críticos devem ter **100% de cobertura de código (code coverage)**.
