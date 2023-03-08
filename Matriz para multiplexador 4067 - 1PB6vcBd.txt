Tenho esse switch/case no arduino:
{
  for (led=1; led<17; led++)
  {
    switch (led)
    {
    case 1:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, LOW);
        digitalWrite(r2, LOW);
        digitalWrite(r3, LOW);  
        //0000      
      }
      break;
    case 2:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, LOW);
        digitalWrite(r2, LOW);
        digitalWrite(r3, LOW); 
        //0001     
      }
      break;
    case 3:  
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, LOW);
        digitalWrite(r3, LOW);
        //0010       
      }
      break;
    case 4:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, LOW);
        digitalWrite(r3, LOW); 
        //0011     
      }
      break;
    case 5:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, LOW);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW); 
        //0100      
      }
      break;
    case 6:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, LOW);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW);  
        //0101      
      }
      break;
    case 7:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW);  
        //0110    
      }
      break;
    case 8:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, LOW);
        //0111     
      }
    case 9:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, LOW);
        digitalWrite(r2, LOW);
        digitalWrite(r3, HIGH); 
        //1000      
      }
    case 10:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, LOW);
        digitalWrite(r2, LOW);
        digitalWrite(r3, HIGH); 
        //1001      
      }
    case 11:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, LOW);
        digitalWrite(r3, HIGH); 
        //1010    
      }
    case 12:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, LOW);
        digitalWrite(r3, HIGH); 
        //1011     
      }
    case 13:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, LOW);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);  
        //1100     
      }
    case 14:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, LOW);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);  
        //1101    
      }
    case 15:
      {
        digitalWrite(r0, LOW);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);
        //1110     
      }
    case 16:
      {
        digitalWrite(r0, HIGH);
        digitalWrite(r1, HIGH);
        digitalWrite(r2, HIGH);
        digitalWrite(r3, HIGH);  
        //1111     
      }
      break;
    }

E preciso de algo mais enxuto numa matriz pra poder trabalhar, alguma coisa assim:

int seletor[4] = {r0,r1,r2,r3}

int matriz[led][seletor] = {
{0,0,0,0},
{0,0,0,1},
{0,0,1,0},
{0,0,1,1},
{0,1,0,0},
{0,1,0,1},
{0,1,1,0},
{0,1,1,1},
{1,0,0,0},
{1,0,0,1},
{1,0,1,0},
{1,0,1,1},
{1,1,1,1},
}

E não sei agora como jogar isso num laćo for pra mandar o sinal pros pinos certos do arduino. É pra versão final do multiplexador, já vou fabricar a PCB e preciso ter ctz dq ta funcionando certinho.