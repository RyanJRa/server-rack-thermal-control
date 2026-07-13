#include <Arduino.h>

#define SENSOR_PIN 32 // ACS712 divided output (GPIO32 is ADC1, safe with Wifi (ADC2))

void setup() {
  Serial.begin(115200);
}

void loop() {

  long sum = 0;

  for (int i = 0; i < 100; i++) {
    sum += analogRead(SENSOR_PIN); // Reads the raw 0-4095 value from the pin
  } 

  int raw = sum / 100; // averages the values out of 100 readings
  float voltage = raw * (3.3 / 4095.0); // Raw ADC pin to ESP32 voltage conversion
  
  float sensorVoltage = voltage / 0.909; // Undoes voltage divider to read sensor output
  
  float current = (sensorVoltage - 2.5) / 0.185; //Undoes sensitivity to get amps
  
  Serial.print("Raw: "); 
  Serial.print(raw); 
  Serial.print(" Voltage: ");
  Serial.print(voltage);
  Serial.print(" Current: ");
  Serial.print(current);
  Serial.println(" A");

  delay(1000); // 1 Hz, KPI sample rate
}