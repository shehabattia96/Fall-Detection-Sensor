/*
 * Code written by Shehab Attia
 * Turns IR LED lights on and reads voltage from the Light Dependent Resistors (LDR). 
 * Materials: https://docs.google.com/spreadsheets/d/1NsnAO1yCBl094IOnQEU04WQaSiIHoZ0Vb58qgTnDUq4/edit#gid=544518370 (Prototype 2 sheet)
 * 
 * Circuit voltage divider: LDR should be connected in series with a 200kOhm resistor.
 * Analog pins: A0->A5
 * If using ADC:
  ADS1115 -->  UNO
    VDD        5V
    GND        GND
    SCL        A5 (or SCL)
    SDA        A4 (or SDA)
    ADS1115 library: https://github.com/baruch/ADS1115/
*/

// Script Settings
#define using_ADS1115 false // Are we using an Analog-to-Digital converter (ADS1115)?
#define using_MatrixDisplay false // Matrix display is the LED strip used in headless testing.
#define num_sensors 5

// Variables
float voltage[num_sensors]; //Stores the voltage acquired from analoguePin

// Analog Pin definition
#if using_ADS1115
  #include <ADS1115.h> //From https://github.com/baruch/ADS1115/
  #define LDR_PIN ADS1115_MUX_GND_AIN0
  ADS1115 adc;
  // TODO: Change I2C address of ADS1115 and get values from two devices.
#endif

//Matrix Display 
#if using_MatrixDisplay
  #include "Segment.h"
  #include "Digit.h"
  #include "Display.h"
  const byte digit_pins[4] {6, 9, 10, 0}; // From com1 - com4
  const byte segment_pins[7] {7, 11, 2, 4, 5, 8, 1}; // From a - g (abc...g)
  const byte dp_pin = 3;
  Display d(digit_pins, segment_pins, dp_pin);
  char charBuf[50];
#endif


void setup() {
  // Begin Serial
  Serial.begin(9600);
  // Set pin mode for Matrix display
  #if using_MatrixDisplay
    for (int i = 0; i <= 12; i++) {
      pinMode(i, OUTPUT);
    }
  #endif

  // Configure Analog-to-Digital converter
  #if using_ADS1115
    adc.begin();
    adc.set_data_rate(ADS1115_DATA_RATE_860_SPS);
    adc.set_mode(ADS1115_MODE_CONTINUOUS);
    adc.set_mux(LDR_PIN);
    adc.set_pga(ADS1115_PGA_TWO_THIRDS);
  
    if (adc.trigger_sample() != 0)
            Serial.println("adc read trigger failed (ads1115 not connected?)");
  #endif
}

float getVoltage(long analogReading){
  return analogReading * (5.0 / 1023.0); //Scale analogue value between 0.0 and 5.0
}


void loop() {
  // Read the voltage from A0
  #if using_ADS1115
    voltage[0] = adc.read_sample_float();
    // Print the voltage
    Serial.println(voltage[0]);
  #else
    Serial.print(0);
    Serial.print(" ");
    Serial.print(5);
    for (int i=0;i<num_sensors;i++){
      voltage[i] = getVoltage(analogRead(i));
      Serial.print(" ");
      Serial.print(voltage[i] );
    }
    Serial.println(" ");
  #endif


  // Display on Matrix Display
  #if using_MatrixDisplay
    String(voltage).toCharArray(charBuf, 50);
     d.print( charBuf); // Must be looped!
  #endif
}
