const int entrada = 13;
const int timeout = 500000;   // meio segundo

void setup() {  
  pinMode(entrada, INPUT);
  Serial.begin(9600);
}

void loop()
{
  long T_ON  = 0;
  long T_OFF = 0;
  long T_TOTAL = 0;
  long FREQ = 0;

  T_ON    = pulseIn(entrada, HIGH, timeout);
  T_OFF   = pulseIn(entrada, LOW, timeout);
  T_TOTAL = (T_ON + T_OFF);
  
  if(T_TOTAL){
     Serial.print("T: ");
     Serial.print(T_TOTAL);
     Serial.print(" ms");
     
     Serial.print("Freq: ");
     Serial.print((1000000/T_TOTAL));
     Serial.println(" Hz");
  }
}