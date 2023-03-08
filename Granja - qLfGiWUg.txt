// Laboratorio J011y R0g3r
// ta na hora de pensar num nome serio pra esse Laboratorio :D
// Código para controle de temperatura em aviário. Define uma temperatura-base (padrão é 28 graus),
// que pode ser alterado e visualizado num display, assim como a temperatura do ambiente.
// 1 grau abaixo da temperatura-base, liga um relay que aciona a primeira linha de ventiladores.
// Acima da temperatura-base, aciona a segunda linha de ventiladores.
// 2 graus acima da temperatura-base, aciona a bomba de aspersão de água.
// Um botão simples permite acionar manualmente a bomba.
//
// Apoio: Laboratorio de Garagem - labdegaragem.com
// Agradecimentos a valiosa ajuda dos amigos:
// Almir, Jonatas, Jucelei, Rogerio, Euclides, Marcelo, Renyer, fredsant,Yure, (esqueci alguem???)
// alem da tremenda paciencia da minha esposa pra me aguentar falando nisso dia e noite :D

int LATCH1 = 2;
int DATA1 = 3;
int CLK1 = 4;
// define os pinos de latch, data e clock do 74HC595 que controla o display da temperatura do ambiente

int LATCH2 = 5;
int DATA2 = 6;
int CLK2 = 7;
// define os pinos de latch, data e clock do 74HC595 que controla o display da temperatura definida como base

// latch: pino 12 no 74hc595
// data: pino 14 no 74hc595
// clock: pino 11 no 74hc595
// ver datasheet (boa sorte!)

int desce = 8;
// pino do botao que reduz a temperatura-base em meio grau
int sobe = 9;
// pino do botao que aumenta a temperatura-base em meio grau
int agua = 10;
// pino do botao que liga a bomba dos aspersores de agua, independente da temperatura
int vent1 = 13;
// pino que liga a primeira linha de ventiladores, quando (temperatura >= (tempbase - 1 grau)) E (temperatura < tempbase)
int vent2 = 12;
// pino que liga a segunda linha de ventiladores, quando (temperatura >= tempbase) E (temperatura <= (tempbase + 1 grau))
int bomba = 11;
// pino que liga a bomba dos aspersores, quando temperatura > (tempbase + 1 grau)
int tempbase=280;
// temperatura-base, notem que estou trabalhando com 10x a temperatura real
// para facilitar a codificacao dos displays de 7 segmentos, que so trabalha com numeros binarios e inteiros

int sensor = A0;

// Renyer, essa eh a parada de matrizes que eu queria te mostrar, usando o tipo byte:
byte digito1[10]= {
  B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11110110};
byte digito2[10]= {
  B11111101,B01100001,B11011011,B11110011,B01100111,B10110111,B10111111,B11100001,B11111111,B11110111};
byte digito3[10]= {
  B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11110110};
byte digito4[10]= {
  B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11110110};
byte digito5[10]= {
  B11111101,B01100001,B11011011,B11110011,B01100111,B10110111,B10111111,B11100001,B11111111,B11110111};
byte digito6[10]= {
  B11111100,B01100000,B11011010,B11110010,B01100110,B10110110,B10111110,B11100000,B11111110,B11110110};
// matrizes de 10 termos, cada um define um Byte diferente para cada
// digito de 0 a 9 no display, ou seja, liga um conjunto especifico de portas do 74hc595
// que acende um conjunto especifico de LEDs.

void setup()
{
  Serial.begin(9600);

  pinMode(A0, INPUT);

  pinMode(LATCH1, OUTPUT);
  pinMode(CLK1, OUTPUT);
  pinMode(DATA1, OUTPUT);

  pinMode(LATCH2, OUTPUT);
  pinMode(CLK2, OUTPUT);
  pinMode(DATA2, OUTPUT);  

  pinMode(desce, INPUT);
  pinMode(sobe, INPUT);
  pinMode(agua, INPUT);

  pinMode(vent1, OUTPUT);
  pinMode(vent2, OUTPUT);
  pinMode(bomba, OUTPUT);  

}

