

#include <SoftwareSerial.h>
#include "DumbServer.h"

SoftwareSerial esp_serial(3, 2);
EspServer esp_server;






/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
/* Set this to a bigger number, to enable sending longer messages */
#define BLYNK_MAX_SENDBYTES 128

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a905b11d42104925b8021ac83fb7555c";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iPhone";
char pass[] = "Yigitbas1";

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(3, 2); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

void emailOnButtonPress()
{
 // *** WARNING: You are limited to send ONLY ONE E-MAIL PER 15 SECONDS! ***

 // Let's send an e-mail when you press the button
 // connected to digital pin 2 on your Arduino

int isButtonPressed = !digitalRead(11); // Invert state, since button is "Active LOW"

 if (digitalRead(11) == HIGH) // You can write any condition to trigger e-mail sending
 {
   Serial.println("Button is pressed."); // This can be seen in the Serial Monitor
   Blynk.email("guerkan.yigitbas@web.de", "Subject: Button Logger", "You just pushed the button...");

   // Or, if you want to use the email specified in the App (like for App Export):
   //Blynk.email("Subject: Button Logger", "You just pushed the button...");
 }
}






void setup()
{
  Serial.begin(9600);
  esp_serial.begin(9600);
  
  Serial.println("Starting server...");
  esp_server.begin(&esp_serial, "iPhone", "Yigitbas1", 30303);
  Serial.println("...server is running");


  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  Blynk.begin(auth, wifi, ssid, pass);
  Blynk.email("guerkan.yigitbas@web.de", "Subject", "My Blynk project is online.");

 // Setting the button
 pinMode(11, INPUT);//_PULLUP);
 // Attach pin 2 interrupt to our handler
 attachInterrupt(digitalPinToInterrupt(11), emailOnButtonPress, CHANGE);
}


void loop()
{
 emailOnButtonPress();
 Blynk.run();
}


