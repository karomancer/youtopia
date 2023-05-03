int COURTHOUSE_THRESHOLD = 28;

/**
 * Setup
 */
void setupCourthouse() {
  pinMode(INT_PIN4, INPUT_PULLUP);

  selectI2CChannels(4);
  if (!apds4.begin()) {
    Serial.println("failed to initialize courthouse! Please check your wiring.");
  } else Serial.println("courthouse initialized!");

  apds4.enableProximity(true);
  apds4.setProximityInterruptThreshold(0, 1);
  apds4.enableProximityInterrupt();
}

/**
 * Check
 */
void checkCourthouse() {
  selectI2CChannels(4);
  if (!digitalRead(INT_PIN4)) {
    int data = apds4.readProximity();
    // Serial.print("courthouse: ");
    // Serial.println(data);

    if (data > COURTHOUSE_THRESHOLD) {
      Serial.println("courthouse registered");
      sensorCharacteristic.writeValue(COURTHOUSE_ID);
    }
    apds4.clearInterrupt();
  }
}