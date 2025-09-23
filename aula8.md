# Aula sobre protothreads

## Tarefa VS Thread VS Processo
| Característica   | Processo                                                                 | Thread                                                                                  | Tarefa                                                                                          |
|------------------|--------------------------------------------------------------------------|-----------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------|
| **Definição**    | Uma instância autônoma de um programa em execução.                       | A menor unidade de execução dentro de um processo.                                       | Um termo geral, sinônimo de processo ou thread, ou uma unidade de trabalho para threads.         |
| **Recursos**     | Possui seu próprio espaço de memória privado e recursos dedicados.        | Compartilha o espaço de memória e recursos do processo pai.                              | Acessa recursos do processo e/ou thread que a executa.                                          |
| **Custo/Peso**   | **"Pesado"**. Criação e alternância são lentas e consomem mais recursos. | **"Leve"**. Criação e alternância são rápidas e consomem menos recursos.                 | Varia dependendo do contexto. Pode ser leve ou pesada.                                          |
| **Segurança**    | Altamente isolado. Se um processo falha, não afeta outros.               | Menor segurança. Uma falha em uma thread pode afetar todo o processo.                    | Varia dependendo da implementação.                                                              |
| **Exemplo**      | Duas janelas do navegador, cada uma como um processo independente.        | Em um editor de texto, uma thread lida com a digitação e outra salva em segundo plano.   | Em um gerenciador de tarefas, "navegador" pode ser listado como uma tarefa.                     |


## Programação com Threads VS Eventos
- **Sistemas orientados a eventos (Máquinas de Estado Finito - MEF):** Usam uma única pilha, consumindo menos memória. No entanto, o código pode ser difícil de ler, e a manutenção e depuração se tornam complexas à medida que mais estados são adicionados.
- **Modelos baseados em Threads:** Permitem programar de forma estruturada e isolar problemas em tarefas independentes, facilitando a manutenção. A depuração também é mais fácil, pois o histórico das chamadas de função é mantido na pilha. No entanto, cada thread exige sua própria pilha, o que consome muita RAM. Além disso, a interdependência entre threads pode causar bugs difíceis de detectar.

## Protothreads
Protothreads são apresentados como uma técnica de programação intermediária para sistemas embarcados com memória limitada que necessitam de concorrência. Eles são, na verdade, corrotinas cooperativas, implementadas como máquinas de estado por baixo dos panos, mas programadas de forma sequencial, como se fossem threads.

- **Continuações Locais:** A ideia central é que uma função pode retomar sua execução de um ponto específico onde parou. Isso é possível através de macros que convertem o código sequencial em uma máquina de estado usando um comando switch-case.

- **Macro PT_WAIT_UNTIL:** Essa macro é fundamental. Ela permite que uma função "espere" por uma condição ser verdadeira, saindo e sendo chamada novamente mais tarde. Quando a condição é atendida, a execução continua a partir daquele ponto.

- **Vantagens:** Eles combinam o estilo de programação sequencial dos threads com o baixo consumo de memória das máquinas de estado, usando apenas uma pilha. Isso torna a depuração mais fácil e os torna ideais para sistemas em tempo real com recursos limitados.

- **Desvantagens:** Pode ter problemas com interdependências entre tarefas (que nem threads reais).

### Funcionamento da implementação do professor 
- `PT_INIT`: Esta macro é usada para inicializar o estado de um Protothread. Ela deve ser chamada antes da primeira execução da tarefa para garantir que a variável de estado seja configurada para zero. Isso é essencial para que o Protothread inicie corretamente do "estado zero" na primeira vez que a função for chamada.

- `PT_BEGIN`: Esta macro marca o início da função do Protothread. Por baixo dos panos, ela cria uma estrutura switch-case com o valor da variável de estado. Isso faz com que a execução "salte" para o ponto correto da função, permitindo que a tarefa retome exatamente onde parou.

- `PT_END`: Esta macro marca o fim da função do Protothread. Ela finaliza a estrutura switch-case e garante que a função saia de maneira limpa.

- `PT_WAIT_UNTIL`: É a macro que gerencia a continuação. Ela verifica uma condição e, se ela for falsa, o Protothread "pausa" e retorna. O ponto de retorno é salvo como o novo estado. Quando a função for chamada novamente, a execução continuará exatamente a partir daquele ponto. Somente quando a condição for verdadeira, o código avança.


## Duvidas para perguntar sobre essa aula:
1. Registradores de periféricos é um para todo o sistema ou cada thread tem uma cópia espelhando? (Acho que é só 1 para todo sistema, mas quero ter certeza)

2. PC (Program Counter), SP (Stack Pointer) e LR (Link Register) é um por thread? (Acho que cada thread tem 1, mas quero ter certeza)

3. Interdependência seria a comunicação (envio de dados) entre as threads?

4. A comunicação entre protothreads é feita apenas via variaveis globais?

5. Por que `case 0` em `PT_BEGIN`? Sem o `break` no `case 0`, sempre irá cair para o próximo `case`

Daria para fazer algo assim
```
typedef struct
{
    unsigned int lc; 
} Protothread;

#define PT_INIT(pt) \
    (pt)->lc = 0

#define PT_WAIT_UNTIL(pt, c)  \
    (pt)->lc = __LINE__; \
    switch((pt)->lc) { \
    case __LINE__: \
        if(!(c)) return 0; \
    }

#define PT_END(pt) \
    (pt)->lc = 0; \
    return 2
```

No lugar de 
```
typedef struct
{
    unsigned int lc; 
} Protothread;

#define PT_INIT(pt) \
    (pt)->lc = 0

#define PT_BEGIN(pt) \
    switch((pt)->lc) { case 0:

#define PT_WAIT_UNTIL(pt, c)  \
    (pt)->lc = __LINE__; \
    case __LINE__: \
        if(!(c)) return 0

#define PT_END(pt) \
    } \
    (pt)->lc = 0; \
    return 2
```

Eliminando uma macro e um `case`vazio