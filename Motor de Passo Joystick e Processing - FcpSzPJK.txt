/*Codigo para girar um motor de passo Mitsumi de 5 fios
 usando joystick ou potenciometro
 Desenvolvido por https://cyberohm.com
 Apoio: labdegaragem.com
 Copie, modifique, compartilhe!
 */

import processing.serial.*; //importa a biblioteca serial do processing
import cc.arduino.*; // importa a biblioteca do arduino para o processing
import processing.net.*;
Arduino arduino; //define o objeto (?) Arduino

color on = color(84, 145, 158); //define a cor quando background está em ON
color off = color(255); //define a cor quando background está em OFF
int a=1200; // largura da tela
int b=600; // altura da tela

int [][] matriz=
{
  {
    0, 0, 0, 1
  }
  , 
  {
    0, 0, 1, 1
  }
  , 
  {
    0, 0, 1, 0
  }
  , 
  {
    0, 1, 1, 0
  }
  , 
  {
    0, 1, 0, 0
  }
  , 
  {
    1, 1, 0, 0
  }
  , 
  {
    1, 0, 0, 0
  }
  , 
  {
    1, 0, 0, 1
  }
};

int joystick = 1;  // Analog input pin that the potentiometer is attached to
int verde = 6;
int amarelo = 7;
int vermelho = 8; 
int button = 9;
int t=5;
int x;
int y;
int count;
int motorState;

int diametro = a/6;

//******************************************** SETUP() ********************************************
void setup()
{
  size(a, b);
  //As duas próximas linhas deram trabalho, mas a vitória pertence aos bravos!
  //Louvado seja ROOT!
  //
  //You can't hack if you don't Slack!
  arduino = new Arduino(this, "/dev/ttyUSB0", 57600); 
  arduino.pinMode(joystick, Arduino.INPUT);
  arduino.pinMode(button, Arduino.INPUT);
  for (int pino=2; pino<9; pino++)
  {
    arduino.pinMode(pino, Arduino.OUTPUT);
  }

  arduino.pinMode(button, Arduino.INPUT);
}


//******************************************** DRAW() ********************************************

void draw()
{
  float sensor = map(arduino.analogRead(joystick), 0, 1023, 0, 100);
  int angle = int(36*sensor/10);
  int begin = arduino.digitalRead(button);


  background(off); //nem precisava comentar.
  stroke(on); // linha de contorno
  stroke(255); // linha de contorno branca.
  strokeWeight(2); // expessura de 3 pixels.
  strokeCap(SQUARE); // quinas quadradas.
  fill(on); //cor de preencimento.

  //LOGOTIPO

  PFont font; 
  font = loadFont("Borg9-48.vlw");
  PFont Arial;
  Arial = loadFont("Arial.vlw");
  textFont(font, 90);
  textAlign(CENTER);
  fill(0);
  text("C Y B E R O H M", a/2+13, b/4+3);
  fill(255, 0, 0);
  text("C Y B E R O H M", a/2+10, b/4);
  textFont(Arial, 28);
  textAlign(RIGHT);
  text("R o b o t i c s", 1070, b/4+50);
  textFont(Arial, 42);
  textAlign(CENTER);

  /*
  PImage img;
   // Image must be in the sketch's "data" folder
   img = loadImage("cyberohm.png");
   image(img, 280, b/16, 800,160);
   */

  fill(255);
  stroke(0); 

  translate(a/2, b/2+100);
  stroke(255, 0, 0);
  strokeWeight(5);
  ellipse(0, 0, diametro, diametro);
  stroke(0);
  strokeWeight(2);
  line(-3*diametro/5, 0, 3*diametro/5, 0);
  line(0, -3*diametro/5, 0, 3*diametro/5);
  /*
  if (begin==1)
   {
   x++;
   if (x>7)
   {
   x=0;
   }
   for (y=0; y<4; y++)
   {
   arduino.digitalWrite((y+2), matriz[x][y]);
   arduino.digitalWrite(vermelho, 1);
   }
   delay(t);
   arduino.digitalWrite(vermelho, 0);
   }
   */
  sensor = map(arduino.analogRead(joystick), 0, 1023, 1, 92);
  if ((motorState==0)&&(begin==0))
  {
    x++;
    if (x>7)
    {
      x=0;
    }
    for (y=0; y<4; y++)
    {
      if (begin==0)
        arduino.digitalWrite((y+2), matriz[x][y]);
          }
  } 
 if ((motorState==0)&&(begin==1))
      {
        motorState=1;
        count=92;
      } 
 
  if ((count<=sensor)&&(sensor-count>2)&&(motorState==1))
  {
    x++;
    if (x>7)
    {
      x=0;
    }
    count++;
    for (y=0; y<4; y++)
    {
      arduino.digitalWrite((y+2), matriz[x][y]);
    }
  } else if ((count>sensor)&&(count-sensor>2)&&(motorState==1))
  {
    x--;
    if (x<0)
    {
      x=7;
    }
    count--;
    for (y=0; y<4; y++)
    {
      arduino.digitalWrite((y+2), matriz[x][y]);
    }
  }

  fill(255, 0, 0);
  stroke(0);
  strokeWeight(5);
  rect(3*diametro/2, 0, 50, -sensor);
  textAlign(LEFT);
  textFont(Arial, 18);
  text(angle+" graus", diametro, 0);
  text(count+" count", diametro, 20);
  text(motorState+" motorState", diametro, 40);
  text(begin+" begin", diametro, 60);
  ellipse(0, 0, 20, 20);
  rotate(radians(-angle));
  quad(0, -20, -20, 0, 0, 20, 20+diametro/2, 0);
}
// \m/ ROCK N ROLL !!!