/*
 AC Light Dimmer - Inmojo 
 AC Voltage dimmer with Zero cross detection
 
 Author: Charith Fernanado http://www.inmojo.com charith@inmojo.com 
 License: Released under the Creative Commons Attribution Share-Alike 3.0 License. 
 http://creativecommons.org/licenses/by-sa/3.0
 Target:  Arduino
 
 Attach the Zero cross pin of the module to Arduino External Interrupt pin
 Select the correct Interrupt # from the below table
 Pin    |  Interrrupt # | Arduino Platform
 ---------------------------------------
 2      |  0            |  All
 3      |  1            |  All
 18     |  5            |  Arduino Mega Only
 19     |  4            |  Arduino Mega Only
 20     |  3            |  Arduino Mega Only
 21     |  2            |  Arduino Mega Only
 
 */

int AC_LOAD = 3;    // Output to Opto Triac pin
int dimming = 128;  // Dimming level (0-128)  0 = ON, 128 = OFF
int buttonPin = 2;
int buttonState;
void setup()
{
  Serial.begin(9600);
  pinMode(AC_LOAD, OUTPUT);	      // Set the AC Load as output
  attachInterrupt(0, zero_crosss_int, RISING);  // Choose the zero cross interrupt # from the table above
}

void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{
  // Firing angle calculation :: 60Hz-> 8.33ms (1/2 Cycle)
  // (8333us - 8.33us) / 128 = 65 (Approx)
  int dimtime = (65*dimming);      
  delayMicroseconds(dimtime);    // Off cycle
  digitalWrite(AC_LOAD, HIGH);   // triac firing
  delayMicroseconds(8.33);         // triac On propogation delay
  digitalWrite(AC_LOAD, LOW);    // triac Off
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  Serial.print("Primeira leitura: ");
  Serial.print(buttonState);
  Serial.println("");
  
  dimming = 128; 
  delay(100);
  dimming = 75;  
  delay(100);
  dimming = 25;  
  delay(100);
  dimming = 0;  
  delay(100);
  
  buttonState = digitalRead(buttonPin);
  Serial.print("Segunda leitura: ");
  Serial.print(buttonState);
  Serial.println("");
  
  

}