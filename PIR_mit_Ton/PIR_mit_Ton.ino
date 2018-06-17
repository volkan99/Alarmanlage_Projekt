
int ledPin = 13;
int pirPin = 8;



void setup() 
{
  pinMode(pirPin, INPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
}


void loop() 
{
  
 if (digitalRead(pirPin) == HIGH) {
    digitalWrite(ledPin,HIGH);

    while(digitalRead(pirPin) == HIGH)
    {
    tone(9,750);
    delay(750);
    tone(9,100);
    delay(500);
    noTone(9);

    digitalRead(pirPin);
   }
 }



 if(digitalRead(pirPin) == LOW) 
  {
    digitalWrite(ledPin,LOW);
    noTone(9);
  }


}



