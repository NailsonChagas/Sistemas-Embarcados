# Programação Concorrente

Segundo o professor, usar o Linux para programação embarcada não difere muito da programação para PC, embora por enquanto não estejamos focando em Linux especificamente.

## Sistemas em Tempo Real

Sistemas em tempo real são sistemas que trabalham sob restrições temporais rigorosas:
- Tempo real não implica necessariamente velocidade, mas sim **previsibilidade**
- O conceito de previsibilidade é crucial em aplicações como:
    - Telefonia
    - Freio ABS
    - Vidros elétricos automotivos

## Conceitos Fundamentais

- **Deadline**: Tempo máximo permitido para tratar um evento
- **Latência**: Tempo que efetivamente leva para tratar um evento (deve ser previsível para conhecermos o pior caso)
- **Jitter**: Variação da latência (não é possível eliminar completamente, apenas minimizar)
- **Determinismo**: Capacidade de processar eventos dentro de um período determinado

## Classificação de Sistemas de Tempo Real

- **Soft Real Time**: Podem funcionar corretamente mesmo quando algumas restrições temporais não são respeitadas (ex: vidro elétrico de carro, player de áudio)
- **Hard Real Time**: Devem seguir rigorosamente as restrições de tempo para evitar consequências catastróficas (ex: sistemas de controle de avião, freio ABS, mísseis)

A maioria dos sistemas combina elementos soft e hard, onde componentes críticos são hard real time e outros podem ser soft real time.

## Arquitetura de Sistemas

Sistemas de baixa complexidade geralmente usam a abordagem de **superlaço** (foreground/background/baremetal):
- Programa principal em loop de repetição
- Interrupções tratam eventos assíncronos
- **Evento assíncrono**: Não pode ser previsto (não depende do código executado no momento)
- **Evento síncrono**: Pode ser previsto (depende do código executado no momento)

## Problemas Comuns em Abordagens Iniciais

Iniciantes frequentemente colocam código crítico em interrupções para priorização, mas isso causa problemas:
- Muito código na interrupção aumenta sua duração
- Interrupções podem ser perdidas se outra ocorrer durante a execução

## Sistemas Operacionais

Sistemas operacionais podem ser vistos de duas perspectivas:
- **Top-down**: Função de abstrair o hardware
- **Bottom-up**: Operam como gerenciadores de recursos

### Funções Básicas de um SO
- Gerenciamento de tempo e recursos da CPU
- Gerenciamento de tarefas
- Gerenciamento de memória (alocação dinâmica em tempo de execução)
- Gerenciamento de periféricos
- Fornecimento de funcionalidades adicionais (sistema de arquivos, protocolos de rede, etc.)

### Linux Embarcado
- Kernel modular (não monolítico)
- Compilação personalizada para incluir apenas o necessário
- Requer mais RAM pois não executa código diretamente da flash

### Motivações para Usar SO
- Padronização e reuso de código (drivers para Ethernet, USB, wireless, UARTs, etc.)
- Sincronização de periféricos com tarefas
- Diferenciação de prioridades de execução
- Multi-tarefa

## RTOS (Real-Time Operating Systems)

### Cenários de Uso
- Múltiplas tarefas com diferentes intervalos de execução
- Necessidade de atividades "simultâneas" (multi-tarefa)

### Tipos de Núcleo RTOS

#### **Cooperativo**
- Tarefas devem liberar explicitamente o controle da CPU
- Baixa latência em interrupções
- Permite uso de funções não reentrantes
- Tempo de resposta limitado pela tarefa mais lenta
- Menor preocupação com recursos compartilhados
- Tarefas de alta prioridade podem esperar por tarefas de menor prioridade

#### **Preemptivo** (ex: escalonamento Round-robin)
- Tarefas de maior prioridade interrompem as de menor prioridade
- Tempo de execução deterministico para tarefas de alta prioridade
- Requer cuidado com funções reentrantes
- Overhead de 1 a 5% da CPU
- Consome espaço adicional de RAM e código

### Conceitos de Execução

- **Função reentrante**: Múltiplas tarefas podem executar a mesma função sem corromper dados
- **Função não reentrante**: Múltiplas tarefas executando a mesma função podem corromper dados (ex: malloc, realloc, free)

### Diferenças entre Tarefa, Thread e Processo

- **Tarefa**: Em RTOS, equivalente a uma thread mas sem associação a um processo. Cada tarefa tem sua própria pilha. Comunicação entre tarefas é permitida diretamente.
- **Thread**: Unidade básica de execução com pilha, contador de programa (PC) e registradores próprios. Custo principal é memória.
- **Processo**: Contêiner que agrupa uma ou mais threads, com espaço de endereçamento próprio e recursos isolados.

A principal diferença entre **tarefa** (em RTOS) e **thread** é que tarefas não estão associadas a processos e geralmente compartilham o mesmo espaço de endereçamento, simplificando a comunicação mas requerendo cuidado com concorrência.

É possivel limitar acesso endereços de memória usando uma MMU