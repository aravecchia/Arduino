int volt;
int pinoleitura = A0;
unsigned long delta1;
unsigned long delta2;
unsigned long frequencia;
void setup(){
    Serial.begin(9600);
    pinMode(pinoleitura, INPUT);
}
void loop(){
  do{
    volt = analogRead(pinoleitura);
  }while(volt != 0);
  delta1 = millis();
  volt = 1;
   do{
    volt = analogRead(pinoleitura);
  }while(volt != 0);
  delta2 = millis();
  frequencia = delta2 - delta1;
  Serial.println(frequencia);  
}