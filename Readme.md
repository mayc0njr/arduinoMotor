
# Arduino Analog Motor. - ptBR

Arduino Analog Motor é um controlador que recebe dados seriais (como por exemplo, Bluetooth), e comanda os motores do Arduino de forma a movimentar-se na velocidade e direção desejada, combinando valores analógicos frente/trás, e esquerda/direita.

Todo o desenvolvimento foi feito usando a IDE Arduino (v1.8.2), que inclui todas as ferramentas para compilação e carregamento do código para o Arduino.

# 1. Instalação

Não há muito a se fazer, após baixar o código, execute-o na IDE ou e uma ferramenta de sua escolha, e faça a verificação/carregamento do código para sua placa.

# 1.1. Requisitos

* Arduino/Genuino UNO (Não testado em outras placas).

* Módulo Bluetooth HC-05/HC-06 (Ou outra forma de enviar dados seriais ao arduino).

* [Arduino IDE](https://www.arduino.cc/en/main/software) Testado na versão 1.8.2.


* [Adafruit Motor Shield](https://learn.adafruit.com/adafruit-motor-shield). Também é necessário baixar a biblioteca para a Shield.

<!-- 
* Diferente da maioria dos controladores bluetooth, esta API faz o uso de 2 bytes/caracteres por comando.
As direções (Frente, Trás, Esquerda e Direita), usam "Botão" + "Valor", para guiar os motores. Outras opções como um LED, por exemplo. usam "Botão" + "Estado"(Apertou/Soltou) para acionar alguma porta digital. -->

# 2. Configuração.
A configuração básica é realizada modificando as constantes atribuídas no "cabeçalho" do código.
Elas estão relacionadas aos motores acoplados à shield, e aos comandos recebidos para o controle.


# 2.1. Tabela de Comandos.

| Constante  | Valor Padrão | Comando Relacionado                  |
|:----------:|:------------:|:------------------------------------:|
| FRENTE     | W            | Mover para a frente                  |
| TRÁS       | S            | Mover para trás                      |
| ESQUERDA   | A            | Girar para a esquerda                |
| DIREITA    | D            | Girar para a direita                 |
| BOMBA      | B            | Acionar a hidro bomba de água        |
| NEON       | N            | Acionar o LED ou Neon acoplado.      |
| APERTOU    | P            | Indica que o botão foi pressiionado. |
| SOLTOU     | E            | Indica que o botão foi solto.        |


# 3. Como Usar.

Após a configuração e carregamento do código na placa, basta ligar um dispositivo bluetooth para envio dos dados para o Arduino. Os comandos enviados para o arduino devem estar de acordo com suas configurações. Para simplificar os testes e/ou desenvolvimento, podem ser usados valores padrões para a movimentação, visto que são analógicos.

# 3.1. Tabela de Velocidades.

A tabela abaixo mostra os valores que indicam se o carrinho está Parado, ou na Velocidade Máxima. É importante ressaltar alguns pontos quanto à tabela.

* Os valores a seguir representam um byte. Ou seja, não deve ser enviada a String "255", mas sim, o byte correspondente, usando algum cast, ou caractere de valor equivalente.

* O valor de velocidade deve ser inserido após a direção desejada. Por exemplo: para mover o carrinho
para frente na velocidade máxima, devo enviar os bytes ['W',(byte)255] para o Arduino.

| Valor | Comando Relacionado           |
|:-----:|:-----------------------------:|
| 0     | Pára os motores relacionados  |
| 255   | Velocidade máxima nos motores |

# 4. A Fazer.

* Um aplicativo Android, para simplificar o uso da biblioteca.

* A Adição de novos comandos na biblioteca.

* Otimizar a leitura/entrada de dados recebidos.

* Detecção de queda de rede (requer a conexão do bluetooth na placa em modo mestre).


# Arduino Analog Motor. - enUS

Arduino Analog Motor is a controller that receives serial data (for example, Bluetooth), and control the arduino motors, to move it on the selected speed and direction, combining analog values to move forward/backward, and left/right.

All the development was done using the Arduino IDE (v1.8.2), which includes all the tools for compiling and uploading the code for the Arduino.

# 1. Installation


There is no much to do, after download the code, run it on the IDE, or your preferred tool, and verify/upload the code to your board.

# 1.1. Requirements

* Arduino/Genuino UNO (Not tested on another board).

* Bluetooth Module HC-05/HC-06 (Or another form to send serial data to Arduino).

* [Arduino IDE](https://www.arduino.cc/en/main/software) Tested version 1.8.2.


* [Adafruit Motor Shield](https://learn.adafruit.com/adafruit-motor-shield). You also need to download the library Shield's library.

<!--
* Unlike most bluetooth controllers, this API makes use of 2 bytes / characters per command.
The directions (Front, Back, Left and Right) use "Button" + "Value" to guide the engines. Other options such as an LED, for example. Use "Button" + "Status" (pressed / released) to trigger any digital ports. -->

# 2. Configuration.
The basic config is done by  modifying the constants assigned in the "header" of the code.
They are related to the motors attached to the shield, and the commands received for the control.
If you're using a bomb, and led, you need to set the digital port respectively for the constants "BOMBA", e "NEON".


# 2.1. Commands Table.

| Constant | Default Value | Related Command                |
|:--------:|:------------:|:-------------------------------:|
| FRENTE   | W            | Move Forward                    |
| TRÁS     | S            | Move Backward                   |
| ESQUERDA | A            | Turn Left                       |
| DIREITA  | D            | Turn Right                      |
| BOMBA    | B            | Trigger the Hydro Pump.         |
| NEON     | N            | Trigger o LED ou Neon attached. |
| APERTOU  | P            | Indicates button press.         |
| SOLTOU   | E            | Indicates button release.       |


# 3. Usage.

After the config and upload code to the board, you need to connect a bluetooth device, to send the data to the board. The commands send to the board, must conform to your settings. To simplify test/development, you can use simple values to movement, since they are analog.

# 3.1. Speed Table.

This table show values that indicates command to stop, or full speed. 
A tabela abaixo mostra os valores que indicam se o carrinho está Parado, ou na Velocidade Máxima. It is important to highlight some points regarding the table.

* The values below, represents a BYTE. That is, you should not send the String "255" to full speed, but the byte/char correspondent to it.

* The speed value should be send after the selected direction. Example: To move forward with full speed,
snd the bytes ['W', (byte)255] to the board.
| Value | Related Command               |
|:-----:|:-----------------------------:|
| 0     | Stop the related motors.      |
| 255   | Set the full speed to motors. |

# 4. TODO.

* An Android app, to simplify the library use, and command.

* Adding new commands to the library.

* Optimize the data input and treatment.

* Detect connection loss. (needs the bluetooth module to be connected on the board as master).