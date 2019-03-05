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


String tempar;
int trocatemp_minuto;
int trocatemp_dia;
int trocatemp_hora;

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
   // delay(1000);
  // setDateTime();
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

 //Serial.print(hora);
  
      Serial.print("Desligamento programado: ");
      Serial.print(liberacao_hora);
      Serial.print(":");
      Serial.print(liberacao_minuto);
      Serial.print(" ");
      Serial.print(liberacao_dia);
      Serial.print(" / ");


      Serial.print("Troca temperatura programada: ");
      Serial.print(trocatemp_hora);
      Serial.print(":");
      Serial.print(trocatemp_minuto);
      Serial.print(" ");
      Serial.print(trocatemp_dia);
      Serial.print(" º");
      Serial.print(tempar);
      Serial.print(" / ");


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

      if (temperature == 24 ){/*delay(500);*/ verdeFuncao();}
      if (temperature > 24){/*delay(500);*/ vermelhoFuncao();}
      if (temperature < 24){/*delay(500);*/ azulFuncao();}


  if (acionamento == LOW)
    {

   Serial.print("Parado    ");

   if (minuto >= liberacao_minuto && hora >= liberacao_hora && liberacao_dia != dia)
      {
      estado=0;
      digitalWrite(pinled, LOW);
      }

    
    }
    
  else
    {
     Serial.print("Movimento ");

     if (minuto <= 49) {liberacao_minuto=minuto; liberacao_minuto=liberacao_minuto+10; liberacao_dia=99; liberacao_hora=hora;}
     if (minuto >= 50) {liberacao_minuto=minuto; liberacao_minuto=liberacao_minuto-50; liberacao_dia=99;} 
     if (minuto >= 50 && hora < 23) {liberacao_hora=hora; liberacao_hora=liberacao_hora+1; liberacao_dia=99;}
     if (hora == 23 && minuto <=49) {liberacao_hora=hora; liberacao_dia=99;}
     if (hora == 23 && minuto >=50) {liberacao_hora=0; liberacao_minuto=minuto; liberacao_minuto=liberacao_minuto-50; liberacao_dia=dia;}

      if (temperature >22)
        {
        digitalWrite(pinled, HIGH);
        //Serial.println("Movimento !!!");
        estado=1;


        if (minuto >= trocatemp_minuto && hora >= trocatemp_hora && trocatemp_dia != dia)
          {
            if (temperature > 26 && tempar!="21"){ set22g(); tempar="21";}
            if (temperature == 26 && tempar!="22"){ set22g(); tempar="22";}
            if (temperature == 25 && tempar!="23") {set23g(); tempar="23";}
            if (temperature == 24 && tempar!="24") {set24g(); tempar="24";}
            if (temperature == 23 && tempar!="25") {set25g(); tempar="25";}
             timer3();
          }
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



void timer3() {
     if (minuto <= 56) {trocatemp_minuto=minuto; trocatemp_minuto=trocatemp_minuto+3; trocatemp_dia=99; trocatemp_hora=hora;}
     if (minuto >= 57) {trocatemp_minuto=minuto; trocatemp_minuto=trocatemp_minuto-57; trocatemp_dia=99;} 
     if (minuto >= 57 && hora < 23) {trocatemp_hora=hora; trocatemp_hora=trocatemp_hora+1; trocatemp_dia=99;}
     if (hora == 23 && minuto <=56) {trocatemp_hora=hora; trocatemp_dia=99;}
     if (hora == 23 && minuto >=57) {trocatemp_hora=0; trocatemp_minuto=minuto; trocatemp_minuto=trocatemp_minuto-57; trocatemp_dia=dia;}  
     
  }


  byte decToBcd(byte val){
// Conversão de decimal para binário
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
// Conversão de binário para decimal
  return ( (val/16*10) + (val%16) );
}




/*
void setDateTime(){
  byte segundo =      00;  //0-59
  byte minuto =        0;  //0-59
  byte hora =           16;  //0-23
  byte diasemana =    2;  //1-7
  byte dia =               5;  //1-31
  byte mes =            3; //1-12
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
void printDate(){

}*/



void set21g() {
delayMicroseconds(12004);
pulseIR(4420);
delayMicroseconds(4620);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(700);
pulseIR(420);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(700);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(5460);
pulseIR(4440);
delayMicroseconds(4640);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(700);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
}


void set22g() {
  
delayMicroseconds(26844);
pulseIR(4400);
delayMicroseconds(4620);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(5480);
pulseIR(4420);
delayMicroseconds(4640);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
}

void set23g() {
  
delayMicroseconds(39920);
pulseIR(4420);
delayMicroseconds(4620);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(480);
delayMicroseconds(1760);
pulseIR(460);
delayMicroseconds(660);
pulseIR(460);
delayMicroseconds(640);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(480);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1760);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1760);
pulseIR(480);
delayMicroseconds(1760);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(660);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(660);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(5460);
pulseIR(4440);
delayMicroseconds(4620);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(460);
delayMicroseconds(1760);
pulseIR(480);
delayMicroseconds(1760);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(660);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1760);
pulseIR(480);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(640);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
}

