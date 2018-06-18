
#define BLYNK_PRINT Serial
#define BLYNK_MAX_SENDBYTES 128

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = "a905b11d42104925b8021ac83fb7555c";
char ssid[] = "iPhone";
char pass[] = "Yigitbas1";

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(3, 2); 
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

void emailOnButtonPress()
{

 if (digitalRead(11) == HIGH) 
 {
   Serial.println("Button is pressed.");
   Blynk.email("guerkan.yigitbas@web.de", "Subject: Button Logger", "You just pushed the button...");

 }
}

void setup()
{
 Serial.begin(9600);

 EspSerial.begin(ESP8266_BAUD);
 delay(10);

 Blynk.begin(auth, wifi, ssid, pass);
 Blynk.email("guerkan.yigitbas@web.de", "Subject", "My Blynk project is online.");
 pinMode(11, INPUT);
 attachInterrupt(digitalPinToInterrupt(11), emailOnButtonPress, CHANGE);
}

void loop()
{
 emailOnButtonPress();
 Blynk.run();
}


