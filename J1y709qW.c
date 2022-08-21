  int azul = 1;
  int vermelho = 0;
  void setup()
{
  Serial.begin(9600);
}
void loop()
{
  delay(300);
  
  if(azul == 2)
  {
     Serial.println("ABC") ;
  }
  else if ((vermelho == 0) &&  (azul == 1))
  {
             Serial.println("123") ;
  }  
}