#include <ArduinoBLE.h>

const char* SUUID = "e9985dc9-f6c5-44ab-83b8-1dcd02b9c01a";

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (true)
      ;
  }

  Serial.println("Scanning for Youtopia...");
  BLE.scanForName("Youtopia");
}

void loop() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    Serial.println("Youtopia exists...");
    while (peripheral.connected()) {
    Serial.println("Connected to Youtopia...");
      BLECharacteristic sensorCharacteristic = peripheral.characteristic(SUUID);

      if (sensorCharacteristic.written()) {
        Serial.println("Received value");
        byte value = 0;
        sensorCharacteristic.readValue(value);
        Serial.write(value);
      }
    }
  }
}
