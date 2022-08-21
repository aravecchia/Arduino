//CYBEROHM.COM

void setup()
{
  size(1300, 640);
}

void draw()
{
  cursor(CROSS);
  int R = 100; //raio da elipse principal
  int factor = 4; //fator de razão entre as elipses

  int origemX; //Origem do plano cartesiano em X
  int origemY; //Origem do plano cartesiano em Y

    int TEXTO = 12;

  background(0); //cor de fundo
  for (origemY = 100; origemY <= 600; origemY = origemY + 150) //Origem do plano cartesiano em Y
  {
    for (origemX = 100; origemX <= 1200; origemX = origemX + 300) //Origem do plano cartesiano em X
    {
      // Fundo do Dial
      stroke(255);
      strokeWeight(2);
      fill(0, 80, 0);
      ellipse(origemX, origemY, 100, 100);

      //Quadrantes do Dial
      strokeWeight(2);
      strokeCap(SQUARE);
      stroke(0);
      line(origemX, origemY-48, origemX, origemY+48);
      line(origemX-48, origemY, origemX+48, origemY);

      //Origem do Dial
      strokeCap(ROUND);
      stroke(255);
      strokeWeight(10);
      point(origemX, origemY);

      // Linha de vetor
      stroke(255, 70, 0);
      strokeWeight(1);
      line(origemX, origemY, mouseX, mouseY);

      // Vetores
      float dX = (mouseX-origemX);
      float dY = (mouseY-origemY);
      float D = sqrt(pow((dX), 2)+pow((dY), 2));
      noStroke();
      fill(255);
      textSize(TEXTO);
      textAlign(LEFT, CENTER);
      text("dx = "+Float.toString(dX), origemX+70, origemY-40);
      text("dy = "+Float.toString(dY), origemX+70, origemY-20);
      text("D  = "+Float.toString(D), origemX+70, origemY);

      //Quadrantes dos vetores:
      if (dY != 0)
      {
        if ((dX/D > 0) && (dY/D > 0))
        {
          float derivada = dX/dY;
          float alpha = degrees(asin(dX/D));
          text("f'(x)= "+Float.toString(derivada), origemX+70, origemY+20);
          text("α = "+Float.toString(alpha)+"º", origemX+70, origemY+40);
        } else if ((dX/D > 0) && (dY/D < 0))
        {
          float derivada = dX/dY;
          float alpha = 180 - degrees(asin(dX/D));
          text("f'(x)= "+Float.toString(derivada), origemX+70, origemY+20);
          text("α = "+Float.toString(alpha)+"º", origemX+70, origemY+40);
        } else if ((dX/D < 0) && (dY/D < 0))
        {
          float derivada = dX/dY;
          float alpha = 180 - degrees(asin(dX/D));
          text("f'(x)= "+Float.toString(derivada), origemX+70, origemY+20);
          text("α = "+Float.toString(alpha)+"º", origemX+70, origemY+40);
        } else if ((dX/D < 0) && (dY/D > 0))
        {
          float derivada = dX/dY;
          float alpha = 360 + degrees(asin(dX/D));
          text("f'(x)= "+Float.toString(derivada), origemX+70, origemY+20);
          text("α = "+Float.toString(alpha)+"º", origemX+70, origemY+40);
        }
      } else
      {
        text("f'(x) -> oo", origemX+70, origemY+20);
        text("α = 90º", origemX+70, origemY+40);
      }
    }
  }
}