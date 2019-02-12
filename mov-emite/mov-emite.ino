
 
int pinled = 12; 
int pinopir = 11; 
int pinledv = 3;
int acionamento;
int IRledPin=13;    
int estado=3;
int estadoAnterior=4;


void setup()
  {
    pinMode(pinled, OUTPUT); 
    pinMode(pinledv, OUTPUT);
    pinMode(IRledPin, OUTPUT); 
    pinMode(pinopir, INPUT);
    Serial.begin(9600);
  }
 
void loop()
  {
  acionamento = digitalRead(pinopir); //Le o valor do sensor PIR
 
  if (acionamento == LOW) //Sem movimento, mantem rele desligado
    {
    digitalWrite(pinled, LOW);
    digitalWrite(pinledv, HIGH);
    Serial.println("Parado");
    estado=0;
    }
  else //Caso seja detectado um movimento, aciona o rele
    {
    digitalWrite(pinled, HIGH);
    digitalWrite(pinledv, LOW);
    Serial.println("Movimento !!!");
    estado=1;
    }

  if (estado != estadoAnterior)
    {
    SendChannelUpCode();
    estadoAnterior=estado;
    }
  }


void pulseIR(long microsecs) {

 
cli();  
 
while (microsecs > 0) {

digitalWrite(IRledPin, HIGH); 
delayMicroseconds(10);        
digitalWrite(IRledPin, LOW);  
delayMicroseconds(10);        
 
microsecs -= 26;
}

sei(); 
}
 






void SendChannelUpCode() {

if (estado==1)
{
delayMicroseconds(31036);
pulseIR(4480);
delayMicroseconds(4560);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(600);
pulseIR(520);
delayMicroseconds(580);
pulseIR(520);
delayMicroseconds(580);
pulseIR(500);
delayMicroseconds(600);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(580);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(580);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(5380);
pulseIR(4480);
delayMicroseconds(4540);
pulseIR(540);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(580);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(580);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(520);
delayMicroseconds(580);
pulseIR(520);
delayMicroseconds(580);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1680);
pulseIR(540);
delayMicroseconds(580);
pulseIR(520);
delayMicroseconds(580);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(600);
pulseIR(500);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
delayMicroseconds(1700);
pulseIR(500);
delayMicroseconds(1700);
pulseIR(520);
delayMicroseconds(1680);
pulseIR(520);
}

if (estado==0)
{

delayMicroseconds(62392);
pulseIR(4380);
delayMicroseconds(4660);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(740);
pulseIR(380);
delayMicroseconds(1820);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(740);
pulseIR(380);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(720);
pulseIR(360);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(740);
pulseIR(380);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(400);
delayMicroseconds(740);
pulseIR(380);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(740);
pulseIR(380);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(5500);
pulseIR(4400);
delayMicroseconds(4680);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(760);
pulseIR(360);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(760);
pulseIR(340);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
}
}
