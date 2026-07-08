//Bibliotecas para tela LCD
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configurações do OLED
#define LARGURA_TELA 128
#define ALTURA_TELA 64
#define RESET_TELA -1 
#define ENDERECO_I2C 0x3C // Endereço físico padrão do SSD1306

//Instaciar o objeto Adafruit_SSD1306 (nossa tela) com a variável 'display'.
//Passando 128 largura e 64 de altura, visto que ela é 128x64 pixel
Adafruit_SSD1306 display(LARGURA_TELA, ALTURA_TELA, &Wire, RESET_TELA);

//LDR = sensor de luz.

const int pino_ldr = A1;
float leitura_ldr = 0; //leitura analógica, há valores não inteiros
float tensao_analogica = 0; //para transformar os valores de tensao digital para analogico

const int pino_led = 3;

//Variáveis para estado de controle da interface:
//A ideia é apenas atualizar a tensão e a os dizeres "ligado" e "desligado" ao acontecer a mudança.
bool estadoLED = false;
bool estadoAnteriorLED = false;
bool primeiraExecucao = true; //inicializamos a tela com true.

void setup()
{
  Serial.begin(9600); //define a taxa de transferência serial em bit/s
  pinMode(pino_led, OUTPUT); //o pino do LED é de saída de sinal elétrico

  // Tenta iniciar a comunicação com o chip da tela. Apenas um teste para inicialização
  if(!display.begin(SSD1306_SWITCHCAPVCC, ENDERECO_I2C)) {
    for(;;); // Trava o sistema num loop infinito se houver falha de hardware
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); //WHITE == 1 (ligado), BLACK == 0 (desligado)
  display.setTextSize(1);

  // --- Estrutura Estática da Interface (Desenhada apenas 1 vez) ---
  display.setCursor(15, 0); 
  display.print("Monitor de Tensao"); //sem acento pq a tela não reconhece
  
  display.drawLine(0, 10, 128, 10, SSD1306_WHITE); // Uma linha de design
  
  display.setCursor(0, 25); 
  display.print("Leitura: ");

  display.setCursor(0, 45); 
  display.print("Status: ");

  // Descarrega o frame inicial da RAM para a tela
  display.display();
}

void loop()
{
  leitura_ldr = analogRead(pino_ldr); //função que capta a leitura do pino_ldr (nesse caso, A3)
  tensao_analogica = 5*leitura_ldr/1023;
  Serial.print("Tensao LDR: ");
  Serial.println(tensao_analogica);
  
  //Agora para ligar o led:
  if(tensao_analogica > 2.5){
  	digitalWrite(pino_led, HIGH);
    estadoLED = true;
  }
  else{
    digitalWrite(pino_led, LOW);
    estadoLED = false;
  }

  //Agora, medir a tensão:
  display.setCursor(55, 25); //pula os pixels da palavra "leitura"
  display.print(tensao_analogica);
  display.print("V "); //Com espaço para limpar lixo de memória residual de outros comandos de "display" feitos antes

  //Atualização de "ligado" para "desligado":
  if(estadoLED != estadoAnteriorLED || primeiraExecucao){
    display.setCursor(50, 45);

    if(estadoLED == true){
      display.print("LIGADO   "); //Com 3 espaços para sobrecresver "DESLIGADO" ao ligar.
    }
    else{
      display.print("DESLIGADO");
    }

    estadoAnteriorLED = estadoLED;
    primeiraExecucao = false;
  }

  display.display(); //atualiza o que está no visor.
  delay(150); //150ms para atualizar o que está na tela.
}