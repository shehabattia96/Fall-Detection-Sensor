/*
 * Code written by Shehab Attia
 * Turns IR LED lights on and reads voltage from the Light Dependent Resistors (LDR). 
 * Materials: https://docs.google.com/spreadsheets/d/1NsnAO1yCBl094IOnQEU04WQaSiIHoZ0Vb58qgTnDUq4/edit#gid=544518370 (Prototype 2 sheet)
 * 
 * LDR should be connected in series with a 200kOhm resistor.
 * IR LED should be connected in series with a 100 ohm resistor.
 */

#define LED_PIN 5
#define LDR_PIN A0
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,HIGH); // Turn LED On
}

float getVoltage(long analogReading){
  return analogReading * (5.0 / 1023.0); //Scale analogue value between 0.0 and 5.0
}

float voltage; //Stores the voltage acquired from analoguePin
void loop() {
    // read the input on analog pin and convert it to a voltage:
    voltage = getVoltage(analogRead(LDR_PIN));

    Serial.println(voltage);
}
