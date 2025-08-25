#include <Arduino.h>

// Basic demo for readings from Adafruit SCD30
#include <Adafruit_SCD30.h>
#include "TCA9548.h"
#include <stdio.h>
#include <Wire.h>
#include <LiquidCrystal.h>
//#include <AsyncTCP.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoOTA.h>
#define   CONTRAST_PIN   9
#define   BACKLIGHT_PIN  7
#define   CONTRAST       110

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2, BACKLIGHT_PIN, POSITIVE );


Adafruit_SCD30  scd30;


TCA9548 MP(0x70);

uint8_t channels = 0;



// login
// WLAN SSID und Password
const char *host = "esp32";
const char *ssid = "5GH";
const char *password = "112330720040719440";


void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit SCD30 test!");

  // Try to initialize!
  if (!scd30.begin()) {
    Serial.println("Failed to find SCD30 chip");
    while (1) { delay(10); }
  }
  Serial.println("SCD30 Found!");


  // if (!scd30.setMeasurementInterval(10)){
  //   Serial.println("Failed to set measurement interval");
  //   while(1){ delay(10);}
  // }
  Serial.print("Measurement Interval: "); 
  Serial.print(scd30.getMeasurementInterval()); 
  Serial.println(" seconds");

// Switch on the backlight and LCD contrast levels
  pinMode(CONTRAST_PIN, OUTPUT);
  analogWrite ( CONTRAST_PIN, CONTRAST );

  //lcd.setBacklightPin ( BACKLIGHT_PIN, POSITIVE );
  //lcd.setBacklight ( HIGH );
  //lcd.backlight();
    
  //lcd.begin(16,4);               // initialize the lcd 



 // lcd.home ();                   // go home
//  lcd.print("Hello, ARDUINO ");  
 // lcd.setCursor ( 0, 1 );        // go to the next line
//  lcd.print (" FORUM - fm   ");      

}

void loop() {
  if (scd30.dataReady()){
    Serial.println("Data available!");
    Serial.println("");
    delay(5000);

    if (!scd30.read()){ Serial.println("Error reading sensor data"); return; }

    Serial.print("Temperature: ");
    Serial.print(scd30.temperature);
    Serial.println(" degrees C");
    
    Serial.print("Relative Humidity: ");
    Serial.print(scd30.relative_humidity);
    Serial.println(" %");
    
    Serial.print("CO2: ");
    Serial.print(scd30.CO2, 3);
    Serial.println(" ppm");
    Serial.println("");
  } else {
    Serial.println("No data");
    delay(5000);

  }

  delay(10000);
}