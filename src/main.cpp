#include <Arduino.h>

// Basic demo for readings from Adafruit SCD30
#include <Adafruit_SCD30.h>
#include "TCA9548.h"
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