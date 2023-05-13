/*
#define SCL1 PB6
#define SDA1 PB7
#define MISO1 PB4
#define MOSI1 PB5
#define SCK1 PB3
#define PG13__CTS6 PG13
#define PG14__TX6 PG14
#define PG12__RTS6 PG12
#define PG9__RX6 PG9
#define RX5 PD2
#define NSS1 PA15
#define TX5 PC12
#define PC9__PWM8_4__SDA3 PC9
#define PA8__SCL3 PA8
#define PG7__CK6 PG7
*/

void Communication_Setup(void) {
  Serial5.begin(115200);
  Serial5.println("This is Serial5 Test, baud rate is 115200");

  Serial6.begin(460800);
  Serial6.println("This is Serial6 Test, baud rate is 460800");

  Wire1.begin();
  Wire3.begin();
}

void Interface_Setup(void) {
  Serial.begin();
  Serial.println("This is a USB test, which has very fast speed");
  Serial1.begin(1500000);
  Serial1.println("This is Serial1 Test, baud rate is 1500000");
  Serial2.begin(2000000);
  Serial2.println("This is Serial2(High Speed) Test, baud rate is 2000000");
  // Serial4.begin(115200);
  // Serial4.println("This is Serial4 Test, baud rate is 115200");
}

void Interface_Test(void) {
  Serial.println("This is a USB test, which has very fast speed");
  Serial1.println("This is Serial1 Test, baud rate is 1500000");
  Serial2.println("This is Serial2(High Speed) Test, baud rate is 2000000");
  //Serial4.println("This is Serial4 Test, baud rate is 115200");
}
