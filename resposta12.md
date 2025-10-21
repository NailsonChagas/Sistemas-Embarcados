0.01A a 1.2A 

1AQn

      3V - 4095
1A -> 1V - 1365

1AQ12 -> 1*2^12 == 4096

4096/1365 == 3.00073 -> Fator de conversão quase totalmente inteiro -> da para usar

Refazer por que não levei em conta que a corrente pode ser negativa

como é de 0 a 3, a referencia é 0 a 100%, logo a referencia já vai estar em Q12 saindo do AD