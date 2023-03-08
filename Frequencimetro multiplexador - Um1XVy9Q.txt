//Código para multiplexador HCF4051 e oscilador NE555.
//Pense nas possibilidades: utilizando algum outro mux de 16 saidas, tenho mais de
// 700 sensores analogicos funcionando num único Arduino!

#include <Wire.h>
//Mux control pins
int r0 = 2;
int r1 = 3;
int r2 = 4;

int entrada = A0;

int var = (analogRead(A0));

int x=0;

unsigned long pico  = 0;
unsigned long vale = 0;
float periodo = 0;
float frequencia = 0;
int T=1000;
void setup()

{
  pinMode(r0, OUTPUT); 
  pinMode(r1, OUTPUT); 
  pinMode(r2, OUTPUT); 

  pinMode(entrada, INPUT); 

  digitalWrite(r0, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);

  Serial.begin(9600);
}

void loop()

{
  for (x=0; x<7; x++)
  {
    toca();
  }
}


void toca()
{
  switch (x)
  {
  case 0:
    {
      digitalWrite(r0, LOW);
      digitalWrite(r1, LOW);
      digitalWrite(r2, LOW);
    }
    break;
  case 1:
    {
      digitalWrite(r0, HIGH);
      digitalWrite(r1, LOW);
      digitalWrite(r2, LOW);
    }
    break;
  case 2:  
    {
      digitalWrite(r0, LOW);
      digitalWrite(r1, HIGH);
      digitalWrite(r2, LOW);
    }
    break;
  case 3:
    {
      digitalWrite(r0, HIGH);
      digitalWrite(r1, HIGH);
      digitalWrite(r2, LOW);
    }
    break;
  case 4:
    {
      digitalWrite(r0, LOW);
      digitalWrite(r1, LOW);
      digitalWrite(r2, HIGH);
    }
    break;
  case 5:
    {
      digitalWrite(r0, HIGH);
      digitalWrite(r1, LOW);
      digitalWrite(r2, HIGH);
    }
    break;
  case 6:
    {
      digitalWrite(r0, LOW);
      digitalWrite(r1, HIGH);
      digitalWrite(r2, HIGH);
    }
    break;
  case 7:
    {
      digitalWrite(r0, HIGH);
      digitalWrite(r1, HIGH);
      digitalWrite(r2, HIGH);
    }
    break;
  }
  lerfrequencia();
  escreverfrequencia();
}

void lerfrequencia()
{


  pico    = (pulseIn(entrada, HIGH));
  vale   = (pulseIn(entrada, LOW));
  periodo = (pico + vale);
  frequencia = (1000000/periodo);
}

void escreverfrequencia()
{
  if(periodo)
  {
    Serial.print("T");
        Serial.print(x);
            Serial.print(": ");
    Serial.print(periodo);
    Serial.print(" us - ");

    Serial.print("Freq");
        Serial.print(x);
            Serial.print(": ");
    Serial.print(frequencia,2);
    Serial.println(" Hz");

    delay(T);
  }
}