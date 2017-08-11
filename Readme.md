
# Arduino Analog Motor.

Arduino Analog Motor é um controlador que recebe dados seriais (como por exemplo, Bluetooth), e comanda os motores do Arduino de forma a movimentar-se na velocidade desejada, combinando valores analógicos frente/trás, e esquerda/direita.

Todo o desenvolvimento foi feito usando a IDE Arduino (v1.8.2), que inclui todas as ferramentas para compilação e carregamento do código para o Arduino.

# 1. Instalação

Não há muito a se fazer, após baixar o código, execute-o na IDE ou e uma ferramenta de sua escolha, e faça a verificação/carregamento do código para o Arduino.

# 1.1. Requisitos

* Arduino/Genuino UNO (Não testado em outras placas).

* Módulo Bluetooth HC-05/HC06 (Ou outra forma de enviar dados seriais ao arduino).

* [Arduino IDE](https://www.arduino.cc/en/main/software) Testado na versão 1.8.2.


* [Adafruit Motor Shield](https://learn.adafruit.com/adafruit-motor-shield). Também é necessário baixar a biblioteca para a Shield.

<!-- 
* Diferente da maioria dos controladores bluetooth, esta API faz o uso de 2 bytes/caracteres por comando.
As direções (Frente, Trás, Esquerda e Direita), usam "Botão" + "Valor", para guiar os motores. Outras opções como um LED, por exemplo. usam "Botão" + "Estado"(Apertou/Soltou) para acionar alguma porta digital. -->

# 2. Configuração.
A configuração básica é realizada modificando as constantes atribuídas no "cabeçalho" do código.
Elas estão relacionadas aos motores acoplados à shield, e aos comandos recebidos para o controle.


# 2.1. Tabela de Comandos.

| Comando  | Valor Padrão | Comando Relacionado                  |
|:--------:|:------------:|:------------------------------------:|
| FRENTE   | W            | Mover o carro para a frente          |
| TRÁS     | S            | Mover o carro para trás              |
| ESQUERDA | A            | Girar o carro para a esquerda        |
| DIREITA  | D            | Girar o carro para a direita         |
| BOMBA    | B            | Acionar a bomba de água              |
| NEON     | N            | Acionar o LED ou Neon acoplado.      |
| APERTOU  | P            | Indica que o botão foi pressiionado. |
| SOLTOU   | E            | Indica que o botão foi solto.        |


# 3. Como Usar.

Após a configuração e carregamento do código na placa, basta ligar um dispositivo bluetooth para envio dos dados para o Arduino. (Um aplicativo Android está em desenvolvimento para simplificar o procedimento). Os comandos enviados para o arduino devem estar de acordo com suas configurações. Para simplificar os testes e/ou desenvolvimento, podem ser usados valores padrões para a movimentação, visto que são analógicos.

# 3.1. Tabela de Velocidades.

A tabela abaixo mostra os valores que indicam se o carrinho está Parado, ou na Velocidade Máxima. É importante ressaltar alguns pontos quanto à tabela.

* Os valores a seguir representam um byte. Ou seja, não deve ser enviada a String "255", mas sim, o byte correspondente, usando algum cast, ou caractere de valor equivalente.

* O valor de velocidade deve ser inserido após a direção desejada. Por exemplo: para mover o carrinho
para frente, na velocidade máxima. devo enviar os bytes ['W',(byte)255] para o Arduino.

| Valor Padrão   | Comando Relacionado                   |
|:--------------:|:-------------------------------------:|
| 0              | Para os motores relacionados          |
| 255            | Velocidade máxima nos motores         |

# 4. A Fazer.

* Um aplicativo Android, para simplificar o uso da biblioteca.

* A Adição de novos comandos na biblioteca.

* Otimizar a leitura/entrada de dados recebidos.

* Detecção de queda de rede (requer conexão em modo mestre).