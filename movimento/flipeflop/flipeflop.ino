//Programa : Sensor de presenca com modulo PIR
//Autor : FILIPEFLOP
 
int pinled = 12; //Pino ligado ao rele
int pinopir = 11; //Pino ligado ao sensor PIR
int pinledv = 3;
int acionamento; //Variavel para guardar valor do sensor
 
void setup()
{
pinMode(pinled, OUTPUT); //Define pino rele como saida
pinMode(pinopir, INPUT); //Define pino sensor como entrada
pinMode(pinledv, OUTPUT); //Define pino sensor como entrada
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
}
else //Caso seja detectado um movimento, aciona o rele
{
digitalWrite(pinled, HIGH);
digitalWrite(pinledv, LOW);
Serial.println("Movimento !!!");
}
}
