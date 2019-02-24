//servo
//#include <Servo.h>
//Servo horizontal;
//Servo vertical;

//realtime
#include "Wire.h"
#define DS1307_ADDRESS 0x68
byte zero = 0x00;


#include <Thermistor.h>
Thermistor temp(2);

int pinled = 12; 
int pinopir = 11; 
int acionamento;
int IRledPin=13;    
int estado=3;
int estadoAnterior=4;
int temperatura;
const int azul = 4;
const int verde = 10;
const int vermelho = 5; 
String cor;

int liberacao_minuto;
int liberacao_hora;
int liberacao_dia;

int segundo;
int minuto;
int hora;   
int diasemana;          
int dia;
int mes;
int ano;

void setup()
  {
    Wire.begin();
    pinMode(pinled, OUTPUT); 
    pinMode(IRledPin, OUTPUT); 
    pinMode(pinopir, INPUT);
    Serial.begin(9600);
    pinMode(azul, OUTPUT);
    pinMode(verde, OUTPUT);
    pinMode(vermelho, OUTPUT);
    delay(1000);
    //setDateTime();
    //servo
//    horizontal.attach(9);
//    vertical.attach(6);
//    vertical.write(175);
//    horizontal.write(90);
  }
 
void loop()
  {

 
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);


//FILTRO 3X

  int segundoanterior = bcdToDec(Wire.read());
  int minutoanterior = bcdToDec(Wire.read());
  int horaanterior = bcdToDec(Wire.read() & 0b111111);    //Formato 24 horas
  int diasemanaanterior = bcdToDec(Wire.read());          //0-6 -> Domingo - Sábado
  int diaanterior = bcdToDec(Wire.read());
  int mesanterior = bcdToDec(Wire.read());
  int anoanterior = bcdToDec(Wire.read());
  
  delay(100);

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);

  int segundoatual = bcdToDec(Wire.read());
  int minutoatual = bcdToDec(Wire.read());
  int horaatual = bcdToDec(Wire.read() & 0b111111);    //Formato 24 horas
  int diasemanaatual = bcdToDec(Wire.read());          //0-6 -> Domingo - Sábado
  int diaatual = bcdToDec(Wire.read());
  int mesatual = bcdToDec(Wire.read());
  int anoatual = bcdToDec(Wire.read());
  
  delay(100);

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);

  
  int segundonovo = bcdToDec(Wire.read());
  int minutonovo = bcdToDec(Wire.read());
  int horanovo = bcdToDec(Wire.read() & 0b111111);    //Formato 24 horas
  int diasemananovo = bcdToDec(Wire.read());          //0-6 -> Domingo - Sábado
  int dianovo = bcdToDec(Wire.read());
  int mesnovo = bcdToDec(Wire.read());
  int anonovo = bcdToDec(Wire.read());

