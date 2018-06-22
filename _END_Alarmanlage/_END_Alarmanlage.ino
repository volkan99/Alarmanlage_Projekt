

#include <SoftwareSerial.h>
#include "DumbServer.h"

SoftwareSerial esp_serial(3, 2);
EspServer esp_server;


int ledPin1 = 13;
int ledPin2 = 12;
int pirPin = 8;
String value="0";


void setup()
{ 
  esp_serial.begin(9600);
  
  esp_server.begin(&esp_serial, "iPhone", "Yigitbas1", 30303);

  pinMode(pirPin, INPUT);
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  
  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);

}


void loop()
{
  while(esp_server.available()) 
   {
    value = esp_server.readStringUntil('\n');
   }


   if (value == "1")
   {
      if (digitalRead(pirPin) == HIGH) 
      {
       digitalWrite(ledPin1,HIGH);
       digitalWrite(ledPin2,HIGH);
       
       while(value == "1")
       {
        tone(9,750);
        delay(200);
        tone(9,100);
        delay(200);
        noTone(9);
        
        while (esp_server.available())
        {  
          value = esp_server.readStringUntil('\n');
        }
        
       }
      }
   }

   if (value == "0")
   {
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,LOW);
    noTone(9);
    digitalWrite(pirPin,LOW);
   }
}


