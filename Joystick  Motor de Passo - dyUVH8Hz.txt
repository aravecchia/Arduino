/*
  Motor de Passo Mitsumi 5 terminais.
 Gira o motor em funcao da leitura de um potenciometro.
 Autor: http://cyberohm.com
 Apoio: http://www.labdegaragem.com
 */

int matriz[8][4] =
{
  {
    0,0,0,1                              }
  ,
  {
    0,0,1,1                              }
  ,
  {
    0,0,1,0                              }
  ,
  {
    0,1,1,0                              }
  ,
  {
    0,1,0,0                              }
  ,
  {
    1,1,0,0                              }
  ,
  {
    1,0,0,0                              }
  ,
  {
    1,0,0,1                              }

};

int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
  int t=10;
int x;
int y;
int count;

void setup() 
{                
  Serial.begin(9600);
  pinMode(2, OUTPUT);   
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); 
}

void loop()
{
  // read the analog in value:
  int  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  int  outputValue = map(sensorValue, 0, 1023, 0, 12);  
  // change the analog out value:

  {
    while(count<outputValue)
    {
      for (x=0; x<8; x++)
      {
        for (y=0; y<4; y++)
        {
          digitalWrite((y+2), matriz[x][y]);
        }
        delay(t);
      }
      count++;
    }
    while(count>outputValue)
    {
      for (x=7; x>=0; x--)
      {
        for (y=0; y<4; y++)
        {
          digitalWrite((y+2), matriz[x][y]);
        }
        delay(t);
      }
      count--;
    }
  }
}