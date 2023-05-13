
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <FlashStorage_STM32.h>
#include <SoftwareSerial.h>
#include "OLD_MotorDrive_V100.h"
#include <Servo.h>

/***********************************************************************

//                            GPIO relative

***********************************************************************/

//Left CON
//#define PB9 PB9             //SW3
//#define PB8 PB8             //SW4
//#define PE1 PE1             //SW1
//#define PE0 PE0             //SW2
//#define PE3 PE3             //Data_EBUS3_TX
//#define PE2 PE2             //Data_EBUS3_NSS
#define PE5__PWM9_1 PE5  //Data_EBUS3_INT_L
//#define PE4 PE4             //Data_EBUS3_Sync_L
//#define PC13 PC13           //Data_EBUS1_NSS
#define PE6__PWM9_2 PE6  //Data_EBUS3_RX
//#define PC15 PC15           //Data_EBUS1_Sync_L
//#define PC14 PC14           //Data_EBUS1_TX
//#define PF1 PF1             //Data_EBUS1_RX
//#define PF0 PF0             //Data_EBUS1_INT_L
#define PF3__ADC3_9 PF3  //LightSource
//#define PF2 PF2             //Debug0
#define PF5__ADC3_15 PF5     //Debug1
#define PF4__ADC3_14 PF4     //Data_EBUS4_NSS
#define ADC3_5__PWM11_1 PF7  //Data_EBUS4_TX
#define ADC3_4__PWM10_1 PF6  //Data_EBUS4_Sync_L
#define ADC3_7__PWM14_1 PF9  //Data_EBUS4_INT_L
#define ADC3_6__PWM13_1 PF8  //Data_EBUS4_RX
#define ADC1_10 PC0          //Data_EBUS2_NSS
#define ADC3_8 PF10          //Data_EBUS2_TX
#define ADC1_12 PC2          //Data_EBUS2_Sync_L
#define ADC1_11 PC1          //Data_EBUS2_INT_L
#define ADC1_0__PWM2_1 PA0   //ServoA
#define ADC1_13 PC3          //Data_EBUS2_RX
#define ADC1_2__PWM2_3 PA2   //ServoC
#define ADC1_1__PWM2_2 PA1   //ServoB
#define ADC2_4 PA4           //InterruptC1
#define ADC1_3__PWM2_4 PA3   //ServoD
#define ADC2_6__PWM3_1 PA6   //RES
#define ADC2_5__PWM2_1 PA5   //InterruptC2
#define ADC2_14 PC4          //CI1
#define ADC2_7__PWM3_2 PA7   //CI2
#define ADC2_8__PWM3_3 PB0   //PwmOutputC
#define ADC2_15 PC5          //DI1
//#define PF11 PF11             //DI2
#define ADC2_9__PWM3_4 PB1  //PwmOutputD
//#define PF13 PF13             //InterruptD1
//#define PF12 PF12             //InterruptD2


//Right CON
#define SCL1 PB6  //Data_BUS_SCL
#define SDA1 PB7  //Data_BUS_SDA
#define MISO1 PB4
#define MOSI1 PB5
//#define PG15 PG15
#define SCK1 PB3
#define PG13__CTS6 PG13
#define PG14__TX6 PG14
//#define PG11 PG11
#define PG12__RTS6 PG12
#define PG9__RX6 PG9
//#define PG10 PG10
#define RX5 PD2
//#define PD7 PD7
#define NSS1 PA15
#define TX5 PC12
#define PC9__PWM8_4__SDA3 PC9
#define PA8__SCL3 PA8
#define PWM8_2 PC7  //Data_BUS_PWMB
#define PWM8_3 PC8  //Data_BUS_PWMA
//#define PG8 PG8     //Data_BUS_Sync_G
#define PWM8_1 PC6  //Data_BUS_INT_G
//#define PG6 PG6
#define PG7__CK6 PG7
//#define PG4 PG4
//#define PG5 PG5         //AI1
//#define PG2 PG2         //InterruptB2
//#define PG3 PG3         //InterruptB1
#define PWM4_3 PD14
#define PWM4_4 PD15
#define PWM4_1 PD12
#define PWM4_2 PD13
#define PWM1_2N PE10  //AI2
#define PWM1_2 PE11   //PwmOutputA
#define PWM1_1N PE8   //BI1
#define PWM1_1 PE9    //PwmOutputB
//#define PG1 PG1
//#define PE7 PE7         //BI2
//#define PF15 PF15       //InterruptA1
//#define PG0 PG0
//#define PF14 PF14       //InterruptA2

