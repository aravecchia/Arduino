//Mux control pins
int r0 = 8;
int r1 = 9;
int r2 = 10;
int r3 = 11;

int s0 = 11;
int s1 = 12;
int s2 = 9;
int s3 = 10;

//Mux in "SIG" pin
int sensor = 1;
int led = 0;
void setup(){
  pinMode(r0, OUTPUT); 
  pinMode(r1, OUTPUT); 
  pinMode(r2, OUTPUT); 
  pinMode(r3, OUTPUT); 
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);

  digitalWrite(r0, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, LOW);
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  Serial.begin(9600);
}


void loop(){

  //Loop through and read all 16 values
  //Reports back Value at channel 6 is: 346
  for(int i = 0; i < 16; i ++)
  {
    Serial.print("Value at channel ");
    Serial.print(i);
    Serial.print("is : ");
    Serial.println(255-map((readMux(i)), 0, 1023, 0, 255));
    analogWrite(led, 255-map((readMux(i)), 0, 1023, 0, 255));
    delay(250);
  }

}


int readMux(int channel)
{
  int controlPin[] = {
    r0, r1, r2, r3  };
  int ledPin[] = {
    s0, s1, s2, s3  };
  int muxChannel[16][4]={
    {
      0,0,0,0    }
    , //channel 0
    {
      1,0,0,0    }
    , //channel 1
    {
      0,1,0,0    }
    , //channel 2
    {
      1,1,0,0    }
    , //channel 3
    {
      0,0,1,0    }
    , //channel 4
    {
      1,0,1,0    }
    , //channel 5
    {
      0,1,1,0    }
    , //channel 6
    {
      1,1,1,0    }
    , //channel 7
    {
      0,0,0,1    }
    , //channel 8
    {
      1,0,0,1    }
    , //channel 9
    {
      0,1,0,1    }
    , //channel 10
    {
      1,1,0,1    }
    , //channel 11
    {
      0,0,1,1    }
    , //channel 12
    {
      1,0,1,1    }
    , //channel 13
    {
      0,1,1,1    }
    , //channel 14
    {
      1,1,1,1    }  //channel 15
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]); 
    digitalWrite(ledPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = (255-map(analogRead(sensor), 0, 1023, 0, 255));

  //return the value
  return val;
}