if (minutoanterior == minutoatual && minutoatual==minutonovo && horaanterior == horaatual && horaatual == horanovo && diaanterior == diaatual && diaatual==dianovo)
  {
  segundo=segundonovo;
  minuto=minutonovo;
  hora=horanovo;
  dia=dianovo;
  mes=mesnovo;
  ano=anonovo;
  }
  
      Serial.print("Desligamento programado: ");
      Serial.print(liberacao_hora);
      Serial.print(":");
      Serial.print(liberacao_minuto);
      Serial.print(" ");
      Serial.print(liberacao_dia);
      Serial.print(" ");

  //Exibe a data e hora. Ex.:   3/12/13 19:00:00
  Serial.print(dia);
  Serial.print("/");
  Serial.print(mes);
  Serial.print("/20");
  Serial.print(ano);
  Serial.print(" ");
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
//  Serial.print(":");
//  Serial.print(segundo);

 //temperatura  
  int temperature = temp.getTemp(); 
  Serial.print(" Temperatura: "); 
  Serial.print(temperature); 
  Serial.println("*C ");
  acionamento = digitalRead(pinopir);

      if (temperature == 24 ){delay(500); verdeFuncao();}
      if (temperature > 24){delay(500); vermelhoFuncao();}
      if (temperature < 24){delay(500); azulFuncao();}


  if (acionamento == LOW)
    {

    //Serial.println("Parado");

    if (minuto >= liberacao_minuto && hora >= liberacao_hora && liberacao_dia != dia)
      {
      estado=0;
      digitalWrite(pinled, LOW);
      }
    }
    
  else
    {
     Serial.println("Movimento");

     if (minuto <= 49) {liberacao_minuto=minuto; liberacao_minuto=liberacao_minuto+10; liberacao_dia=99;}
     if (minuto >= 50) {liberacao_minuto=minuto; liberacao_minuto=liberacao_minuto-50; liberacao_dia=99;} 
     if (minuto >= 50 && hora < 23) {liberacao_hora=hora; liberacao_hora=liberacao_hora+1; liberacao_dia=99;}
     if (hora == 23 && minuto <=49) {liberacao_hora=hora; liberacao_dia=99;}
     if (hora == 23 && minuto >=50) {liberacao_hora=0; liberacao_minuto=minuto; liberacao_minuto=liberacao_minuto-50; liberacao_dia=dia;}

      if (temperature >23)
        {
        digitalWrite(pinled, HIGH);
        //Serial.println("Movimento !!!");
        estado=1;
        }
        
      else
        {
        digitalWrite(pinled, LOW);
        //Serial.println("Parado");
        estado=0;
        }
    }


  if (estado != estadoAnterior)
    {
    SendChannelUpCode();
    estadoAnterior=estado;
    }

    
} // end void loop



void verdeFuncao(){
  digitalWrite(azul, LOW);
  digitalWrite(verde, HIGH);
  digitalWrite(vermelho, LOW);
}

void azulFuncao(){
  digitalWrite(azul, HIGH);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, LOW);
}
void vermelhoFuncao(){
  digitalWrite(azul, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(vermelho, HIGH);
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
delayMicroseconds(5392);
pulseIR(4360);
delayMicroseconds(4660);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(720);
pulseIR(360);
delayMicroseconds(1840);
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
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(400);
delayMicroseconds(740);
pulseIR(380);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(720);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(380);
delayMicroseconds(720);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(720);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
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
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(400);
delayMicroseconds(720);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(720);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
/*
delay(500);

delayMicroseconds(5392);
pulseIR(4360);
delayMicroseconds(4660);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(720);
pulseIR(360);
delayMicroseconds(1840);
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
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(740);
pulseIR(360);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(400);
delayMicroseconds(740);
pulseIR(380);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(720);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(380);
delayMicroseconds(720);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(720);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
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
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(420);
delayMicroseconds(1820);
pulseIR(400);
delayMicroseconds(720);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(720);
pulseIR(380);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(720);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(700);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1840);
pulseIR(400);
delayMicroseconds(1820);
pulseIR(420);
*/
} 
}


/*
void setDateTime(){

  byte segundo =      00;  //0-59
  byte minuto =        40;  //0-59
  byte hora =           22;  //0-23
  byte diasemana =    2;  //1-7
  byte dia =               23;  //1-31
  byte mes =            02; //1-12
  byte ano  =            19; //0-99

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero); 

  Wire.write(decToBcd(segundo));
  Wire.write(decToBcd(minuto));
  Wire.write(decToBcd(hora));
  Wire.write(decToBcd(diasemana));
  Wire.write(decToBcd(dia));
  Wire.write(decToBcd(mes));
  Wire.write(decToBcd(ano));

  Wire.write(zero); 

  Wire.endTransmission();

}
*/


byte decToBcd(byte val){
// Conversão de decimal para binário
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
// Conversão de binário para decimal
  return ( (val/16*10) + (val%16) );
}
/*
void printDate(){

}*/