/***********************************************************************

//                            Communication relative

***********************************************************************/

TwoWire Wire3(PC9__PWM8_4__SDA3, PA8__SCL3);
HardwareSerial Serial5(RX5, TX5);
HardwareSerial Serial6(PG9__RX6, PG14__TX6);

/***********************************************************************

//                            OLD BUS relative

***********************************************************************/

//Main board
#define BUS_SDA PB11
#define BUS_SCL PB10
#define BUS_INT_G PE12
#define BUS_Sync_G PE15
#define BUS_PWMA PE13
#define BUS_PWMB PE14
TwoWire Wire2(BUS_SDA, BUS_SCL);


//Shield board(Data_BUS)
#define Data_BUS_SDA SDA1
#define Data_BUS_SCL SCL1
#define Data_BUS_INT_G PWM8_1
#define Data_BUS_Sync_G PG8
#define Data_BUS_PWMA PWM8_3
#define Data_BUS_PWMB PWM8_2
TwoWire Wire1(Data_BUS_SDA, Data_BUS_SCL);

#define OLD_Eye_IICAddressBase 0x10

/***********************************************************************

//                            OLD EBUS relative

***********************************************************************/

//Main board
#define EBUS_MOSI PB15
#define EBUS_MISO PB14
#define EBUS_SCK PB13
#define EBUS_NSS PB12
#define EBUS_TX PD8
#define EBUS_RX PD9
#define EBUS_INT_L PD10
#define EBUS_Sync_L PD11

HardwareSerial Serial3(EBUS_RX, EBUS_TX);
SPIClass SPI_3(EBUS_MOSI, EBUS_MISO, EBUS_SCK, EBUS_NSS);


//Shield board(Data_EBUS)
#define Data_EBUS_MOSI MOSI1
#define Data_EBUS_MISO MISO1
#define Data_EBUS_SCK SCK1
SPIClass SPI_1(MOSI1, MISO1, SCK1);



#define Data_EBUS1_NSS PC13
#define Data_EBUS1_TX PC14
#define Data_EBUS1_RX PF1
#define Data_EBUS1_INT_L PF0
#define Data_EBUS1_Sync_L PC15
// SoftwareSerial EBUS1Serial =  SoftwareSerial(Data_EBUS1_RX, Data_EBUS1_TX);
SoftwareSerial EBUS1Serial(Data_EBUS1_RX, Data_EBUS1_TX);

#define Data_EBUS2_NSS ADC1_10
#define Data_EBUS2_TX ADC3_8
#define Data_EBUS2_RX ADC1_13
#define Data_EBUS2_INT_L ADC1_11
#define Data_EBUS2_Sync_L ADC1_12
SoftwareSerial EBUS2Serial(Data_EBUS2_RX, Data_EBUS2_TX);

#define Data_EBUS3_NSS PE2
#define Data_EBUS3_TX PE3
#define Data_EBUS3_RX PE6__PWM9_2
#define Data_EBUS3_INT_L PE5__PWM9_1
#define Data_EBUS3_Sync_L PE4
SoftwareSerial EBUS3Serial(Data_EBUS3_RX, Data_EBUS3_TX);

#define Data_EBUS4_NSS PF4__ADC3_14
#define Data_EBUS4_TX ADC3_5__PWM11_1
#define Data_EBUS4_RX ADC3_6__PWM13_1
#define Data_EBUS4_INT_L ADC3_7__PWM14_1
#define Data_EBUS4_Sync_L ADC3_4__PWM10_1
SoftwareSerial EBUS4Serial(Data_EBUS4_RX, Data_EBUS4_TX);

/***********************************************************************

//                            DC Motor relative

***********************************************************************/
#define AI1 PG5            //Motor A I1
#define AI2 PWM1_2N        //Motor A I2
#define PwmOutputA PWM1_2  //Motor A PWM
#define InterruptA1 PF15   //Motor A Interrupt1
#define InterruptA2 PF14   //Motor A Interrupt2
#define BI1 PWM1_1N        //Motor B I1
#define BI2 PE7            //Motor B I2
#define PwmOutputB PWM1_1  //Motor B PWM
#define InterruptB1 PG3    //Motor B Interrupt1
//#define InterruptB2 PG2                 //Motor B Interrupt2
#define CI1 ADC2_14                //Motor C I1
#define CI2 ADC2_7__PWM3_2         //Motor C I2
#define PwmOutputC ADC2_8__PWM3_3  //Motor C PWM
#define InterruptC1 ADC2_4         //Motor C Interrupt1
//#define InterruptC2 ADC2_5__PWM2_1      //Motor C Interrupt2
#define DI1 ADC2_15                //Motor D I1
#define DI2 PF11                   //Motor D I2
#define PwmOutputD ADC2_9__PWM3_4  //Motor D PWM
#define InterruptD1 PF13           //Motor D Interrupt1
//#define InterruptD2 PF12                //Motor D Interrupt2

