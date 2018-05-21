#include <DHT.h>
#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(3,2);

//defining of Pin
#define DHTPIN 7
#define DHTTYPE DHT11
#define mot1 12
#define mot2 11
#define ledPin 10
#define ledPin2 6
#define pirPin 4
#define sender 8

//flag
int flag = 0;

//dht Intialize
DHT dht(DHTPIN, DHTTYPE);

void setup() {
 pinMode(mot1,OUTPUT);
 pinMode(mot2,OUTPUT);
 pinMode(ledPin,OUTPUT);
 pinMode(ledPin2,OUTPUT);
 pinMode(pirPin,INPUT);

 pinMode(sender,OUTPUT);
 digitalWrite(ledPin2,LOW);
 digitalWrite(mot2,LOW);
 Serial.begin(9600);
 ArduinoUno.begin(4800);
 dht.begin();
}
void automation()
{
    float valTemp = dht.readTemperature();
    Serial.println(valTemp);
    if(valTemp > 25)
    {
      digitalWrite(mot1,HIGH);
      Serial.println("Fan is Working");
    }
    int ldrValue = analogRead(A0);
    int ledGlow = 1024 - ldrValue;
    if(ldrValue > 700)
    {
      ledGlow = 0;
    }
    analogWrite(ledPin,ledGlow);
    Serial.println(ldrValue);
    Serial.println("Led working");
}

void pirState()
{
  int out_pir = digitalRead(pirPin);
  Serial.print("valu of o is ");
  Serial.println(out_pir);
  if(out_pir == 1)
    {
		Serial.println(1);
    }
    
}

void loop() {
  //automation();
  Serial.println("Intialized");
while(ArduinoUno.available()>0){
  float val = ArduinoUno.parseFloat();
  if(ArduinoUno.read()== '\n'){
    Serial.println(val);
    if(val == 10)
  {
    automation();
    Serial.println("Lights on");
  }
  else{
    digitalWrite(mot1,LOW);
    analogWrite(ledPin,0);
    pirState();
    Serial.println("Pir");
  }
  }
}
}


