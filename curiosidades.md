variaveis globais são iniciadas com tudo 0 e locais com lixo de memória (ver data e bss para a explicação)

bootloader: programa que inicia antes do firmware para carregar o firmware (ver vantagens e desvantagens)

PT_SPAW: para um função que usa a api da protothread precisa usar outra função deve ser chamado o PT_SPAW

*pt-- = alguma coisa : decrementa o endereço e o popula com alguma coisa 

Se um 1ms é usado como menor resolução de tempo, a cada 1ms entra em uma interrupção. Usar um micro segundo não funcionaria pois a cada micro segundo ele teria que empilar e desempilhar a pilha o que leva micro segundos tbm, não sobrando tempo para usar o processador

volatile: uma variavel momento é uma variavel que pode mudar a qualquer momento (ex: variaveis usadas por uma interrupção, registradores). Todas variaveis de um OS são volateis -> procurar melhor como funciona

hard fault -> o que é (estouro de pilha, erro de acesso a memória, erro de DMA)

1) O que siginifica statical e volatil para variavel global, local e funções?
Volatil não muda nada ser global e local
Não exstem funções volateis

