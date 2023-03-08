#include "popo_Mega2560_MotorDrive_V2.h"
#include "popo_TCS3200_HSL.h"
#include <EEPROM.h>

#include <Wire.h>
#include <DFRobot_QMC5883.h>

#define Disable 0
#define Enable 1

#define BaudRate 115200
/*             General related              */

#define SW2_pin 36
#define SW3_pin 34

DFRobot_QMC5883 compass;
void CompassSetup(); 
float CompassDegree(); 

/******************************************/

/*             TestLed related              */

#define NumberOfPin_LED 6
#define LEDBrightness 10
int TestLED_Array[NumberOfPin_LED] = {2, 3, 4, 5, 6, 53};

#define WLED_ON analogWrite(TestLED_Array[0],LEDBrightness)
#define WLED_OFF analogWrite(TestLED_Array[0],LOW)

#define YLED_ON analogWrite(TestLED_Array[1],LEDBrightness)
#define YLED_OFF analogWrite(TestLED_Array[1],LOW)

#define RLED_ON analogWrite(TestLED_Array[2],LEDBrightness)
#define RLED_OFF analogWrite(TestLED_Array[2],LOW)

#define GLED_ON analogWrite(TestLED_Array[3],LEDBrightness)
#define GLED_OFF analogWrite(TestLED_Array[3],LOW)

#define BLED_ON analogWrite(TestLED_Array[4],LEDBrightness)
#define BLED_OFF analogWrite(TestLED_Array[4],LOW)

#define POWER_ON analogWrite(TestLED_Array[5],LEDBrightness)
#define POWER_OFF analogWrite(TestLED_Array[5],LOW)

/******************************************/

/*             TestIR related              */
#define Eye_Numbers 13
#define EyeCor_Maxvalue 100
volatile byte IR_State = 0;
volatile int Direction_Total_Eye_Value = 0;

#define Const_MidTotalValue_Area 80
#define Const_BoundaryTotalValue 1000
//#define Const_CornerTotalValue 1200

int Abs_Direction_Total_Eye_Value = 0;
int Div_Abs_Direction_Total_Eye_Value = 0;

int IR_eye[Eye_Numbers] = {A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15};                         //20180630
volatile int Eye_Value[Eye_Numbers] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile int Eye_CorValue[Eye_Numbers] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//int Eye_Weighted[Eye_Numbers] = { 11, 7, 5, 3, 2, 2, 0 , -2, -2, -3, -5, -7, -11};
int Eye_Weighted[Eye_Numbers] = { 12, 12, 9, 5, 3, 1, 0 , -1, -3, -5, -9, -12, -12};
volatile int Direction_Eye_Value[Eye_Numbers] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int Eye_ValueMin[Eye_Numbers] = {160, 37, 34, 34, 451, 262, 43, 35, 34, 33, 35, 36, 52};
int Eye_ValueMAX[Eye_Numbers] = {811, 733, 715, 686, 890, 862, 787, 702, 611, 659, 673, 741, 824};

/******************************************/

/*             TestColor related              */
#define ColorBaseAddress 0x10
#define RightSide 0
#define LeftSide 1

popo_TCS3200_HSLClass Color;
long ColorArray[6] = {0, 0, 0, 0, 0, 0};
long RightRedColorValue = 0;
long RightGreenColorValue = 0;
long RightBlueColorValue = 0;
long LeftRedColorValue = 0;
long LeftGreenColorValue = 0;
long LeftBlueColorValue = 0;

int RightColorMixValue = 0;
int LeftColorMixValue = 0;
/******************************************/

/*             Motor related              */
popo_Mega2560_MotorDrive_V2Class Motor;

long interrupt4Counter = 0;
long interrupt5Counter = 0;
#define MaxMotorPWM 120
#define MinMotorPWM 20
/******************************************/


/*             UltraSonic related              */
int trigPin = 42;                  //Trig Pin
int echoPin = 44;                  //Echo Pin
long cm;

/******************************************/


/*             OLED related              */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);

/******************************************/


/*             ServoMotor related              */

#include <Servo.h>

#define Arm_InitAngle 160
#define Arm_GetBallAngle 0

#define Grab_InitAngle 50
#define Grab_GetBallAngle 0

Servo ArmServo;
Servo GrabServo;
/******************************************/

#define CrossUpdateFlag 2

void setup()
{
  Serial.begin(115200);
  GeneralSetup();
  LEDSetup();
  //IRSetup();
  //ColorSetup();
  MotorSetup();
  //OLEDSetup();
  //UltraSonicSetup();
  //ServoMotorSetup();
  CompassSetup();
}


void loop()
{
  Turn90R();
  Serial.println(CompassDegree()); 
  delay(5000);
}
