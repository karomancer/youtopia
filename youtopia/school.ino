/**
 * Setup
 */
void setupSchool() {
  pinMode(INT_PIN5, INPUT_PULLUP);

  selectI2CChannels(5);
  if (!apds5.begin()) {
    Serial.println("failed to initialize school! Please check your wiring.");
  } else Serial.println("school initialized!");

  apds5.enableProximity(true);
  apds5.setProximityInterruptThreshold(0, 5);
  apds5.enableProximityInterrupt();
}

/**
 * Check
 */
void checkSchool() {
  selectI2CChannels(5);
  if (!digitalRead(INT_PIN5)) {
    int data5 = apds5.readProximity();
    // Serial.print("school: ");
    // Serial.println(apds5.readProximity());

    if (data5 > 50) {
      Serial.println("school registered");
      sensor5Characteristic.writeValue(1);
    }
    apds5.clearInterrupt();
  }
}