OLD_MotorDrive_V100Class MotorA;
OLD_MotorDrive_V100Class MotorB;
OLD_MotorDrive_V100Class MotorC;
OLD_MotorDrive_V100Class MotorD;

long MotorA_Counter = 0;
long MotorB_Counter = 0;
long MotorC_Counter = 0;
long MotorD_Counter = 0;

int MaxMotorPWM = 100;
int MinMotorPWM = 60;


long newtime = 0;
long oldtime = 0;
long subtime = 0;

long newstepA = 0;
long oldstepA = 0;
long newstepB = 0;
long oldstepB = 0;
long newstepC = 0;
long oldstepC = 0;
long newstepD = 0;
long oldstepD = 0;


/***********************************************************************

//                            Servo Motor relative

***********************************************************************/

Servo ServoA;
Servo ServoB;
Servo ServoC;
Servo ServoD;

#define ServoA_Pin ADC1_0__PWM2_1  //ServoA
#define ServoC_Pin ADC1_2__PWM2_3  //ServoC
#define ServoB_Pin ADC1_1__PWM2_2  //ServoB
#define ServoD_Pin ADC1_3__PWM2_4  //ServoD

/***********************************************************************

//                            Other interface relative

***********************************************************************/

#define TX1 PA9   //CH9340K
#define RX1 PA10  //CH9340K
#define TX2 PD5   //HighSpeed UART
#define RX2 PD6   //HighSpeed UART
#define RTS2 PD4  //HighSpeed UART
#define CTS2 PD3  //HighSpeed UART
#define TX4 PC10  //Debug UART
#define RX4 PC11  //Debug UART

HardwareSerial Serial1(RX1, TX1);
HardwareSerial Serial2(RX2, TX2);
//HardwareSerial Serial2(RX2, TX2, RTS2, CTS2);
//Debug BUS
//HardwareSerial Serial4(PC11, PC10);
//USBSerial SerialUSB;

#define Button0 PG0
#define Button1 PG1

#define SW1 PB8
#define SW2 PB9
#define SW3 PE0
#define SW4 PE1

#define RES ADC2_6__PWM3_1

#define WLED PWM4_4
#define WLED_ON (digitalWrite(WLED, LOW))
#define WLED_OFF (digitalWrite(WLED, HIGH))
#define RLED PWM4_3
#define RLED_ON (digitalWrite(RLED, LOW))
#define RLED_OFF (digitalWrite(RLED, HIGH))
#define GLED PWM4_2
#define GLED_ON (digitalWrite(GLED, LOW))
#define GLED_OFF (digitalWrite(GLED, HIGH))
#define BLED PWM4_1
#define BLED_ON (digitalWrite(BLED, LOW))
#define BLED_OFF (digitalWrite(BLED, HIGH))

#define Debug0LED PF2
#define Debug0LED_ON (digitalWrite(Debug0LED, LOW))
#define Debug0LED_OFF (digitalWrite(Debug0LED, HIGH))
#define Debug1LED PF5__ADC3_15
#define Debug1LED_ON (digitalWrite(Debug1LED, LOW))
#define Debug1LED_OFF (digitalWrite(Debug1LED, HIGH))

#define LightSource PF3__ADC3_9
Adafruit_NeoPixel strip(7, LightSource, NEO_GRB + NEO_KHZ800);
#define EyeBrightness 50

#define Disable 0
#define Enable 1
#define Interface_test Disable
#define SimpleAllLED_test Enable



/***********************************************************************

//                            Eye relative

***********************************************************************/

#define Eye_Numbers 16
byte LineState = 0;
#define AllWhiteFlag 1
#define AllBlackFlag 2
#define LeftHalfBlackFlag 3
#define RightHalfBlackFlag 4
#define LeftBigBendFlag 5
#define RightBigBendFlag 6
#define LeftSmallBendFlag 7
#define RightSmallBendFlag 8
#define StraightFlag 9
int Direction_Total_Eye_Value = 0;
// int Eye_Value[Eye_Numbers] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// int Eye_CorValue[Eye_Numbers] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte Eye_Value_H[Eye_Numbers] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte Eye_Value_S[Eye_Numbers] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte Eye_Value_V[Eye_Numbers] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
byte TempArray[127];

