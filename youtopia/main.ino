void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("set up begin");

  setupNature();
  setupMarket();
  setupHospital();
  setupInfrastructure();
  setupCourthouse();
  setupSchool();

  setupBLE();

  Serial.println("set up done");
}

void loop() {
  BLEDevice central = BLE.central();

  // if (central) {
    // Serial.println("Connected to central");
    // while (central.connected()) {
      checkNature();
      checkMarket();
      checkHospital();
      checkInfrastructure();
      checkCourthouse();
      checkSchool();
    // }
  // }

  delay(100);
}
