void setupBLE() {
  if (!BLE.begin()) {
    while (true)
      ;
  }

  // Set up Youtopia Bluetooth service
  BLE.setLocalName(CITY_NAME);
  BLE.setDeviceName(CITY_NAME);
  BLE.setAdvertisedService(cityService);

  // Infrastructure characteristic
  sensor0Characteristic.addDescriptor(sensor0Descriptor);
  sensor1Characteristic.addDescriptor(sensor1Descriptor);
  sensor2Characteristic.addDescriptor(sensor2Descriptor);
  sensor3Characteristic.addDescriptor(sensor3Descriptor);
  sensor4Characteristic.addDescriptor(sensor4Descriptor);
  sensor5Characteristic.addDescriptor(sensor5Descriptor);
  
  cityService.addCharacteristic(sensor0Characteristic);
  cityService.addCharacteristic(sensor1Characteristic);
  cityService.addCharacteristic(sensor2Characteristic);
  cityService.addCharacteristic(sensor3Characteristic);
  cityService.addCharacteristic(sensor4Characteristic);
  cityService.addCharacteristic(sensor5Characteristic);

  sensor0Characteristic.writeValue(0);
  sensor1Characteristic.writeValue(0);
  sensor2Characteristic.writeValue(0);
  sensor3Characteristic.writeValue(0);
  sensor4Characteristic.writeValue(0);
  sensor5Characteristic.writeValue(0);

  BLE.addService(cityService);
  BLE.advertise(); 
}
