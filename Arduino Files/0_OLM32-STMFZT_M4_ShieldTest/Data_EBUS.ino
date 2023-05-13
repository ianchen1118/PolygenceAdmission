/*
#define EBUS_MOSI PB15
#define EBUS_MISO PB14
#define EBUS_SCK PB13
#define EBUS_NSS PB12
#define EBUS_TX PD8
#define EBUS_RX PD9
#define EBUS_INT_L PD10
#define EBUS_Sync_L PD11
*/

void EBUS_Setup(void) {

  Serial3.begin(1500000);
  Serial3.println("This is EBUS_UART(Serial3) Test, baud rate is 1500000");

  pinMode(EBUS_INT_L, OUTPUT);   //INPUT
  pinMode(EBUS_Sync_L, OUTPUT);  //INPUT

  pinMode(EBUS_MOSI, OUTPUT);  //OUTPUT
  pinMode(EBUS_MISO, OUTPUT);  //OUTPUT
  pinMode(EBUS_SCK, OUTPUT);   //OUTPUT
  pinMode(EBUS_NSS, OUTPUT);   //OUTPUT
}

void Data_EBUS_Setup(void) {

  // Serial3.begin(115200);
  // Serial3.println("This is EBUS_UART(Serial3) Test, baud rate is 115200");

  Serial1.println("Data_EBUS_Setup");
  EBUS1Serial.begin(115200);
  Serial1.println("9600");
  EBUS1Serial.println("This is EBUS1Serial(Software) Test, baud rate is 115200");
  Serial1.println("DONE1");
  EBUS2Serial.begin(115200);
  EBUS2Serial.println("This is EBUS2Serial(Software) Test, baud rate is 115200");
  Serial1.println("DONE2");
  EBUS3Serial.begin(115200);
  EBUS3Serial.println("This is EBUS3Serial(Software) Test, baud rate is 115200");
  Serial1.println("DONE3");
  EBUS4Serial.begin(115200);
  EBUS4Serial.println("This is EBUS4Serial(Software) Test, baud rate is 115200");
  Serial1.println("DONE4");

  pinMode(Data_EBUS1_INT_L, OUTPUT);   //INPUT
  pinMode(Data_EBUS1_Sync_L, OUTPUT);  //INPUT
  pinMode(Data_EBUS2_INT_L, OUTPUT);   //INPUT
  pinMode(Data_EBUS2_Sync_L, OUTPUT);  //INPUT
  pinMode(Data_EBUS3_INT_L, OUTPUT);   //INPUT
  pinMode(Data_EBUS3_Sync_L, OUTPUT);  //INPUT
  pinMode(Data_EBUS4_INT_L, OUTPUT);   //INPUT
  pinMode(Data_EBUS4_Sync_L, OUTPUT);  //INPUT

  pinMode(Data_EBUS1_NSS, OUTPUT);  //OUTPUT
  digitalWrite(Data_EBUS1_NSS, HIGH);
  pinMode(Data_EBUS2_NSS, OUTPUT);  //OUTPUT
  digitalWrite(Data_EBUS2_NSS, HIGH);
  pinMode(Data_EBUS3_NSS, OUTPUT);  //OUTPUT
  digitalWrite(Data_EBUS3_NSS, HIGH);
  pinMode(Data_EBUS4_NSS, OUTPUT);  //OUTPUT
  digitalWrite(Data_EBUS4_NSS, HIGH);
}

void EBUS_Test(void) {

  Serial3.println("This is EBUS_UART(Serial3) Test, baud rate is 1500000");

  digitalWrite(EBUS_INT_L, HIGH);
  digitalWrite(EBUS_Sync_L, HIGH);
  digitalWrite(EBUS_MOSI, HIGH);
  digitalWrite(EBUS_MISO, HIGH);
  digitalWrite(EBUS_SCK, HIGH);
  digitalWrite(EBUS_NSS, HIGH);

  digitalWrite(EBUS_INT_L, LOW);
  digitalWrite(EBUS_Sync_L, LOW);
  digitalWrite(EBUS_MOSI, LOW);
  digitalWrite(EBUS_MISO, LOW);
  digitalWrite(EBUS_SCK, LOW);
  digitalWrite(EBUS_NSS, LOW);
}

void Data_EBUS_Test(void) {

  digitalWrite(Data_EBUS_MOSI, HIGH);
  digitalWrite(Data_EBUS_MISO, HIGH);
  digitalWrite(Data_EBUS_SCK, HIGH);
  delay(1);
  digitalWrite(Data_EBUS_MOSI, LOW);
  digitalWrite(Data_EBUS_MISO, LOW);
  digitalWrite(Data_EBUS_SCK, LOW);

  EBUS1Serial.println("This is EBUS1Serial(Software) Test, baud rate is 115200");
  EBUS2Serial.println("This is EBUS2Serial(Software) Test, baud rate is 115200");
  EBUS3Serial.println("This is EBUS3Serial(Software) Test, baud rate is 115200");
  EBUS4Serial.println("This is EBUS4Serial(Software) Test, baud rate is 115200");

  digitalWrite(Data_EBUS1_INT_L, HIGH);
  digitalWrite(Data_EBUS1_Sync_L, HIGH);
  digitalWrite(Data_EBUS1_NSS, HIGH);
  delay(1);
  digitalWrite(Data_EBUS1_INT_L, LOW);
  digitalWrite(Data_EBUS1_Sync_L, LOW);
  digitalWrite(Data_EBUS1_NSS, LOW);
  delay(1);

  digitalWrite(Data_EBUS2_INT_L, HIGH);
  digitalWrite(Data_EBUS2_Sync_L, HIGH);
  digitalWrite(Data_EBUS2_NSS, HIGH);
  delay(1);
  digitalWrite(Data_EBUS2_INT_L, LOW);
  digitalWrite(Data_EBUS2_Sync_L, LOW);
  digitalWrite(Data_EBUS2_NSS, LOW);
  delay(1);

  digitalWrite(Data_EBUS3_INT_L, HIGH);
  digitalWrite(Data_EBUS3_Sync_L, HIGH);
  digitalWrite(Data_EBUS3_NSS, HIGH);
  delay(1);
  digitalWrite(Data_EBUS3_INT_L, LOW);
  digitalWrite(Data_EBUS3_Sync_L, LOW);
  digitalWrite(Data_EBUS3_NSS, LOW);
  delay(1);

  digitalWrite(Data_EBUS4_INT_L, HIGH);
  digitalWrite(Data_EBUS4_Sync_L, HIGH);
  digitalWrite(Data_EBUS4_NSS, HIGH);
  delay(1);
  digitalWrite(Data_EBUS4_INT_L, LOW);
  digitalWrite(Data_EBUS4_Sync_L, LOW);
  digitalWrite(Data_EBUS4_NSS, LOW);
  delay(1);
}
