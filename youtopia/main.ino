void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("set up begin");

  setupBLE();

  setupNature();
  setupMarket();
  setupHospital();
  setupInfrastructure();
  setupCourthouse();
  setupSchool();

  Serial.println("set up done");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    checkNature();
    checkMarket();
    checkHospital();
    checkInfrastructure();
    checkCourthouse();
    checkSchool();
  }

  delay(100);
}
