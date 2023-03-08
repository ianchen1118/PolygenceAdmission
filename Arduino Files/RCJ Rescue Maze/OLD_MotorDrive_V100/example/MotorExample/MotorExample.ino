#include "OLD_MotorDrive_V100.h"

#define TestTime 1000

/*             Motor related              */
#if (ESP32)
#define AI1 40                //Motor A I1
#define AI2 41                //Motor A I2
#define PwmOutputA 42                //Motor A PWM
#define InterruptA1 4                //Motor A Interrupt1
//#define InterruptA2                //Motor A Interrupt2
#define BI1 37                //Motor B I1
#define BI2 38                //Motor B I2
#define PwmOutputB 39                //Motor B PWM
#define InterruptB1 5                //Motor B Interrupt1
//#define InterruptB2                //Motor B Interrupt2
#define XI1 45                //Motor X I1
#define XI2 0                 //Motor X I2
#define PwmOutputX 35                //Motor X PWM
#define InterruptX1 6                //Motor X Interrupt1
//#define InterruptX2                //Motor X Interrupt2 
#define YI1 21                //Motor Y I1
#define YI2 47                //Motor Y I2
#define PwmOutputY 48                //Motor Y PWM
#define InterruptY1 7                //Motor Y Interrupt1
//#define InterruptY2                //Motor Y Interrupt2

#else
#define AI1 17         //Motor A I1
#define AI2 16         //Motor A I2
#define BI1 15         //Motor B I1
#define BI2 14         //Motor B I2
#define XI1 24         //Motor X I1
#define XI2 22         //Motor X I2
#define YI1 23         //Motor Y I1
#define YI2 25         //Motor Y I2
#define PwmOutputA 8   //Motor A PWM
#define PwmOutputB 11  //Motor B PWM
#define PwmOutputX 7   //Motor X PWM
#define PwmOutputY 13  //Motor Y PWM

#endif

OLD_MotorDrive_V100Class MotorA;
OLD_MotorDrive_V100Class MotorB;
OLD_MotorDrive_V100Class MotorX;
OLD_MotorDrive_V100Class MotorY;

long MotorA_Counter = 0;
long MotorB_Counter = 0;
long MotorX_Counter = 0;
long MotorY_Counter = 0;

int MaxMotorPWM = 100;
int MinMotorPWM = 60;


long newtime = 0;
long oldtime = 0;
long subtime = 0;

long newstepA = 0;
long oldstepA = 0;
long newstepB = 0;
long oldstepB = 0;
long newstepX = 0;
long oldstepX = 0;
long newstepY = 0;
long oldstepY = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  MotorSetup();

  MotorA.CW_DirectMode(MaxMotorPWM);
  //MotorA.CCW_DirectMode(MaxMotorPWM);
  MotorB.CW_DirectMode(MaxMotorPWM);
  // MotorB.CCW_DirectMode(MaxMotorPWM);
  MotorX.CW_DirectMode(MaxMotorPWM);
  // MotorX.CCW_DirectMode(MaxMotorPWM);
  MotorY.CW_DirectMode(MaxMotorPWM);
  // MotorY.CCW_DirectMode(MaxMotorPWM);
  delay(300);
  while (1)
    ;
}

void loop() {
  // put your main code here, to run repeatedly:
  //ContinousRecordTest();
  ContinousTest();
  //SignalTest();
}

void MotorSetup(void) {

#if (ESP32)
  MotorA.InitInBrake(AI1, AI2, PwmOutputA, 0);
  MotorB.InitInBrake(BI1, BI2, PwmOutputB, 0);
  MotorX.InitInBrake(XI1, XI2, PwmOutputX, 0);
  MotorY.InitInBrake(YI1, YI2, PwmOutputY, 0);

  attachInterrupt(InterruptA1, MotorA1_Interrupt, HIGH);  //GPIO4  MotorA
  attachInterrupt(InterruptB1, MotorB1_Interrupt, HIGH);  //GPIO5  MotorB
  attachInterrupt(InterruptX1, MotorX1_Interrupt, HIGH);  //GPIO6  MotorX
  attachInterrupt(InterruptY1, MotorY1_Interrupt, HIGH);  //GPIO7  MotorY

#else
  MotorA.InitInBrake(AI1, AI2, PwmOutputA);
  MotorB.InitInBrake(BI1, BI2, PwmOutputB);
  MotorX.InitInBrake(XI1, XI2, PwmOutputX);
  MotorY.InitInBrake(YI1, YI2, PwmOutputY);

  attachInterrupt(2, MotorA1_Interrupt, HIGH);  //D21  MotorA
  attachInterrupt(3, MotorB1_Interrupt, HIGH);  //D20  MotorB
  attachInterrupt(4, MotorX1_Interrupt, HIGH);  //D19  MotorX
  attachInterrupt(5, MotorY1_Interrupt, HIGH);  //D18  MotorY

#endif
}
  
