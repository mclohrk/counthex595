//Constantes associadas aos pinos do arduino
int const clockPin = 7; //ligado ao clock do 74HC595
int const latchPin = 2; //ligado ao latch do 74HC595
int const dataPin  = 4; //ligado ao data do 74HC595
int setDisplay[16] = {126,12,182,158,204,218,250,14,254,206,238,248,114,188,242,226};
int inPin = 8; //pino de entrada para interruptor
int estadoBotao = 0; //Ler o estado do botão
int divisao;
int resto;
int parada = 255;

byte  TAM_MAX  =255; //tamanho maximo do contador vetor
byte  TAM_ATUAL  =0;
byte botao= 10;
byte var=0;
byte var2=0;
byte botao2=11;
byte led =12;
byte parar=0;
int times = 0;
int qtdAperto = 0;
int i=0;

void reset(){

  var=digitalRead(botao); // ler o valor enviado pelo botão: "HIGH" ou "LOW"
  /* pega valor do botao e compara com HIGH,
  caso true ele igual a o contador i forçando a sair do laço, reiniciando  */
  if (var == HIGH){
  i= parada;
  digitalWrite(led, HIGH); // liga o led
  delay(500);
  digitalWrite(led, LOW); // desliga o led

   }

}
void setup() {
  //definindo os pinos como de saída
  pinMode(clockPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  //Botão definido como de entrada
  pinMode(inPin,INPUT);
   pinMode (led,OUTPUT);
}

void loop() {


  //Contando de 0 até 255
  for (int i = 0; i <= parada; i++) {


  var=digitalRead(botao); // ler o valor enviado pelo botão: "HIGH" ou "LOW"
  var2=digitalRead(botao2);
  /* pega valor do botao e compara com HIGH,
  caso true ele igual a o contador i forçando a sair do laço, reiniciando  */

  if (var == HIGH){
      qtdAperto++;
  }

  if(qtdAperto >= 3)
    {
      i= parada;
      digitalWrite(led, HIGH); // liga o led
      delay(250);
      digitalWrite(led, LOW); // desliga o led
      times = 0;
      qtdAperto = 0;
}

  if (times >= 30)
  {
      times = 0;
      qtdAperto = 0;
      if(var2 == HIGH)
        {
            i= parada;
            digitalWrite(led, HIGH); // liga o led
            delay(250);
            digitalWrite(led, LOW); // desliga o led
        }
        continue;
  }

  if(qtdAperto != 0 || var2 == HIGH)
  {
      times++;
  }

    divisao = i/16;
    resto = i%16;

    //permite o fluxo dos dados.
    digitalWrite(latchPin,LOW);

    for (int x = 0; x <= 7; x++) {

      //pronto para receber o bit.
      digitalWrite(clockPin,LOW);

      if (setDisplay[resto] & (1 << x)) {
        digitalWrite(dataPin,LOW);
      } else {
        digitalWrite(dataPin,HIGH);
      }

      //grava o bit recebido.
      digitalWrite(clockPin,HIGH);

    }
    for (int x = 0; x <= 7; x++) {

      //pronto para receber o bit.
      digitalWrite(clockPin,LOW);

      if (setDisplay[divisao] & (1 << x)) {
        digitalWrite(dataPin,LOW);
      } else {
        digitalWrite(dataPin,HIGH);
      }

      //grava o bit recebido.
      digitalWrite(clockPin,HIGH);
    }

    //finaliza o fluxo dos dados e envia os 8 bits.
    digitalWrite(latchPin,HIGH);

    //tempo de espera entre a exibição de um
    //número e o outro.

    estadoBotao = digitalRead(inPin);
    if(estadoBotao==LOW){
      digitalWrite(dataPin, LOW);
      digitalWrite(latchPin, LOW);
      digitalWrite(clockPin, LOW);

    }
    delay(100);

  }

  }
