int NATURE_THRESHOLD = 40;
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

    if (data > NATURE_THRESHOLD) {
      Serial.println("market registered");
      sensorCharacteristic.writeValue(MARKET_ID);
    }
    apds1.clearInterrupt();
  }
}