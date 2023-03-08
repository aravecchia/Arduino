int LATCH1 = 2;
int DATA1 = 3;
int CLK1 = 4;

int LATCH2 = 5;
int DATA2 = 6;
int CLK2 = 7;

int desce = 8;
int sobe = 9;
int agua = 10;
int vent1 = 11;
int vent2 = 12;
int bomba = 13;
int tempbase=275;

//latch: pino 12 no 74hc595
//data: pino 14 no 74hc595
//clock: pino 11 no 74hc595
const int inPin = 0; // analog pin


byte digito1[10]= {
  B11111101,B01100001,B11011011,B11110011,B01100111,B10110111,B10111111,B11100001,B11111111,B11110111};
byte digito2[10]= {
  B11111101,B01100001,B11011011,B11110011,B01100111,B10110111,B10111111,B11100001,B11111111,B11110111};
byte digito3[10]= {
  B11111101,B01100001,B11011011,B11110011,B01100111,B10110111,B10111111,B11100001,B11111111,B11110111};
byte digito4[10]= {
  B11111101,B01100001,B11011011,B11110011,B01100111,B10110111,B10111111,B11100001,B11111111,B11110111};
byte digito5[10]= {
  B11111101,B01100001,B11011011,B11110011,B01100111,B10110111,B10111111,B11100001,B11111111,B11110111};
byte digito6[10]= {
  B11111101,B01100001,B11011011,B11110011,B01100111,B10110111,B10111111,B11100001,B11111111,B11110111};


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
  int t=50;

  int value = analogRead(inPin);
  float millivolts = (value / 1024.0) * 5000;
  float temperatura = millivolts / 10; // sensor output is 10mV per degree Celsius
  float celsius = millivolts / 10; // sensor output is 10mV per Serial.print(celsius);
  Serial.print(temperatura);
  Serial.print(" degrees Celsius, ");
  Serial.println(" degrees Celsius, ");

  int unidade;
  int dezena;
  int centena;

  int uni;
  int dez;
  int cent;

  {
    {
      int temperatura = analogRead(A0);
      cent = (temperatura/100);
      dezena = ((temperatura - (cent*100)) / 10);
      uni = temperatura - ((100*cent) + (10*dez));
      digitalWrite(LATCH1, LOW);
      shiftOut(DATA1, CLK1, LSBFIRST, digito1[cent]);
      shiftOut(DATA1, CLK1, LSBFIRST, digito2[dez]);
      shiftOut(DATA1, CLK1, LSBFIRST, digito3[uni]);
      digitalWrite(LATCH1, HIGH); 
      delay(t);
    }

    {
      //separar digitos tempbase exemplo: 285
      centena = (tempbase/100);
      //285/100=2 apenas o numero inteiro é captado
      dezena = ((tempbase - (centena*100)) / 10);
      //285-(2*100)/10 ou seja,285-200 (=85/10=8,5) apenas 8 é jogado no inteiro
      unidade = tempbase - ((100*centena) + (10*dezena));
      // 285-(200+80) ou (285 - 280) = 5
      digitalWrite(LATCH2, LOW);
      shiftOut(DATA2, CLK2, LSBFIRST, digito4[centena]); // escreve a centena no display
      shiftOut(DATA2, CLK2, LSBFIRST, digito5[dezena]); // escreve a dezena no display
      shiftOut(DATA2, CLK2, LSBFIRST, digito6[unidade]); // escreve a unidade no display
      digitalWrite(LATCH2, HIGH); 
      delay(t);
    }
    if ((digitalRead(sobe) == HIGH) && (tempbase!=0))
    {
      tempbase = tempbase + 5;
      centena = (tempbase/100);
      dezena = ((tempbase - (centena*100)) / 10);
      unidade = tempbase - ((100*centena) + (10*dezena));
      digitalWrite(LATCH2, LOW);
      shiftOut(DATA2, CLK2, LSBFIRST, digito4[centena]);
      shiftOut(DATA2, CLK2, LSBFIRST, digito5[dezena]);
      shiftOut(DATA2, CLK2, LSBFIRST, digito6[unidade]);
      digitalWrite(LATCH2, HIGH); 
      delay(t);
    }

    if ((digitalRead(desce) == HIGH) && (tempbase!=0))
    {
      tempbase = tempbase - 5;
      centena=(tempbase/100);
      dezena=((tempbase-(centena*100))/10);
      unidade=tempbase-((100*centena) + (10*dezena));
      digitalWrite(LATCH2, LOW);
      shiftOut(DATA2, CLK2, LSBFIRST, digito4[centena]);
      shiftOut(DATA2, CLK2, LSBFIRST, digito5[dezena]);
      shiftOut(DATA2, CLK2, LSBFIRST, digito6[unidade]);
      digitalWrite(LATCH2, HIGH); 
      delay(t);
    }
    if ((temperatura < (tempbase-1)) && (digitalRead(agua) == LOW) && (tempbase!=0))
    {
      digitalWrite(vent1, LOW); 

      digitalWrite(vent2, LOW); 

      digitalWrite(bomba, LOW);
    }

    else if (((tempbase-1) <= temperatura) && (temperatura < tempbase) && (digitalRead(agua) == LOW) && (tempbase!=0))
    {
      digitalWrite(vent1, HIGH); 

      digitalWrite(vent2, LOW); 

      digitalWrite(bomba, LOW);
    } 

    else if ((tempbase <= temperatura) && (temperatura < (tempbase+1)) && (digitalRead(agua) == LOW) && (tempbase!=0))
    {
      digitalWrite(vent1, HIGH); 

      digitalWrite(vent2, HIGH); 

      digitalWrite(bomba, LOW);
    } 
    else if (((tempbase+1) <= temperatura) && (digitalRead(agua) == LOW) && (tempbase!=0))
    {
      digitalWrite(vent1, HIGH); 

      digitalWrite(vent2, HIGH); 

      digitalWrite(bomba, HIGH);
    }       
    while ((digitalRead(agua) == HIGH) && (tempbase!=0))
    {
      digitalWrite(bomba, HIGH);
    }       
  }
}