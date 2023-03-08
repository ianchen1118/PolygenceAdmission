#include "OLD_MotorDrive_V100.h"

#define TestTime 1000
/*             Motor related              */
#define PwmOutputA 8   //Motor A PWM
#define PwmOutputB 11  //Motor B PWM
#define PwmOutputX 7   //Motor X PWM
#define PwmOutputY 13  //Motor Y PWM
#define AI1 17         //Motor A BI1
#define AI2 16         //Motor A BI2
#define BI1 15         //Motor B BI1
#define BI2 14         //Motor B BI2
#define XI1 24         //Motor X BI1
#define XI2 22         //Motor X BI2
#define YI1 23         //Motor Y BI1
#define YI2 25         //Motor Y BI2


OLD_MotorDrive_V100Class MotorA;
OLD_MotorDrive_V100Class MotorB;
OLD_MotorDrive_V100Class MotorX;
OLD_MotorDrive_V100Class MotorY;

long interrupt2Counter = 0;
long interrupt3Counter = 0;
long interrupt4Counter = 0;
long interrupt5Counter = 0;

int MaxMotorPWM = 100;
int MinMotorPWM = 60;


long newtime = 0;
long oldtime = 0;
long subtime = 0;

long newstep2 = 0;
long oldstep2 = 0;
long newstep3 = 0;
long oldstep3 = 0;
long newstep4 = 0;
long oldstep4 = 0;
long newstep5 = 0;
long oldstep5 = 0;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  //ContinousRecordTest();
  ContinousTest();
  //SignalTest();
}

void MotorSetup(void) {

#if (ESP32)
  MotorA.InitInBrake(40, 41, 42, 0);
  MotorB.InitInBrake(37, 38, 39, 0);
  MotorX.InitInBrake(45, 0, 35, 0);
  MotorY.InitInBrake(21, 47, 48, 0);

  attachInterrupt(4, interrupt2, HIGH);  //GPIO4  MotorA
  attachInterrupt(5, interrupt3, HIGH);  //GPIO5  MotorB
  attachInterrupt(6, interrupt4, HIGH);  //GPIO6  MotorX
  attachInterrupt(7, interrupt5, HIGH);  //GPIO7  MotorY

#else
  MotorA.InitInBrake(AI1, AI2, PwmOutputA);
  MotorB.InitInBrake(BI1, BI2, PwmOutputB);
  MotorX.InitInBrake(XI1, XI2, PwmOutputX);
  MotorY.InitInBrake(YI1, YI2, PwmOutputY);

  attachInterrupt(2, interrupt2, HIGH);  //D21  MotorA
  attachInterrupt(3, interrupt3, HIGH);  //D20  MotorB
  attachInterrupt(4, interrupt4, HIGH);  //D19  MotorX
  attachInterrupt(5, interrupt5, HIGH);  //D18  MotorY

#endif
}

void interrupt2(void) {
  interrupt2Counter = MotorA.interrupt();
  //Serial.println(MotorA.GobalStep);
  //Serial.print("interrupt2Counter = ");
  //Serial.print(interrupt2Counter);
  //Serial.print(" || ");
}

void interrupt3(void) {
  interrupt3Counter = MotorB.interrupt();
  // Serial.println(MotorB.GobalStep);
  // Serial.print("interrupt3Counter = ");
  // Serial.print(interrupt3Counter);
  // Serial.print(" || ");
}

void interrupt4(void) {
  interrupt4Counter = MotorX.interrupt();
  // Serial.println(MotorX.GobalStep);
  // Serial.print("interrupt4Counter = ");
  // Serial.println(interrupt4Counter);
  // Serial.print(" || ");
}

void interrupt5(void) {
  interrupt5Counter = MotorY.interrupt();
  // Serial.println(MotorY.GobalStep);
  // Serial.print("interrupt5Counter = ");
  // Serial.print(interrupt5Counter);
  // Serial.print(" || ");
}

