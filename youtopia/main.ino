void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("set up begin");

  pinMode(INT_PIN, INPUT_PULLUP);
  pinMode(INT_PIN1, INPUT_PULLUP);
  pinMode(INT_PIN2, INPUT_PULLUP);
  pinMode(INT_PIN3, INPUT_PULLUP);
  pinMode(INT_PIN4, INPUT_PULLUP);
  pinMode(INT_PIN5, INPUT_PULLUP);

  ////////////////////////////////////
  //////////////  APDS0 //////////////
  ////////////////////////////////////
  selectI2CChannels(0);
  if (!apds.begin()) {
    Serial.println("failed to initialize APDS! Please check your wiring.");
  } else Serial.println("APDS initialized!");


  apds.setProximityInterruptThreshold(0, 5);
  //enable proximity mode
  apds.enableProximity(true);

  //enable the proximity interrupt
  apds.enableProximityInterrupt();

  ////////////////////////////////////
  //////////////  APDS1 //////////////
  ////////////////////////////////////
  selectI2CChannels(1);
  if (!apds1.begin()) {
    Serial.println("failed to initialize APDS1! Please check your wiring.");
  } else Serial.println("APDS1 initialized!");

  //enable proximity mode
  apds1.enableProximity(true);

  apds1.setProximityInterruptThreshold(0, 5);

  //enable the proximity interrupt
  apds1.enableProximityInterrupt();

  ////////////////////////////////////
  //////////////  APDS2 //////////////
  ////////////////////////////////////
  selectI2CChannels(2);
  if (!apds2.begin()) {
    Serial.println("failed to initialize APDS2! Please check your wiring.");
  } else Serial.println("APDS2 initialized!");

  //enable proximity mode
  apds2.enableProximity(true);

  apds2.setProximityInterruptThreshold(0, 5);

  //enable the proximity interrupt
  apds2.enableProximityInterrupt();

  // //  ////////////////////////////////////
  // //  //////////////  APDS3 //////////////
  // //  ////////////////////////////////////

  selectI2CChannels(3);
  if (!apds3.begin()) {
    Serial.println("failed to initialize APDS3! Please check your wiring.");
  } else Serial.println("APDS3 initialized!");

  //enable proximity mode
  apds3.enableProximity(true);

  //enable the proximity interrupt
  apds3.setProximityInterruptThreshold(0, 5);
  apds3.enableProximityInterrupt();

  // //  ////////////////////////////////////
  // //  //////////////  APDS4 //////////////
  // //  ////////////////////////////////////

  selectI2CChannels(4);
  if (!apds4.begin()) {
    Serial.println("failed to initialize APDS4! Please check your wiring.");
  } else Serial.println("APDS4 initialized!");

  //enable proximity mode
  apds4.enableProximity(true);

  apds4.setProximityInterruptThreshold(0, 5);
  //enable the proximity interrupt
  apds4.enableProximityInterrupt();

  // //  ////////////////////////////////////
  // //  //////////////  APDS5 //////////////
  // //  ////////////////////////////////////

  selectI2CChannels(5);
  if (!apds5.begin()) {
    Serial.println("failed to initialize APDS5! Please check your wiring.");
  } else Serial.println("APDS5 initialized!");

  //enable proximity mode
  apds5.enableProximity(true);

  apds5.setProximityInterruptThreshold(0, 5);
  //enable the proximity interrupt
  apds5.enableProximityInterrupt();


  setupBLE();

  Serial.println("set up done");
}

void loop() {
  BLEDevice central = BLE.central();
  // Serial.println(millis());

  //  Serial.println("hello");
  // put your main code here, to run repeatedly:

  if (central) {
    selectI2CChannels(0);
    if (!digitalRead(INT_PIN)) {
      int data0 = apds.readProximity();
      Serial.println(apds.readProximity());
      Serial.print("sensor0: ");

      if (data0 > 200) {
        sensor0Characteristic.writeValue(1);
      }

      //clear the interrupt
      apds.clearInterrupt();
    }

    selectI2CChannels(1);
    if (!digitalRead(INT_PIN1)) {
      int data1 = apds1.readProximity();
      Serial.print("sensor1: ");
      Serial.println(apds1.readProximity());
      
      if (data1 > 200) {
        sensor1Characteristic.writeValue(1);
      }
      //clear the interrupt
      apds1.clearInterrupt();

      sensor1Characteristic.writeValue(1);
    }

    selectI2CChannels(2);
    if (!digitalRead(INT_PIN2)) {
      int data2 = apds2.readProximity();
      Serial.print("sensor2: ");
      Serial.println(apds2.readProximity());

      if (data2 > 200) {
        sensor2Characteristic.writeValue(1);
      }
      //clear the interrupt
      apds2.clearInterrupt();

      sensor2Characteristic.writeValue(1);
    }

    selectI2CChannels(3);
    if (!digitalRead(INT_PIN3)) {
      int data3 = apds3.readProximity();
      Serial.print("sensor3: ");
      Serial.println(apds3.readProximity());

      if (data3 > 200) {
        sensor3Characteristic.writeValue(1);
      }
      //clear the interrupt
      apds3.clearInterrupt();

      sensor3Characteristic.writeValue(1);
    }

    selectI2CChannels(4);
    if (!digitalRead(INT_PIN4)) {
      int data4 = apds4.readProximity();
      Serial.print("sensor4: ");
      Serial.println(apds4.readProximity());

      if (data4 > 200) {
        sensor4Characteristic.writeValue(1);
      }
      //clear the interrupt
      apds4.clearInterrupt();

      sensor4Characteristic.writeValue(1);
    }

    selectI2CChannels(5);
    if (!digitalRead(INT_PIN5)) {
      int data5 = apds5.readProximity();
      Serial.print("sensor5: ");
      Serial.println(apds5.readProximity());
      if (data5 > 200) {
        sensor4Characteristic.writeValue(1);
      }
      //clear the interrupt
      apds5.clearInterrupt();

      sensor5Characteristic.writeValue(1);
    }
  }

  delay(100);
}

void selectI2CChannels(uint8_t i) {

  if (i > 7) return;

  Wire.beginTransmission(MUX_Address);

  Wire.write(1 << i);

  Wire.endTransmission();
}
