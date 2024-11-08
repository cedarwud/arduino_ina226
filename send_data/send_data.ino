#include <Wire.h>
#include <INA226_WE.h>

// Define I2C addresses for the two INA226 sensors
#define I2C_ADDRESS_1 0x40  // INA226 sensor 1
#define I2C_ADDRESS_2 0x41  // INA226 sensor 2

// Initialize two INA226 sensor objects with different addresses
INA226_WE ina226_1(I2C_ADDRESS_1);
INA226_WE ina226_2(I2C_ADDRESS_2);

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize INA226 Sensor 1
  if (!ina226_1.init()) {
    Serial.println("Failed to init INA226 #1. Check your wiring.");
    while (1) {}
  }
  // Set shunt resistor value (in ohms) and max expected current (in amps)
  ina226_1.setShuntResistor(0.1);  // Replace with your actual shunt resistor value
  ina226_1.setMaxCurrent(3.0);     // Replace with expected maximum current

  // Configure averaging, conversion time, and mode for continuous measurement
  ina226_1.setAverage(INA226_AVERAGES_16); // Adjust as needed
  ina226_1.setConversionTime(INA226_CT_1_1MS);
  ina226_1.setMode(INA226_MODE_CONTINUOUS);

  // Initialize INA226 Sensor 2
  if (!ina226_2.init()) {
    Serial.println("Failed to init INA226 #2. Check your wiring.");
    while (1) {}
  }
  ina226_2.setShuntResistor(0.1);  // Replace with your actual shunt resistor value
  ina226_2.setMaxCurrent(3.0);     // Replace with expected maximum current
  ina226_2.setAverage(INA226_AVERAGES_16);
  ina226_2.setConversionTime(INA226_CT_1_1MS);
  ina226_2.setMode(INA226_MODE_CONTINUOUS);

  Serial.println("INA226 Current Sensor - Data Ready");
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

  // Send the data
  sendData(voltage_V1, current_A1, power_W1, voltage_V2, current_A2, power_W2);

  // Adjust or remove delay as needed for real-time response
  delay(100); // Reducing delay for higher frequency data updates
}

// Function to send JSON data over the serial port
void sendData(float voltage1, float current1, float power1, float voltage2, float current2, float power2) {
  String jsonData = "{\"sensor_1\": {\"voltage\":";
  jsonData += voltage1;
  jsonData += ", \"current\":";
  jsonData += current1;
  jsonData += ", \"power\":";
  jsonData += power1;
  jsonData += ", \"channel\": 0}, \"sensor_2\": {\"voltage\":";
  jsonData += voltage2;
  jsonData += ", \"current\":";
  jsonData += current2;
  jsonData += ", \"power\":";
  jsonData += power2;
  jsonData += ", \"channel\": 1}}";

  Serial.println(jsonData);
}
