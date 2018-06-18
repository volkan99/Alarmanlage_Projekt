
int ledPin = 13;
int pirPin = 8;
int value=0;

void setup() 
  {
  Serial.begin(9600); 
  pinMode(pirPin, INPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  }


void loop() 
 {
    while (Serial.available())
       { 
        value = Serial.read();
       }


    if (value == '1')
    {
      if (digitalRead(pirPin) == HIGH) 
        {
          digitalWrite(ledPin,HIGH);
          while(value == '1')
           {
             tone(9,1000);
             delay(750);
             tone(9,500);
             delay(500);
             noTone(9);

             while (Serial.available())
             { 
              value = Serial.read();
             }
           }
        }
    }

    if (value == '0')
    {
      if(digitalRead(pirPin) == LOW) 
        {
         digitalWrite(ledPin,LOW);
         noTone(9);
        }
    }

 }



