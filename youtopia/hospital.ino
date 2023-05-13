int HOSPITAL_THRESHOLD = 20;
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

    if (data > HOSPITAL_THRESHOLD) {
      // Serial.println("hospital registered");
      Serial.println(HOSPITAL_ID);
      sensorCharacteristic.writeValue(HOSPITAL_ID);
    }
    apds2.clearInterrupt();
  }
}