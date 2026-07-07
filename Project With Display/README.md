# Adicionando um display (mini tela OLED) no projeto
Infelizmente, não será possível demonstrar essa parte no simulador, dado a diferença entre a tela aqui usada e a tela disponível no [Thinkercad](https://www.tinkercad.com/dashboard).
Vamos adicionar uma tela no projeto do LDR. A mini tela terá a função de monitorar a tensão (aquela que é mostrada pelo multímetro do [Thinkercad](https://www.tinkercad.com/dashboard)) e mostrar se o LED está ligado ou desligado, de forma escrita.

- O modelo da tela é um [módulo de tela OLED](https://pt.aliexpress.com/item/1005007551771400.html?spm=a2g0o.order_list.order_list_main.35.1b61caa4XXkVZo&gatewayAdapt=glo2bra) de quase 0,96 polegadas. É um módulo de exibição IIC OLED I2C azul de 128x64 pixel SSD1306 Mini.
- Nela, temos 4 entradas: GND, VCC, SCL e SDA.