void SignalTest(void) {

  oldtime = millis();
  oldstep2 = interrupt2Counter;
  oldstep3 = interrupt3Counter;
  oldstep4 = interrupt4Counter;
  oldstep5 = interrupt5Counter;
  while (1) {

    newtime = millis();
    subtime = newtime - oldtime;

    if (subtime >= TestTime) {
      newstep2 = interrupt2Counter;
      newstep3 = interrupt3Counter;
      newstep4 = interrupt4Counter;
      newstep5 = interrupt5Counter;
      PrintMotorData();
      MotorA.Brake_Slide();
      MotorB.Brake_Slide();
      MotorX.Brake_Slide();
      MotorY.Brake_Slide();
      while (1)
        ;
    }
  }
}

void ContinousTest(void) {

  oldstep2 = interrupt2Counter;
  oldstep3 = interrupt3Counter;
  oldstep4 = interrupt4Counter;
  oldstep5 = interrupt5Counter;
  while (1) {
    for (int i = 0; i < 196; i++) {
      MaxMotorPWM = MinMotorPWM + (i);
      MotorA.CW_DirectMode(MaxMotorPWM);
      MotorB.CW_DirectMode(MaxMotorPWM);
      MotorX.CW_DirectMode(MaxMotorPWM);
      MotorY.CW_DirectMode(MaxMotorPWM);
      subtime = 0;
      delay(100);
      oldstep2 = interrupt2Counter;
      oldstep3 = interrupt3Counter;
      oldstep4 = interrupt4Counter;
      oldstep5 = interrupt5Counter;
      oldtime = millis();
      while (subtime < TestTime) {

        newtime = millis();
        subtime = newtime - oldtime;
        if (subtime >= TestTime) {
          newstep2 = interrupt2Counter;
          newstep3 = interrupt3Counter;
          newstep4 = interrupt4Counter;
          newstep5 = interrupt5Counter;
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

void ContinousRecordTest(void) {

  oldstep2 = interrupt2Counter;
  oldstep3 = interrupt3Counter;
  oldstep4 = interrupt4Counter;
  oldstep5 = interrupt5Counter;
  while (1) {
    for (int i = 0; i < 20; i++) {
      MaxMotorPWM = MinMotorPWM + (i * 10);
      MotorA.CW_DirectMode(MaxMotorPWM);
      MotorB.CW_DirectMode(MaxMotorPWM);
      MotorX.CW_DirectMode(MaxMotorPWM);
      MotorY.CW_DirectMode(MaxMotorPWM);
      subtime = 0;
      delay(100);
      oldstep2 = interrupt2Counter;
      oldstep3 = interrupt3Counter;
      oldstep4 = interrupt4Counter;
      oldstep5 = interrupt5Counter;
      oldtime = millis();
      while (subtime < TestTime) {

        newtime = millis();
        subtime = newtime - oldtime;
        if (subtime >= TestTime) {
          newstep2 = interrupt2Counter;
          newstep3 = interrupt3Counter;
          newstep4 = interrupt4Counter;
          newstep5 = interrupt5Counter;
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
  detachInterrupt(4);  //GPIO4  MotorA
  detachInterrupt(5);  //GPIO5  MotorB
  detachInterrupt(6);  //GPIO6  MotorX
  detachInterrupt(7);  //GPIO7  MotorY
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
  Serial.print(newstep2 - oldstep2);
  Serial.print("\t");
  Serial.print(" || MotorB step: ");
  Serial.print("\t");
  Serial.print(newstep3 - oldstep3);
  Serial.print("\t");
  Serial.print(" || MotorX step: ");
  Serial.print("\t");
  Serial.print(newstep4 - oldstep4);
  Serial.print("\t");
  Serial.print(" || MotorY step: ");
  Serial.print("\t");
  Serial.println(newstep5 - oldstep5);

#if (ESP32)
  attachInterrupt(4, interrupt2, HIGH);  //GPIO4  MotorA
  attachInterrupt(5, interrupt3, HIGH);  //GPIO5  MotorB
  attachInterrupt(6, interrupt4, HIGH);  //GPIO6  MotorX
  attachInterrupt(7, interrupt5, HIGH);  //GPIO7  MotorY
#else
  attachInterrupt(2, interrupt2, HIGH);  //D21  MotorA
  attachInterrupt(3, interrupt3, HIGH);  //D20  MotorB
  attachInterrupt(4, interrupt4, HIGH);  //D19  MotorX
  attachInterrupt(5, interrupt5, HIGH);  //D18  MotorY
#endif
}