# Respostas da Lista

## 1. Definição de Sistema e Sistema Embarcado

**Sistema**: É uma combinação de componentes que atuam para desempenhar uma função.

**Diferenciação**: Um sistema embarcado é um sistema de computação dedicado a executar funções específicas dentro de um dispositivo maior, diferindo de sistemas genéricos por seu propósito especializado.

**Características desejadas em sistemas embarcados**:
- Requisitos de desempenho específicos
- Baixo consumo de energia
- Custo otimizado
- Alta confiabilidade
- Eficiência computacional
- Tamanho reduzido (quando aplicável)
- Tempo real (em muitos casos)

## 2. Arquiteturas RISC vs CISC

**Principais diferenças**:

| **RISC** | **CISC** |
|----------|----------|
| Instruções de mesmo tamanho | Instruções de tamanho variável |
| Instruções simples | Instruções complexas |
| Execução mais eficiente | Pode demandar mais ciclos de clock |
| Pipeline mais eficiente | Pipeline menos eficiente |
| Programas geralmente maiores | Programas geralmente menores |

**Impacto no conjunto de instruções**:
- RISC: Conjunto reduzido de instruções simples e padronizadas
- CISC: Conjunto amplo de instruções complexas e especializadas
- Tendência atual: Processadores híbridos que combinam características de ambas arquiteturas

## 3. Operação "A = *B" em Assembly RISC

```assembly
LDR R0, [R1]    @ A = *B
```

*Onde:*
- `R1` contém o endereço de B (ponteiro)
- `R0` receberá o valor apontado por R1 (conteúdo de B)

## 4. Passagem de Parâmetros

### a) Processador RISC com 16 registradores (R0-R15)
```
a → R0
b → R1
c (ponteiro) → R2
```

### b) Processador com registradores específicos (D0-D7 e A0-A7)
```
a → D0
b → D1
c (ponteiro) → A0
```

### c) Processador HCS08 (um acumulador e registrador de índice)
**Passagem via pilha** - os parâmetros seriam empilhados na seguinte ordem:
1. Endereço do ponteiro c
2. Valor de b
3. Valor de a

*A função processa desempilharia esses valores na ordem inversa para acessar os parâmetros.*