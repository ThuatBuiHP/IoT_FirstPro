#include <Arduino.h>

void setup() {
  // Set up serial communication between the ESP32 and the computer at 9600 baud
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly (endless loop)
  Serial.println("Hello World!");
  delay(1000);
}

