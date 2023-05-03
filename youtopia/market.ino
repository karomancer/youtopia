/**
 * Setup
 */

void setupMarket() {
  pinMode(INT_PIN1, INPUT_PULLUP);

  selectI2CChannels(1);
  if (!apds1.begin()) {
    Serial.println("failed to initialize market! Please check your wiring.");
  } else Serial.println("market initialized!");

  apds1.enableProximity(true);
  apds1.setProximityInterruptThreshold(0, 5);
  apds1.enableProximityInterrupt();
}

/**
 * Check
 */
void checkMarket() {
  selectI2CChannels(1);
  if (!digitalRead(INT_PIN1)) {
    int data = apds1.readProximity();
    // Serial.print("market: ");
    // Serial.println(data);

    if (data > 40) {
      Serial.println("market registered");
      sensor1Characteristic.writeValue(1);
    }
    apds1.clearInterrupt();
  }
}