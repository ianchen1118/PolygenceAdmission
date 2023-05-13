
void IIC3Scaner(void) {
  byte error, address;
  int nDevices;

  Serial1.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire3.beginTransmission(address);
    error = Wire3.endTransmission();

    if (error == 0) {
      Serial1.print("I2C device found at address 0x");
      if (address < 16)
        Serial1.print("0");
      Serial1.print(address, HEX);
      Serial1.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial1.print("Unknown error at address 0x");
      if (address < 16)
        Serial1.print("0");
      Serial1.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial1.println("No I2C devices found\n");
  else
    Serial1.println("done\n");

  delay(500);  // wait 5 seconds for next scan
}