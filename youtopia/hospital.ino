/**
 * Setup
 */
void setupHospital() {
  pinMode(INT_PIN2, INPUT_PULLUP);

  selectI2CChannels(2);
  if (!apds2.begin()) {
    Serial.println("failed to initialize hospital! Please check your wiring.");
  } else Serial.println("hospital initialized!");

  apds2.enableProximity(true);
  apds2.setProximityInterruptThreshold(0, 5);
  apds2.enableProximityInterrupt();
}

/**
 * Check
 */
void checkHospital() {
  selectI2CChannels(2);
  if (!digitalRead(INT_PIN2)) {
    int data = apds2.readProximity();
    // Serial.print("hospital: ");
    // Serial.println(data);

    if (data > 20) {
      Serial.println("hospital registered");
      sensor2Characteristic.writeValue(1);
    }
    apds2.clearInterrupt();
  }
}