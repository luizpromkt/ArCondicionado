// CAPTAR FUNÇÕES DE DIMINUIR E ALMENTAR A POTENCIA DO PARA PARA NÃO TER QUE RESOVLER O PROBLEMA SINEBTE DESLIGANDO E LIGANDO.
// TEMPORIZAR AS AÇÕES DE 5 EM 5 MINUTOS. 




//realtime
#include "Wire.h"
#define DS1307_ADDRESS 0x68
byte zero = 0x00;


#include <Thermistor.h> //INCLUSÃO DA BIBLIOTECA
 
Thermistor temp(2);

int pinled = 12; 
int pinopir = 11; 
int pinledv = 3;
int acionamento;
int IRledPin=13;    
int estado=3;
int estadoAnterior=4;
int temperatura;
const int azul = 4;
const int verde = 10;
const int vermelho = 5; 
String cor;



void setup()
  {
    Wire.begin();
    pinMode(pinled, OUTPUT); 
    pinMode(pinledv, OUTPUT);
    pinMode(IRledPin, OUTPUT); 
    pinMode(pinopir, INPUT);
    Serial.begin(9600);
    pinMode(azul, OUTPUT);
    pinMode(verde, OUTPUT);
    pinMode(vermelho, OUTPUT);
    delay(1000);

   // setDateTime();
  }
 
void loop()
  {


//realtime
  printDate(); // delay(1000);

 //temperatura  
  int temperature = temp.getTemp(); //VARIÁVEL DO TIPO INTEIRO QUE RECEBE O VALOR DE TEMPERATURA CALCULADO PELA BIBLIOTECA
  Serial.print(" Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(temperature); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
  Serial.println("*C "); //IMPRIME O TEXTO NO MONITOR SERIAL
  // delay(1000); //INTERVALO DE 1 SEGUNDO
  acionamento = digitalRead(pinopir);



      if (temperature == 24 ){delay(50); verdeFuncao();}
      if (temperature > 24){delay(50); vermelhoFuncao();}
      if (temperature < 24){delay(50); azulFuncao();}




  if (acionamento == LOW)
    {
    digitalWrite(pinled, LOW);
    digitalWrite(pinledv, LOW);
    Serial.print("Apesar do movimento manter desligado !!! - ");
    estado=0;
    }
  else
    {
      if (temperature >23) {
    digitalWrite(pinled, HIGH);
    digitalWrite(pinledv, HIGH);
    Serial.print("Movimento !!! - ");
    estado=1;
       
    
      }
      else{
    digitalWrite(pinled, LOW);
    digitalWrite(pinledv, LOW);
    Serial.print(" - Parado - ");
    estado=0; }
    }



  if (estado != estadoAnterior)
    {
    SendChannelUpCode();
    estadoAnterior=estado;
    }

    
} 



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

delay(1000);

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
pulseIR(420);}
}



void setDateTime(){

  byte segundo =      00;  //0-59
  byte minuto =        36;  //0-59
  byte hora =           20;  //0-23
  byte diasemana =    2;  //1-7
  byte dia =               18;  //1-31
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

byte decToBcd(byte val){
// Conversão de decimal para binário
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
// Conversão de binário para decimal
  return ( (val/16*10) + (val%16) );
}

void printDate(){

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  int segundo = bcdToDec(Wire.read());
  int minuto = bcdToDec(Wire.read());
  int hora = bcdToDec(Wire.read() & 0b111111);    //Formato 24 horas
  int diasemana = bcdToDec(Wire.read());             //0-6 -> Domingo - Sábado
  int dia = bcdToDec(Wire.read());
  int mes = bcdToDec(Wire.read());
  int ano = bcdToDec(Wire.read());

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
  Serial.print(":");
  Serial.print(segundo);
  Serial.print(" - ");
}
