int entrada = A0;
int delta1;
int delta2;
int periodo;
long frequencia;

void setup()
{  
  Serial.begin(9600);
  pinMode(entrada, INPUT);
}

void loop()
{

  int tensao = analogRead(entrada);
  delta1 = 0;
delta2 = millis();
  if (tensao = 0);
  {
    periodo=(delta2-delta1);
    frequencia=2/periodo;
    Serial.println(frequencia,2);
  }
}