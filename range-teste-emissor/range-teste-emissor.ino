
int IRledPin =  13;  
int estado=0;

void setup()   {

pinMode(IRledPin, OUTPUT);
 
Serial.begin(9600);

delay(5000);
}
 
void loop()
{
Serial.println("Sending IR signal");
 
SendChannelUpCode();
//delay(5000);
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

if (estado==0)
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
estado=1;
delay(5000);
}

if (estado==1)
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
estado=0;
delay(5000);
}
}