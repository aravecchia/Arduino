/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int ledA = 13;
int ledB = 12;
int t = 500;
// the setup routine runs once when you press reset:
void setup()
{                
  // initialize the digital pin as an output.
  pinMode(ledA, OUTPUT); 
  pinMode(ledB, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop()
{
  digitalWrite(ledA, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(ledB, HIGH);   // turn the LED on (HIGH is the voltage level)  
  delay(t);               // wait for a second
  digitalWrite(ledA, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(ledB, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(t);               // wait for a second
}