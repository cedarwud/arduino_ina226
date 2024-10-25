#include <Wire.h>
#include <INA226_WE.h>

// Define I2C addresses for the two INA226 sensors
#define I2C_ADDRESS_1 0x40  // INA226 sensor 1
#define I2C_ADDRESS_2 0x41  // INA226 sensor 2

// Initialize two INA226 sensor objects with different addresses
INA226_WE ina226_1 = INA226_WE(I2C_ADDRESS_1);
INA226_WE ina226_2 = INA226_WE(I2C_ADDRESS_2);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize INA226 Sensor 1
  if (!ina226_1.init()) {
    Serial.println("Failed to init INA226 #1. Check your wiring.");
    while (1) {}
  }

  // Initialize INA226 Sensor 2
  if (!ina226_2.init()) {
    Serial.println("Failed to init INA226 #2. Check your wiring.");
    while (1) {}
  }

  Serial.println("INA226 Current Sensor - Data Push to Local Server");
}

void loop() {
  // Sensor 1 readings
  float voltage_V1 = ina226_1.getBusVoltage_V();
  float current_A1 = ina226_1.getCurrent_mA();
  float power_W1 = ina226_1.getBusPower();

  // Sensor 2 readings
  float voltage_V2 = ina226_2.getBusVoltage_V();
  float current_A2 = ina226_2.getCurrent_mA();
  float power_W2 = ina226_2.getBusPower();

  // Create a JSON-formatted string with the sensor data for both INA226 sensors
  String jsonData = "{\"sensor_1\": {\"voltage\":";
  jsonData += voltage_V1;
  jsonData += ", \"current\":";
  jsonData += current_A1;
  jsonData += ", \"power\":";
  jsonData += power_W1;
  jsonData += ", \"channel\":";
  jsonData += 0;
  jsonData += "}, \"sensor_2\": {\"voltage\":";
  jsonData += voltage_V2;
  jsonData += ", \"current\":";
  jsonData += current_A2;
  jsonData += ", \"power\":";
  jsonData += power_W2;
  jsonData += ", \"channel\":";
  jsonData += 1;
  jsonData += "}}";

  // Send the JSON data for both sensors over the serial port
  Serial.println(jsonData);

  delay(1000); // Send data every second
}
