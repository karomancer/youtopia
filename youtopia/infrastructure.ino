/**
 * Setup
 */
void setupInfrastructure() {
  pinMode(INT_PIN3, INPUT_PULLUP);

  selectI2CChannels(3);
  if (!apds3.begin()) {
    Serial.println("failed to initialize infrastructure! Please check your wiring.");
  } else Serial.println("infrastructure initialized!");

  apds3.enableProximity(true);
  apds3.setProximityInterruptThreshold(0, 5);
  apds3.enableProximityInterrupt();
}

/**
 * Check
 */
void checkInfrastructure() {
  selectI2CChannels(3);
  if (!digitalRead(INT_PIN3)) {
    int data = apds3.readProximity();
    // Serial.print("infrastructure: ");
    // Serial.println(data);

    if (data > 25) {
      Serial.println("infrastructure registered");
      sensor3Characteristic.writeValue(1);
    }
    apds3.clearInterrupt();
  }
}