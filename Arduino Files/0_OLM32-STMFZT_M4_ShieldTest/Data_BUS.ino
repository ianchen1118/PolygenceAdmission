/*
#define BUS_SDA PB11
#define BUS_SCL PB10
#define BUS_INT_G PE12
#define BUS_Sync_G PE15
#define BUS_PWMA PE13
#define BUS_PWMB PE14
*/

void BUS_Setup(void) {

  // Wire2.begin();
  // pinMode(BUS_SDA, OUTPUT);
  // pinMode(BUS_SCL, OUTPUT);

  pinMode(BUS_INT_G, OUTPUT);
  pinMode(BUS_Sync_G, OUTPUT);
  pinMode(BUS_PWMA, OUTPUT);
  pinMode(BUS_PWMB, OUTPUT);
}

void Data_BUS_Setup(void) {

  Wire1.begin();
  // Wire1.setClock(400000UL);
  // pinMode(BUS_SDA, OUTPUT);
  // pinMode(BUS_SCL, OUTPUT);

  pinMode(Data_BUS_INT_G, OUTPUT);
  pinMode(Data_BUS_Sync_G, OUTPUT);
  digitalWrite(Data_BUS_INT_G, HIGH);
  digitalWrite(Data_BUS_Sync_G, HIGH);
  pinMode(Data_BUS_PWMA, OUTPUT);
  pinMode(Data_BUS_PWMB, OUTPUT);
}

void BUS_Test(void) {
  // Wire2.beginTransmission(0x60);
  // Wire2.write(0x11);
  // Wire2.endTransmission(true);

  // Wire2.requestFrom(0x60, 1);
  // while (Wire2.available())
  // {
  //   Wire2.read();
  // }
  // delay(500);
  // digitalWrite(BUS_SDA, HIGH);
  // digitalWrite(BUS_SCL, HIGH);
  // digitalWrite(BUS_SDA, LOW);
  // digitalWrite(BUS_SCL, LOW);

  digitalWrite(BUS_INT_G, HIGH);
  digitalWrite(BUS_Sync_G, HIGH);
  digitalWrite(BUS_PWMA, HIGH);
  digitalWrite(BUS_PWMB, HIGH);

  digitalWrite(BUS_INT_G, LOW);
  digitalWrite(BUS_Sync_G, LOW);
  digitalWrite(BUS_PWMA, LOW);
  digitalWrite(BUS_PWMB, LOW);
}

void Data_BUS_Test(void) {
  Wire1.beginTransmission(0x60);
  Wire1.write(0x11);
  Wire1.endTransmission(true);

  Wire1.requestFrom(0x60, 1);
  while (Wire1.available()) {
    Wire1.read();
  }
  delay(500);

  digitalWrite(BUS_INT_G, HIGH);
  digitalWrite(BUS_Sync_G, HIGH);
  digitalWrite(BUS_PWMA, HIGH);
  digitalWrite(BUS_PWMB, HIGH);
  delay(1);
  digitalWrite(BUS_INT_G, LOW);
  digitalWrite(BUS_Sync_G, LOW);
  digitalWrite(BUS_PWMA, LOW);
  digitalWrite(BUS_PWMB, LOW);
}