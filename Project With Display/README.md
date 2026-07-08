# Adicionando um display (mini tela OLED) no projeto
Infelizmente, não será possível demonstrar essa parte no simulador, dado a diferença entre a tela aqui usada e a tela disponível no [Thinkercad](https://www.tinkercad.com/dashboard).
Vamos adicionar uma tela no projeto do LDR. A mini tela terá a função de monitorar a tensão (aquela que é mostrada pelo multímetro do [Thinkercad](https://www.tinkercad.com/dashboard)) e mostrar se o LED está ligado ou desligado, de forma escrita.

## Hardware: conectando a tela OLED ao projeto
- O modelo da tela é um [módulo de tela OLED](https://pt.aliexpress.com/item/1005007551771400.html?spm=a2g0o.order_list.order_list_main.35.1b61caa4XXkVZo&gatewayAdapt=glo2bra) de quase 0,96 polegadas. É um módulo de exibição IIC OLED I2C azul de 128x64 pixel SSD1306 Mini.
- Nela, temos 4 entradas: GND, VCC, SCL e SDA.

![display](Imagens/display.jpeg)

1. O GND vai conectado a trilha GND advinda do Arduino.
2. O VCC é por onde o display é energizado. Ele recebe os 5V do Arduino.
3. O SCL (Serial Clock) é a sincronização de dados do display. No Arduino, o pino analógico A5 é a linha de clock para sincronizar dados. Portanto, o SCL deve ser conectado ao pino A5.
4. O SDA (Serial Data)deve ser conectado ao pino analógico A4 do Arduino. É por meio dela que os dados de imagem trafegam entre o display (SDA) e o Arduino (pino A4).

- Como a tela é diferente da usada no Thinkercad, deixo a imagem da conexão no circuito físico:

![displayFios](Imagens/fios_no_display.jpeg)

![arduinoFios](Imagens/fios_no_arduino.jpeg)

Repare nas cores. O fio azul está conectado ao SDL e ao pino A5, enquanto o fio branco está conectado ao SDA e ao pino A4.

## Software: explicações sobre programar a tela
- De início, vamos precisar instalar algumas bibliotecas específicas para esse modelo de tela, para que o código compile e o microcontrolador consiga renderizar os gráficos. Elas podem ser instaladas através da Arduino IDE.
- As bibliotecas que serão usadas:

1. ``<Wire.h>`` é uma biblioteca interna padrão do Arduino que gerencia o hardware de comunicação I2C. É ela que é responsável por trafegar os dados através dos pinos A4 (SDA) e A5 (SCL).
2. ``<Adafruit_GFX.h>`` (externa). Deve ser instalada. É uma biblioteca de processamento gráfico universal. Ela possui as rotinas matemáticas para desenhar pixels, linhas, círculos e escrever textos na memória.
3. ``<Adafruit_SSD1306.h>`` (externa). Deve ser instalada. É a biblioteca específica para a tela utilizada, que traduz os comandos visuais de ``<Adafruit_GFX.h>`` em sinais que o controlador SSD1306 entende.

- Para instalá-las, basta ir em 'Sketch' -> 'Include Library' -> 'Manage Libraries' e pesquisar as bibliotecas externas necessárias.

![pesquisaBibliotecas1](Imagens/pesquisando_bibliotecas1.png)

![pesquisaBibliotecas2](Imagens/pesquisando_bibliotecas2.png)

### Explicações sobre o código
- Vamos fazer algumas definições:

1. ``LARGURA_TELA 128`` e ``ALTURA_TELA 64``: Definem a matriz de pixels. Essa informação dita o tamanho do buffer (1024 bytes) que será alocado na memória SRAM do microcontrolador.
2. ``RESET_TELA -1``: Como a tela não possui botão de reset físico, o valor -1 é usado para reset lógico via software.
3. ``ENDERECO_I2C 0x3C``: É o endereço hexadecimal padrão do chip SSD1306 no barramento I2C. O Arduino usa esse endereço para garantir que os dados de vídeo cheguem ao dispositivo correto.
4. Instanciação do objeto: o objeto global ``Adafruit_SSD1306`` será instanciado, passando os parâmetros definidos anteriormente. Dessa forma, temos: ``Adafruit_SSD1306 display(LARGURA_TELA, ALTURA_TELA, &Wire, RESET_TELA);``, sendo ``display`` o nome que demos ao objeto. Dessa forma, alocamos o buffer de memória e passamos o ponteiro ``&Wire`` para o objeto, concendendo a tela o acesso direto ao hardware I2C do Arduino.
5. Trava de segurança: dentro de ``setup()``, temos uma trava de segurança utilizando o comando ``SSD1306_SWITCHCAPVCC``, que liga o conversor de tensão interno da tela. Se o Arduino não receber uma resposta do endereço I2C (0x3C), isso indica uma falha de hardware (ou de conexão/fiação). Fazemos então um código que entra em loop infinito caso isso aconteça, travando o sistema de continuar executando o código em um hardware defeituoso.
```
if(!display.begin(SSD1306_SWITCHCAPVCC, ENDERECO_I2C)){
    for(;;);
}
```
6. A lógica de atualização: telas OLED não recebem comandos diretos de caracteres como os LCDs tradicionais. Todo o desenho é feito em um vetor na memória RAM e "mandado" para o vidro da tela.
- Usamos ``display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);``. Ao definir a cor de fundo preta junto com o texto branco, os novos caracteres sobrescrevem os bits antigos diretamente no buffer de memória. Isso elimina a necessidade de usar ``display.clearDisplay()`` a cada leitura do sensor.
- O sistema monitora variáveis de estado (``estadoAtualLed`` e ``estadoAnteriorLed``). A string de status ("LIGADO" ou "DESLIGADO") só é reescrita na memória se houver uma mudança real de hardware, economizando ciclos de processamento.
- ``display.display()``: O único momento em que a comunicação I2C realmente acontece. No final do loop principal, este comando despacha os 1024 bytes de vídeo armazenados na RAM para o hardware do display, atualizando os pixels visíveis.

### Código Final
- Veja os arquivos de código. Apenas foi adicionado essa parte da tela no código original do projeto. Colocá-lo aqui tornaria essa seção muito grande.

## Vídeo do projeto com a tela OLED
O objeto que usei no vídeo é apenas para tampar o LDR e mostrar a tela em funcionamento.

![telaOLED](Gifs/tela_oled.gif)