void set24g() {
  delayMicroseconds(53780);
pulseIR(4420);
delayMicroseconds(4640);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(1760);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(5440);
pulseIR(4440);
delayMicroseconds(4620);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(1780);
pulseIR(460);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(420);
delayMicroseconds(680);
pulseIR(440);
delayMicroseconds(660);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(440);
delayMicroseconds(1800);
pulseIR(440);
delayMicroseconds(1780);
pulseIR(460);


  }

void set25g () {
  
delayMicroseconds(35016);
pulseIR(380);
delayMicroseconds(940);
pulseIR(3060);
delayMicroseconds(4660);
pulseIR(400);
delayMicroseconds(3160);
pulseIR(180);
delayMicroseconds(5400);
pulseIR(140);
delayMicroseconds(960);
pulseIR(180);
delayMicroseconds(3200);
pulseIR(120);
delayMicroseconds(940);
pulseIR(180);
delayMicroseconds(4260);
pulseIR(220);
delayMicroseconds(5400);
pulseIR(140);
delayMicroseconds(3160);
pulseIR(220);
delayMicroseconds(880);
pulseIR(220);
delayMicroseconds(880);
pulseIR(240);
delayMicroseconds(18820);
pulseIR(180);
delayMicroseconds(900);
pulseIR(220);
delayMicroseconds(880);
pulseIR(240);
delayMicroseconds(840);
pulseIR(260);
delayMicroseconds(880);
pulseIR(220);
delayMicroseconds(5360);
pulseIR(220);
delayMicroseconds(880);
pulseIR(220);
delayMicroseconds(3120);
pulseIR(220);
delayMicroseconds(860);
pulseIR(260);
delayMicroseconds(840);
pulseIR(260);
delayMicroseconds(840);
pulseIR(260);
delayMicroseconds(840);
pulseIR(260);
delayMicroseconds(5380);
pulseIR(180);
delayMicroseconds(12460);
pulseIR(4180);
delayMicroseconds(8160);
pulseIR(260);
delayMicroseconds(5300);
pulseIR(300);
delayMicroseconds(840);
pulseIR(260);
delayMicroseconds(3080);
pulseIR(260);
delayMicroseconds(820);
pulseIR(280);
delayMicroseconds(3040);
pulseIR(300);
delayMicroseconds(820);
pulseIR(280);
delayMicroseconds(5320);
pulseIR(260);
delayMicroseconds(3100);
pulseIR(260);
delayMicroseconds(840);
pulseIR(260);
delayMicroseconds(820);
pulseIR(280);
delayMicroseconds(18780);
pulseIR(240);
delayMicroseconds(860);
pulseIR(240);
delayMicroseconds(860);
pulseIR(260);
delayMicroseconds(840);
pulseIR(260);
delayMicroseconds(860);
pulseIR(240);
delayMicroseconds(5320);
pulseIR(260);
delayMicroseconds(860);
pulseIR(260);
delayMicroseconds(3080);
pulseIR(260);
delayMicroseconds(840);
pulseIR(260);
delayMicroseconds(840);
pulseIR(260);
delayMicroseconds(820);
pulseIR(280);
delayMicroseconds(840);
pulseIR(260);
delayMicroseconds(5320);
pulseIR(260);
  }