long temp, temp2, temp3, temp4, temp5 = 0;
void setup() {

  Interface_Setup();
  Communication_Setup();
  BUS_Setup();
  Data_BUS_Setup();
  EBUS_Setup();
  // Data_EBUS_Setup();

  LED_Setup();
  ButtonSWRES_Setup();

  MotorSetup();
  MotorA.CW_DirectMode(MaxMotorPWM);
  // MotorA.CCW_DirectMode(MaxMotorPWM);
  MotorB.CW_DirectMode(MaxMotorPWM);
  //MotorB.CCW_DirectMode(MaxMotorPWM);
  MotorC.CW_DirectMode(MaxMotorPWM);
  // MotorC.CCW_DirectMode(MaxMotorPWM);
  MotorD.CW_DirectMode(MaxMotorPWM);
  // MotorD.CCW_DirectMode(MaxMotorPWM);
  // delay(300);
  // while (1)
  //   ;
}

void loop() {

  // ButtonSWRES_Test();
  // Data_BUS_Test();
  // Data_EBUS_Test();
  // IIC3Scaner();

  // Serial1.print("MotorA_Counter = ");
  // Serial1.print(MotorA_Counter);
  // Serial1.print("  MotorB_Counter = ");
  // Serial1.print(MotorB_Counter);
  // Serial1.print("  MotorC_Counter = ");
  // Serial1.print(MotorC_Counter);
  // Serial1.print("  MotorD_Counter = ");
  // Serial1.println(MotorD_Counter);

  // if (Serial1.available()) {
  //     Serial1.println("TTT");
  //     Wire1.beginTransmission(OLD_Eye_IICAddressBase);
  //     Wire1.write(1);
  //     delay(1);
  //     Wire1.endTransmission();

  //     Wire1.beginTransmission(OLD_Eye_IICAddressBase);
  //     Wire1.requestFrom(OLD_Eye_IICAddressBase, 8);
  //     if (Wire1.available()) {
  //       Serial1.print("Data returned: ");
  //       while (Wire1.available()) Serial1.print((char) Wire1.read());
  //       Serial1.println();
  //     }
  //     Wire1.endTransmission();
  //     while(Serial1.available()) Serial1.read();  // Clear the serial buffer, in this example, just request data from slave
  //   }
  temp = millis();
  Wire1.beginTransmission(OLD_Eye_IICAddressBase);
  Wire1.write(0x50);  //0x50
  Wire1.endTransmission(1);
  delay(8);

  Wire1.beginTransmission(OLD_Eye_IICAddressBase);
  Wire1.write(0x51);
  Wire1.endTransmission(1);
  // delay(5);
  Wire1.requestFrom(OLD_Eye_IICAddressBase, 69);
  if (Wire1.available()) {

    for (int i = 0; i < 69; i++)
      TempArray[i] = Wire1.read();

    LineState = TempArray[1];
    Direction_Total_Eye_Value = (TempArray[2] * 256) + TempArray[3] - 10000;
    uint8_t j = 0;
    for (uint8_t i = 4; i < ((Eye_Numbers * 2) + 4); i += 2) {
      Eye_Value_H[j] = (TempArray[i] * 256) + TempArray[i + 1];
      j++;
    }
    j = 0;
    for (uint8_t i = 36; i < Eye_Numbers + 36; i++) {
      Eye_Value_S[j] = TempArray[i];
      j++;
    }
    j = 0;
    for (uint8_t i = 52; i < Eye_Numbers + 52; i++) {
      Eye_Value_V[j] = TempArray[i];
      j++;
    }
    // Serial1.print("Data length: ");
    // Serial1.print(Wire1.available());
    // Serial1.println();
  }
  temp2 = millis();

  Serial1.print("Time Spend: ");
  Serial1.print(temp2 - temp);
  Serial1.print("  Direction_Total_Eye_Value: ");
  Serial1.println(Direction_Total_Eye_Value);

  // Serial1.print("State: ");
  // Serial1.print(LineState);

  // switch (LineState) {
  //   case AllWhiteFlag:
  //     Serial1.print("AllWhiteFlag");
  //     break;

  //   case AllBlackFlag:
  //     Serial1.print("AllBlackFlag");
  //     break;

  //   case LeftHalfBlackFlag:
  //     Serial1.print("LeftHalfBlackFlag");
  //     break;

  //   case RightHalfBlackFlag:
  //     Serial1.print("RightHalfBlackFlag");
  //     break;

  //   case RightBigBendFlag:
  //     Serial1.print("RightBigBendFlag");
  //     break;

  //   case LeftBigBendFlag:
  //     Serial1.print("LeftBigBendFlag");
  //     break;

  //   case RightSmallBendFlag:
  //     Serial1.print("RightSmallBendFlag");
  //     break;

  //   case LeftSmallBendFlag:
  //     Serial1.print("LeftSmallBendFlag");
  //     break;

  //   case StraightFlag:
  //     Serial1.print("StraightFlag");
  //     break;
  // }

  // Serial1.print("  Eye_Value: ");
  // Serial1.print(Direction_Total_Eye_Value);

  // Serial1.print("  H: ");
  // for (byte i = 0; i < Eye_Numbers; i++) {
  //   Serial1.print(Eye_Value_H[i]);
  //   Serial1.print("  ");
  // }

  // Serial1.print("  S: ");
  // for (byte i = 0; i < Eye_Numbers; i++) {
  //   Serial1.print(Eye_Value_S[i]);
  //   Serial1.print("  ");
  // }

  // Serial1.print("  V: ");
  // for (byte i = 0; i < Eye_Numbers; i++) {
  //   Serial1.print(Eye_Value_V[i]);
  //   Serial1.print("  ");
  // }

  // Serial1.println();

  // while(1)
  // {
  //   // Serial1.println("TT");
  //   if (Serial6.available() >= 1) {
  //     Serial1.println((char)Serial6.read());
  //   }
  //   // delay(10);
  // }



  // digitalWrite(Data_EBUS1_INT_L, LOW);
  // if (digitalRead(Data_EBUS1_Sync_L) == 1) {
  //   delay(2);
  //   if (Serial6.available() >= 1) {
  //     if (Serial6.read() == 'O') {
  //       if (Serial6.read() == 'O') {

  //         LineState = Serial6.read();

  //         Direction_Total_Eye_Value = (Serial6.read() * 256) + Serial6.read();
  //         Direction_Total_Eye_Value -= 10000;

  //         for (byte i = 0; i < Eye_Numbers; i++)
  //           Eye_Value_H[i] = (Serial6.read() * 256) + Serial6.read();
  //         for (byte i = 0; i < Eye_Numbers; i++)
  //           Eye_Value_S[i] = Serial6.read();
  //         for (byte i = 0; i < Eye_Numbers; i++)
  //           Eye_Value_V[i] = Serial6.read();

  //         Serial1.print("State: ");
  //         Serial1.print(LineState);

  //         switch (LineState) {
  //           case AllWhiteFlag:
  //             Serial1.print("AllWhiteFlag");
  //             break;

  //           case AllBlackFlag:
  //             Serial1.print("AllBlackFlag");
  //             break;

  //           case LeftHalfBlackFlag:
  //             Serial1.print("LeftHalfBlackFlag");
  //             break;

  //           case RightHalfBlackFlag:
  //             Serial1.print("RightHalfBlackFlag");
  //             break;

  //           case RightBigBendFlag:
  //             Serial1.print("RightBigBendFlag");
  //             break;

  //           case LeftBigBendFlag:
  //             Serial1.print("LeftBigBendFlag");
  //             break;

  //           case RightSmallBendFlag:
  //             Serial1.print("RightSmallBendFlag");
  //             break;

  //           case LeftSmallBendFlag:
  //             Serial1.print("LeftSmallBendFlag");
  //             break;

  //           case StraightFlag:
  //             Serial1.print("StraightFlag");
  //             break;
  //         }

  //         Serial1.print("  Eye_Value: ");
  //         Serial1.print(Direction_Total_Eye_Value);

  //         // Serial1.print("  H: ");
  //         // for (byte i = 0; i < Eye_Numbers; i++) {
  //         //   Serial1.print(Eye_Value_H[i]);
  //         //   Serial1.print("  ");
  //         // }

  //         // Serial1.print("  S: ");
  //         // for (byte i = 0; i < Eye_Numbers; i++) {
  //         //   Serial1.print(Eye_Value_S[i]);
  //         //   Serial1.print("  ");
  //         // }

  //         // Serial1.print("  V: ");
  //         // for (byte i = 0; i < Eye_Numbers; i++) {
  //         //   Serial1.print(Eye_Value_V[i]);
  //         //   Serial1.print("  ");
  //         // }

  //         Serial1.println();
  //       }
  //     }
  //   }
  // } else {
  //   if (Serial6.available())
  //     Serial6.read();
  // }
}
