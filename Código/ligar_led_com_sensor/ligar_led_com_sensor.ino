//LDR = sensor de luz.

const int pino_ldr = A3;
float leitura_ldr = 0; //leitura analógica, há valores não inteiros
float tensao_analogica = 0; //para transformar os valores de tensao digital para analogico

const int pino_led = 3;

void setup()
{
  Serial.begin(9600); //define a taxa de transferência serial em bit/s
  pinMode(pino_led, OUTPUT); //o pino do LED é de saída de sinal elétrico
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
  }
  else{
    digitalWrite(pino_led, LOW);
  }
}