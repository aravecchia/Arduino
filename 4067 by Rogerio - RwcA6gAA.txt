//Mux control pins
int s00 = 5;
int s01 = 6;
int s02 = 7;
int s03 = 8;

int s10 = 9;
int s11 = 10;
int s12 = 11;
int s13 = 12;


//Mux in "SIG" pin
int SIG_pin = 0;

void setup(){
  pinMode(s00, OUTPUT); 
  pinMode(s01, OUTPUT); 
  pinMode(s02, OUTPUT);
  pinMode(s03, OUTPUT);
  
  pinMode(s10, OUTPUT); 
  pinMode(s11, OUTPUT); 
  pinMode(s12, OUTPUT); 
  pinMode(s13, OUTPUT); 
  
  digitalWrite(s00, LOW);
  digitalWrite(s01, LOW);
  digitalWrite(s02, LOW);
  digitalWrite(s03, LOW);
  
  digitalWrite(s10, LOW);
  digitalWrite(s11, LOW);
  digitalWrite(s12, LOW);
  digitalWrite(s13, LOW);
  
  Serial.begin(9600);
}

void loop(){

  
  //Principal fazer iteração de 0 até numero de secundarios a usar (no seu teste = 2)
 for(int princ = 0; princ < 2; princ ++){
  //Secundária, fazer o loop de 0 a 8
  for(int sec = 0; sec < 8; sec ++){
    Serial.print("Master: ");
    Serial.print(princ);
    Serial.print(" , Segundario: ");
    Serial.print(sec);
    Serial.print(" , eh : ");
    Serial.println(readMux(princ,sec));
    delay(500);
   }
  }  
}
int readMux(int principal, int secundario){
  int controlPin0[] = {s00, s01, s02, s03};
  int controlPin1[] = {s10, s11, s12, s13};

  //pode-se usar um vetor para armazenar os 3 valores e depois fazer um laço FOR p/ escrever
  bool pr0 = bitRead(principal, 0);
  bool pr1 = bitRead(principal, 1);
  bool pr2 = bitRead(principal, 2);
  bool pr3 = bitRead(principal, 3);
  

  bool sec0 = bitRead(secundario, 0); 
  bool sec1 = bitRead(secundario, 1);
  bool sec2 = bitRead(secundario, 2);
  bool sec3 = bitRead(secundario, 3);
  

 //Se estiverem como vetor, pode-se usar um laço FOR aqui para escrever os 3 valores
 digitalWrite(controlPin0[0], pr0);
 digitalWrite(controlPin0[1], pr1);
 digitalWrite(controlPin0[2], pr2);
 digitalWrite(controlPin0[3], pr3);
 

 digitalWrite(controlPin1[0], sec0);  
 digitalWrite(controlPin1[1], sec1);  
 digitalWrite(controlPin1[2], sec2);  
 digitalWrite(controlPin1[3], sec3);  


  //read the value at the SIG pin
  int val = analogRead(SIG_pin);

  //return the value
  return val;
}