void loop()
{
  int t=1000;
  long intervalo = 5000;
  long previousMillis = millis();
  //rever onde fica e quantos milisegundos dura.

  int value = analogRead(sensor);
  float millivolts = (value / 1024.0) * 5000;
  float temperatura = millivolts / 8.97; //sensor output is 10mV per degree Celsius.
  float celsius = millivolts / 10; // sensor output is 10mV per Serial.print(celsius);
  Serial.print("Temperatura = ");
  Serial.print(temperatura);
  Serial.println(" graus Celsius.");

  int unidade1;
  int dezena1;
  int centena1;

  int unidade2;
  int dezena2;
  int centena2;

  {
    {
      int displaytemp = (10*temperatura);
      // trabalhando com 10x a temperatura pra facilitar com o display de 7 segmentos.

      // Esse eh a dica do Almir e do Jucelei que fechou minhas duvidas:
      // Eu tava quebrando a cabeca naquele dia mas tava cansado demais pra deduzir uma coisa tao simples:
      //separar digitos tempbase exemplo: 285
      centena1 = (displaytemp/100);
      //285/100=2 apenas o numero inteiro é captado  
      dezena1 = ((displaytemp - (centena1*100)) / 10);
      //285-(2*100)/10 ou seja,285-200 (=85/10=8,5) apenas 8 é jogado no inteiro
      unidade1 = displaytemp - ((100*centena1) + (10*dezena1));
      // 285-(200+80) ou (285 - 280) = 5  
      //Essa e a dica do Jonatas:
      digitalWrite(LATCH1, LOW);
      shiftOut(DATA1, CLK1, LSBFIRST, digito1[centena1]); //primeiro CI recebe 1 Byte
      shiftOut(DATA1, CLK1, LSBFIRST, digito2[dezena1]);  //segundo CI recebe 1 Byte
      shiftOut(DATA1, CLK1, LSBFIRST, digito3[unidade1]); //terceiro CI recebe 1 Byte
      digitalWrite(LATCH1, HIGH);
      delay(t);
      // Depois de fritar muito o cerebro que percebi como funciona o esquema de latch-clock-data.
      // Na animacao que o Jonatas me mostrou parecia que o bit enviado pelo Arduino para o 74hc595
      // deslocava-se da primeira porta ate a ultima: Q1, Q2, ... Q8.
      // Mas quem se desloca eh o CI que recebe o Byte: a cada vez que o clock muda de estado ( 0 || 1 ),
      // o CI transfere o endereco de recebimento para o proximo CI da fila.
      // O PCF-8574A tem 3 bits (000 a 111) que definem qual o endereco de cada CI.
      // Ja no 74HC595, o proximo endereco eh definido pela ligacao entre os pinos 9 e 14.
      // O proximo CI eh aquele cujo pino 14 estiver ligado ao pino 9 do CI que acabou de receber o Byte.
      // Facil, neh? ;
    }

    {
      centena2 = (tempbase/100);
      dezena2 = ((tempbase - (centena2*100)) / 10);
      unidade2 = tempbase - ((100*centena2) + (10*dezena2));
      digitalWrite(LATCH2, LOW);
      shiftOut(DATA2, CLK2, LSBFIRST, digito4[centena2]); // escreve a centena no display
      shiftOut(DATA2, CLK2, LSBFIRST, digito5[dezena2]); // escreve a dezena no display
      shiftOut(DATA2, CLK2, LSBFIRST, digito6[unidade2]); // escreve a unidade no display
      digitalWrite(LATCH2, HIGH);
      delay(t);
    }
    {
      while(abs(millis()) - previousMillis < intervalo)
      {   
        if ((digitalRead(sobe) == HIGH) && (tempbase!=0))
        {
          tempbase = tempbase + 5;
          centena2 = (tempbase/100);
          dezena2 = ((tempbase - (centena2*100)) / 10);
          unidade2 = tempbase - ((100*centena2) + (10*dezena2));
          digitalWrite(LATCH2, LOW);
          shiftOut(DATA2, CLK2, LSBFIRST, digito4[centena2]);
          shiftOut(DATA2, CLK2, LSBFIRST, digito5[dezena2]);
          shiftOut(DATA2, CLK2, LSBFIRST, digito6[unidade2]);
          digitalWrite(LATCH2, HIGH);
          delay(t);
        }

        if ((digitalRead(desce) == HIGH) && (tempbase!=0))
        {
          tempbase = tempbase - 5;
          centena2=(tempbase/100);
          dezena2=((tempbase-(centena2*100))/10);
          unidade2=tempbase-((100*centena2) + (10*dezena2));
          digitalWrite(LATCH2, LOW);
          shiftOut(DATA2, CLK2, LSBFIRST, digito4[centena2]);
          shiftOut(DATA2, CLK2, LSBFIRST, digito5[dezena2]);
          shiftOut(DATA2, CLK2, LSBFIRST, digito6[unidade2]);
          digitalWrite(LATCH2, HIGH);
          delay(t);
        }

        // Daqui pra frente eh matematica, dai foi so nadar de bracada,
        // mas ainda to fucando nos livros de C
        // pra enxugar esse codigo:
        if (((10*temperatura) < (tempbase-10)) && (digitalRead(agua) == LOW) && (tempbase!=0))
        {
          digitalWrite(vent1, LOW);
          digitalWrite(vent2, LOW);
          digitalWrite(bomba, LOW);
        }

        else if (((10*temperatura) < (tempbase-10)) && (digitalRead(agua) == HIGH) && (tempbase!=0))
        {
          digitalWrite(vent1, LOW);
          digitalWrite(vent2, LOW);
          digitalWrite(bomba, HIGH);
        }

        else if (((tempbase-10) <= (10*temperatura)) && ((10*temperatura) < tempbase) && (digitalRead(agua) == LOW) && (tempbase!=0))
        {
          digitalWrite(vent1, HIGH);
          digitalWrite(vent2, LOW);
          digitalWrite(bomba, LOW);
        }

        else if (((tempbase-10) <= (10*temperatura)) && ((10*temperatura) < tempbase) && (digitalRead(agua) == HIGH) && (tempbase!=0))
        {
          digitalWrite(vent1, HIGH);
          digitalWrite(vent2, LOW);
          digitalWrite(bomba, HIGH);
        }

        else if ((tempbase <= (10*temperatura)) && ((10*temperatura) < (tempbase+20)) && (digitalRead(agua) == LOW) && (tempbase!=0))
        {
          digitalWrite(vent1, HIGH);
          digitalWrite(vent2, HIGH);
          digitalWrite(bomba, LOW);
        }

        else if ((tempbase <= (10*temperatura)) && ((10*temperatura) < (tempbase+20)) && (digitalRead(agua) == HIGH) && (tempbase!=0))
        {
          digitalWrite(vent1, HIGH);
          digitalWrite(vent2, HIGH);
          digitalWrite(bomba, HIGH);
        }

        else if ((((tempbase+20) <= (10*temperatura)) && (digitalRead(agua) == LOW) && (tempbase!=0)) || (((tempbase+20) <= (10*temperatura)) && (digitalRead(agua) == HIGH) && (tempbase!=0)))
        {
          digitalWrite(vent1, HIGH);
          digitalWrite(vent2, HIGH);
          digitalWrite(bomba, HIGH);
        }      
      }
    }
  }
}