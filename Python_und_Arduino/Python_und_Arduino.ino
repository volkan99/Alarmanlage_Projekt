int led=13;
int wert=0;

void setup() 
   { 
      Serial.begin(9600); 
      pinMode(led, OUTPUT);
      digitalWrite (led, LOW);
      Serial.println("Verbindungsaufbau...");
   }
 
void loop() 
   {
     while (Serial.available())
        {
           wert = Serial.read();
        }
     
     if (wert == '1')
        digitalWrite (led, HIGH);
     
     else if (wert == '0')
        digitalWrite (led, LOW);
   }