void MotorA1_Interrupt(void) {
  MotorA_Counter = MotorA.interrupt();
  //Serial.println(MotorA.GobalStep);
  //Serial.print("MotorA_Counter = ");
  //Serial.print(MotorA_Counter);
  //Serial.print(" || ");
}

void MotorB1_Interrupt(void) {
  MotorB_Counter = MotorB.interrupt();
  // Serial.println(MotorB.GobalStep);
  // Serial.print("MotorB_Counter = ");
  // Serial.print(MotorB_Counter);
  // Serial.print(" || ");
}

void MotorX1_Interrupt(void) {
  MotorX_Counter = MotorX.interrupt();
  // Serial.println(MotorX.GobalStep);
  // Serial.print("MotorX_Counter = ");
  // Serial.println(MotorX_Counter);
  // Serial.print(" || ");
}

void MotorY1_Interrupt(void) {
  MotorY_Counter = MotorY.interrupt();
  // Serial.println(MotorY.GobalStep);
  // Serial.print("MotorY_Counter = ");
  // Serial.print(MotorY_Counter);
  // Serial.print(" || ");
}

void ContinousTest(void) {

  oldstepA = MotorA_Counter;
  oldstepB = MotorB_Counter;
  oldstepX = MotorX_Counter;
  oldstepY = MotorY_Counter;
  while (1) {
    for (int i = 0; i < 196; i++) {
      MaxMotorPWM = MinMotorPWM + (i);
      MotorA.CW_DirectMode(MaxMotorPWM);
      MotorB.CW_DirectMode(MaxMotorPWM);
      MotorX.CW_DirectMode(MaxMotorPWM);
      MotorY.CW_DirectMode(MaxMotorPWM);
      subtime = 0;
      delay(100);
      oldstepA = MotorA_Counter;
      oldstepB = MotorB_Counter;
      oldstepX = MotorX_Counter;
      oldstepY = MotorY_Counter;
      oldtime = millis();
      while (subtime < TestTime) {

        newtime = millis();
        subtime = newtime - oldtime;
        if (subtime >= TestTime) {
          newstepA = MotorA_Counter;
          newstepB = MotorB_Counter;
          newstepX = MotorX_Counter;
          newstepY = MotorY_Counter;
          PrintMotorData();
        }
      }
    }
    MotorA.Brake_Slide();
    MotorB.Brake_Slide();
    MotorX.Brake_Slide();
    MotorY.Brake_Slide();
    while (1)
      ;
  }
}


void PrintMotorData(void) {

#if (ESP32)
  detachInterrupt(InterruptA1);  //GPIO4  MotorA
  detachInterrupt(InterruptB1);  //GPIO5  MotorB
  detachInterrupt(InterruptX1);  //GPIO6  MotorX
  detachInterrupt(InterruptY1);  //GPIO7  MotorY
#else
  detachInterrupt(2);                    //D21  MotorA
  detachInterrupt(3);                    //D20  MotorB
  detachInterrupt(4);                    //D19  MotorX
  detachInterrupt(5);                    //D18  MotorY
#endif
  Serial.print("Motor Speed: ");
  Serial.print("\t");
  Serial.print(MaxMotorPWM);
  Serial.print("\t");
  Serial.print(" || Spend time: ");
  Serial.print("\t");
  Serial.print(subtime);
  Serial.print("\t");
  Serial.print(" || MotorA step: ");
  Serial.print("\t");
  Serial.print(newstepA - oldstepA);
  Serial.print("\t");
  Serial.print(" || MotorB step: ");
  Serial.print("\t");
  Serial.print(newstepB - oldstepB);
  Serial.print("\t");
  Serial.print(" || MotorX step: ");
  Serial.print("\t");
  Serial.print(newstepX - oldstepX);
  Serial.print("\t");
  Serial.print(" || MotorY step: ");
  Serial.print("\t");
  Serial.println(newstepY - oldstepY);

#if (ESP32)
  attachInterrupt(InterruptA1, MotorA1_Interrupt, HIGH);  //GPIO4  MotorA
  attachInterrupt(InterruptB1, MotorB1_Interrupt, HIGH);  //GPIO5  MotorB
  attachInterrupt(InterruptX1, MotorX1_Interrupt, HIGH);  //GPIO6  MotorX
  attachInterrupt(InterruptY1, MotorY1_Interrupt, HIGH);  //GPIO7  MotorY
#else
  attachInterrupt(2, MotorA1_Interrupt, HIGH);  //D21  MotorA
  attachInterrupt(3, MotorB1_Interrupt, HIGH);  //D20  MotorB
  attachInterrupt(4, MotorX1_Interrupt, HIGH);  //D19  MotorX
  attachInterrupt(5, MotorY1_Interrupt, HIGH);  //D18  MotorY
#endif
}
