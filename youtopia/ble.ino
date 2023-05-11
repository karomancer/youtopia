void setupBLE() {
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (true)
      ;
  }

  BLE.setLocalName(CITY_NAME);
  BLE.setDeviceName(CITY_NAME);
  BLE.setAdvertisedService(cityService);

  // sensorCharacteristic.addDescriptor(sensorDescriptor);
  cityService.addCharacteristic(sensorCharacteristic);
  sensorCharacteristic.writeValue(0);

  BLE.addService(cityService);
  BLE.advertise(); 
}
