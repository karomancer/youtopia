/**
 * Setup
 */
void setupNature() {
  pinMode(INT_PIN, INPUT_PULLUP);
  selectI2CChannels(0);
  if (!apds.begin()) {
    Serial.println("failed to initialize nature! Please check your wiring.");
  } else Serial.println("nature initialized!");

  apds.setProximityInterruptThreshold(0, 5);
  apds.enableProximity(true);
  apds.enableProximityInterrupt();
}

/**
 * Check
 */
void checkNature() {
  selectI2CChannels(0);
  if (!digitalRead(INT_PIN)) {
    int data = apds.readProximity();
    // Serial.print("nature: ");
    // Serial.println(data);

    if (data > 15) {
      Serial.println("nature registered");
      sensorCharacteristic.writeValue(NATURE_ID);
    }
    apds.clearInterrupt();
  }
}