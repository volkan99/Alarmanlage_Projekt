
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
  //int s = digitalRead(pirPin);
  //digitalWrite(ledPin, s);
  
 if (digitalRead(pirPin) == HIGH) 
   {
    digitalWrite(ledPin,HIGH);
   }



 if(digitalRead(pirPin) == LOW) 
   {
    digitalWrite(ledPin,LOW);
   }

}



