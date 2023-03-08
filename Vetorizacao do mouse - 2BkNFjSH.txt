//CYBEROHM.COM

void setup()
{
  size(800, 600);
}

void draw()
{
  int a = 100; //raio da elipse principal
  int factor = 4; //fator de razão entre as elipses
  int origem = 100; //Origem do plano cartesiano
  float dX = mouseX-origem;
  float dY = -(mouseY-origem);
  int TEXTO = 14;


  background(255); //cor de fundo
  strokeWeight(5);
  //círculo central
  stroke(0, 0, 255);
  if (mousePressed)
  {
    fill(255, 0, 0);
    background(0); //muda a cor de fundo
  } else
  {
    fill(0, 200, 0);
  }

  //circulo do mouse
  ellipse(origem, origem, a, a);
  stroke(0);
  if (mousePressed)
  {
    fill(0, 200, 0);
  } else
  {
    fill(255, 0, 0);
  }

  //cruz do mouse
  strokeWeight(2);
  ellipse(mouseX, mouseY, a/factor, a/factor);
  line((mouseX-(a/factor)), mouseY, (mouseX+(a/factor)), mouseY);
  line(mouseX, (mouseY-(a/factor)), mouseX, (mouseY+(a/factor))); 

  //linha de direção  
  stroke(#FF8000);
  strokeWeight(3);

  line(origem, origem, mouseX, mouseY);

  //Fundo do relógio
  stroke(0);
  fill(0);
  rect(0, 3*height/4-20, width, width/4+20);

  //Relogio X
  noStroke();
  fill(255);
  textSize(TEXTO);
  textAlign(LEFT, CENTER);
  text("dx= "+Float.toString(dX), width/2, 3*height/4);

  //Relogio Y

  noStroke();
  fill(255);
  textSize(TEXTO);
  textAlign(LEFT, CENTER);
  text("dy= "+Float.toString(dY), width/2, 3*height/4+20);

  //Relogio principal
  float D = sqrt(pow((dX), 2)+pow((dY), 2));
  noStroke();
  fill(255);
  textSize(TEXTO);
  textAlign(LEFT, CENTER);
  text("D= "+Float.toString(D), width/2, 3*height/4+40);

  //Relogio de coordenadas
  if (dY != 0)
  {
    float alpha = (dX/dY);
    noStroke();
    fill(255);
    textSize(TEXTO);
    textAlign(LEFT, CENTER);
    text("alpha= "+Float.toString(alpha), width/2, 3*height/4+60);
    //Equação da reta
    text("y= "+Float.toString(alpha*dX)+"x", width/2, 3*height/4+80);
  } else
  {
    noStroke();
    fill(255);
    textSize(TEXTO);
    textAlign(LEFT, CENTER);
    text("alpha= NON EKZISTE!!!", width/2, 3*height/4+60);
    text("y= 0", width/2, 3*height/4+80);
  }

  //E finalmente a porra do relogio final!
  if (dY != 0)
  {
    float beta = asin(dY/D);
    noStroke();
    fill(255);
    {
      if (beta >= 0 && beta <= PI/2)
      {
        arc((origem), (origem), (a-5), (a-5), 0, (beta+PI/2));
        textSize(TEXTO);
        textAlign(LEFT, CENTER);
        text("beta= "+Float.toString(degrees(beta)), width/2, 3*height/4+100);
      }
    }
  }
}