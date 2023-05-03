#include <ArduinoBLE.h>
#include <Wire.h>
#include <Adafruit_APDS9960.h>

#define MUX_Address 0x70  // TCA9548A Encoders address

#define INT_PIN 2
#define INT_PIN1 3
#define INT_PIN2 4
#define INT_PIN3 5
#define INT_PIN4 6
#define INT_PIN5 7

Adafruit_APDS9960 apds;
Adafruit_APDS9960 apds1;
Adafruit_APDS9960 apds2;
Adafruit_APDS9960 apds3;
Adafruit_APDS9960 apds4;
Adafruit_APDS9960 apds5;

int INFRA_ID = 1;
int SCHOOL_ID = 2;
int COURTHOUSE_ID = 3;
int HOSPITAL_ID = 4;
int MARKET_ID = 5;
int NATURE_ID = 6;

const char* CITY_NAME = "Youtopia";
const char* CITY_UUID = "2d32cb10-dd61-11ed-b5ea-0242ac120002";

const char* SUUID = "e9985dc9-f6c5-44ab-83b8-1dcd02b9c01a";

BLEService cityService(CITY_UUID);  // create service

BLEByteCharacteristic sensorCharacteristic(SUUID, BLEWrite | BLENotify);
BLEDescriptor sensorDescriptor("2901", "Sensor Data");

void selectI2CChannels(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(MUX_Address);
  Wire.write(1 << i);
  Wire.endTransmission();
}
