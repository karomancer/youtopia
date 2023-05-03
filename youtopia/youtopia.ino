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

const char* CITY_NAME = "Youtopia";
const char* CITY_UUID = "2d32cb10-dd61-11ed-b5ea-0242ac120002";

const char* S0_UUID = "e9985dc9-f6c5-44ab-83b8-1dcd02b9c01a";
const char* S1_UUID = "e9985dc9-f6c5-44ab-83b8-1dcd02b9c01b";
const char* S2_UUID = "e9985dc9-f6c5-44ab-83b8-1dcd02b9c01c";
const char* S3_UUID = "e9985dc9-f6c5-44ab-83b8-1dcd02b9c01d";
const char* S4_UUID = "e9985dc9-f6c5-44ab-83b8-1dcd02b9c01e";
const char* S5_UUID = "e9985dc9-f6c5-44ab-83b8-1dcd02b9c01f";

BLEService cityService(CITY_UUID);  // create service

BLEByteCharacteristic sensor0Characteristic(S0_UUID, BLERead | BLENotify);
BLEByteCharacteristic sensor1Characteristic(S1_UUID, BLERead | BLENotify);
BLEByteCharacteristic sensor2Characteristic(S2_UUID, BLERead | BLENotify);
BLEByteCharacteristic sensor3Characteristic(S3_UUID, BLERead | BLENotify);
BLEByteCharacteristic sensor4Characteristic(S4_UUID, BLERead | BLENotify);
BLEByteCharacteristic sensor5Characteristic(S5_UUID, BLERead | BLENotify);

BLEDescriptor sensor0Descriptor("2901", "Infrastructure");
BLEDescriptor sensor1Descriptor("2901", "School");
BLEDescriptor sensor2Descriptor("2901", "Hospital");
BLEDescriptor sensor3Descriptor("2901", "Market");
BLEDescriptor sensor4Descriptor("2901", "Nature");
BLEDescriptor sensor5Descriptor("2901", "Courthouse");

void selectI2CChannels(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(MUX_Address);
  Wire.write(1 << i);
  Wire.endTransmission();
}
