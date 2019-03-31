//References https://www.tutorialspoint.com/arduino/arduino_ultrasonic_sensor.htm 
#define pingPin  10 //Trig
#define echoPin  9 //Echo

void setup() {
  Serial.begin (9600);
   pinMode(echoPin, INPUT);
   pinMode(pingPin, OUTPUT);
}

long duration, inches, cm;
void loop() {  
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   if (cm<2000){
     Serial.print(0);
     Serial.print(" ");
     Serial.print(400); //Max range in cm
     Serial.print(" ");
     Serial.print(inches);
     Serial.print(" in, ");
     Serial.print(cm);
     Serial.print("cm");
     Serial.println();
   }
   delay(500);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
