int INFRA_THRESHOLD = 25;
/**
 * Setup
 */
void setupInfrastructure() {
  pinMode(INT_PIN, INPUT_PULLUP);

  selectI2CChannels(3);
  if (!apds.begin()) {
    Serial.println("failed to initialize infrastructure! Please check your wiring.");
  } else Serial.println("infrastructure initialized!");

  apds.enableProximity(true);
  apds.setProximityInterruptThreshold(0, 5);
  apds.enableProximityInterrupt();
}

/**
 * Check
 */
void checkInfrastructure() {
  selectI2CChannels(3);
  if (!digitalRead(INT_PIN3)) {
    int data = apds.readProximity();
    // Serial.print("infrastructure: ");
    // Serial.println(data);

    if (data > INFRA_THRESHOLD) {
      Serial.println("infrastructure registered");
      sensorCharacteristic.writeValue(INFRA_ID);
    }
    apds.clearInterrupt();
  }
}