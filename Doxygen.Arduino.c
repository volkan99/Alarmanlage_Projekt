/** @date 24.06.2018
 *  @mainpage Dokumentation
 *  
 *  
 *  @section sec1 Grundlagen der Informatik
 *  Dies ist das Projekt für Grundlagen der Informatik und
 *  beinhaltet sowohl Code geschrieben mit Python als auch mit C.
 *  Es soll eine Grafische Benutzeroberfläche aufweisen, eine W-Lan
 *  Verbindung erstellen können und mit dem Arduino zusammen arbeiten.
 *  
 *  @section sec2 Das Projekt
 *  Das Projekt kommt einer richtigen Alarmanlage nahe.
 *  Der Aufbau ist nicht kompliziert. Zwei LEDs, ein active Buzzer und
 *  ein PIR-Sensor werden mit dem Arduino verbunden. Um nicht am Laptop 
 *  oder ähnliches gebunden zu sein, versorgt man den Arduino mit Strom über einer Power Bank.
 *  Wenn nun der PIR-Sensor Wärme sieht, werden die LEDs und der Buzzer aktiviert.
 *  Diesen PIR-Sensor 'aktivieren' und 'deaktivieren' wir mithilfe 
 *  einer Python GUI.
 *  
 *  
 *   
 *  @section sec3 Python Code 
 *  
 *  Python_Code_Aufbau beschreibt den groben Aufbau des Codes
 *  
 *  @author Volkan  Yigitbas
 *  @author Guerkan Yigitbas
 * 
 *  
 *  
 */


#include <SoftwareSerial.h>
#include "DumbServer.h"

/** Erstellen des ESP-Servers. Wird zur drahtlosen Verbindung benötigt*/
SoftwareSerial esp_serial(3, 2);
EspServer esp_server;

/** Pin 13 wird eine LED zugewiesen
*/
int ledPin1 = 13;
/** Pin 12 wird eine weitere LED zugewiesen
 */
int ledPin2 = 12;
/** An Pin 8 soll der PIR-Sensor angeschlossen werden.
 */
int pirPin = 8;
/** Dieser String wird benutz, um ausgelese Werte zu speichern
 */
String value="0";

/**
 * @brief Im void setup werden einmalig Sachen ausgeführt.
 * 
 * Zunächst wird eine Verbindung zum ESP-Server und dem Handy HotSpot aufgebaut.
 * Des weitern werden die LED-Pins als OUTPUT gesetzt und auf LOW gestellt.
 * Zudem wird der PIR-Pin als INPUT festgelegt
 */

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

/**
 * @brief Im void loop wird auf eine Aktion in Python gewartet
 * 
 * mit \code while(esp_server.available())\endcode wird ständig nach Daten gesucht. 
 * Sobald etwas empfangen wurde, wird mit \code value = esp_server.readStringUntil('\n');\endcode
 * dieser in der Variable "value" gespeichert.
 * Wenn dieser Wert 1 ist, wird auf eine Reaktion des PIR-Sensors gewartet.
 * Wenn dieser Wärme sieht, also auf HIGH umsteigt, werden die LEDs auf
 * HIGH gestellt und leuchten. Danach wird in einer Schleife ein active Buzzer
 * abwechselnd in unterschiedlichen Frequenzen ertönen und bereit gemacht Daten zu empfangen.
 * Wenn eine 0 empfangen wird, werden die LEDs, der Buzzer und der PIR-Sensor 
 * ausgeschaltet.
 */

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


