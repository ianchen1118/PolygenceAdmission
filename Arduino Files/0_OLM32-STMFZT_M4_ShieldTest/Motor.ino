/*
Motor.CW_DirectMode(MaxMotorPWM);
Motor.CCW_DirectMode(MaxMotorPWM);
Motor.CW_WaitMode(MaxMotorPWM, 100);
Motor.CCW_WaitMode(MaxMotorPWM, 100);
Motor.Brake_Slide();
Motor.Brake_Lock();
*/

void MotorSetup(void) {

  MotorA.InitInBrake(AI1, AI2, PwmOutputA);
  MotorB.InitInBrake(BI1, BI2, PwmOutputB);
  MotorC.InitInBrake(CI1, CI2, PwmOutputC);
  MotorD.InitInBrake(DI1, DI2, PwmOutputD);

  attachInterrupt(InterruptA1, MotorA1_Interrupt, HIGH);  //MotorA
  attachInterrupt(InterruptB1, MotorB1_Interrupt, HIGH);  //MotorB
  attachInterrupt(InterruptC1, MotorC1_Interrupt, HIGH);  //MotorC
  attachInterrupt(InterruptD1, MotorD1_Interrupt, HIGH);  //MotorD

  ServoA.attach(ServoA_Pin);
  ServoB.attach(ServoB_Pin);
  ServoC.attach(ServoC_Pin);
  ServoD.attach(ServoD_Pin);

  ServoA.write(0);
  ServoB.write(0);
  ServoC.write(0);
  ServoD.write(0);
}

void MotorA1_Interrupt(void) {
  MotorA_Counter = MotorA.interrupt();
  // Serial1.println(MotorA.GobalStep);
  // Serial1.print("MotorA_Counter = ");
  // Serial1.print(MotorA_Counter);
  // Serial1.print(" || ");
}

void MotorB1_Interrupt(void) {
  MotorB_Counter = MotorB.interrupt();
  // Serial1.println(MotorB.GobalStep);
  // Serial1.print("MotorB_Counter = ");
  // Serial1.print(MotorB_Counter);
  // Serial1.print(" || ");
}

void MotorC1_Interrupt(void) {
  MotorC_Counter = MotorC.interrupt();
  // Serial1.println(MotorC.GobalStep);
  // Serial1.print("MotorC_Counter = ");
  // Serial1.println(MotorC_Counter);
  // Serial1.print(" || ");
}

void MotorD1_Interrupt(void) {
  MotorD_Counter = MotorD.interrupt();
  // Serial1.println(MotorD.GobalStep);
  // Serial1.print("MotorD_Counter = ");
  // Serial1.print(MotorD_Counter);
  // Serial1.print(" || ");
}

void ContinousTest(void) {

  oldstepA = MotorA_Counter;
  oldstepB = MotorB_Counter;
  oldstepC = MotorC_Counter;
  oldstepD = MotorD_Counter;
  while (1) {
    for (int i = 0; i < 196; i++) {
      MaxMotorPWM = MinMotorPWM + (i);
      MotorA.CW_DirectMode(MaxMotorPWM);
      MotorB.CW_DirectMode(MaxMotorPWM);
      MotorC.CW_DirectMode(MaxMotorPWM);
      MotorD.CW_DirectMode(MaxMotorPWM);
      subtime = 0;
      delay(100);
      oldstepA = MotorA_Counter;
      oldstepB = MotorB_Counter;
      oldstepC = MotorC_Counter;
      oldstepD = MotorD_Counter;
      oldtime = millis();
      while (subtime < 1000) {

        newtime = millis();
        subtime = newtime - oldtime;
        if (subtime >= 1000) {
          newstepA = MotorA_Counter;
          newstepB = MotorB_Counter;
          newstepC = MotorC_Counter;
          newstepD = MotorD_Counter;
          PrintMotorData();
        }
      }
    }
    MotorA.Brake_Slide();
    MotorB.Brake_Slide();
    MotorC.Brake_Slide();
    MotorD.Brake_Slide();
    while (1)
      ;
  }
}


void PrintMotorData(void) {

  detachInterrupt(InterruptA1);  //MotorA
  detachInterrupt(InterruptB1);  //MotorB
  detachInterrupt(InterruptC1);  //MotorC
  detachInterrupt(InterruptD1);  //MotorD

  Serial1.print("Motor Speed: ");
  Serial1.print("\t");
  Serial1.print(MaxMotorPWM);
  Serial1.print("\t");
  Serial1.print(" || Spend time: ");
  Serial1.print("\t");
  Serial1.print(subtime);
  Serial1.print("\t");
  Serial1.print(" || MotorA step: ");
  Serial1.print("\t");
  Serial1.print(newstepA - oldstepA);
  Serial1.print("\t");
  Serial1.print(" || MotorB step: ");
  Serial1.print("\t");
  Serial1.print(newstepB - oldstepB);
  Serial1.print("\t");
  Serial1.print(" || MotorC step: ");
  Serial1.print("\t");
  Serial1.print(newstepC - oldstepC);
  Serial1.print("\t");
  Serial1.print(" || MotorD step: ");
  Serial1.print("\t");
  Serial1.println(newstepD - oldstepD);

  attachInterrupt(InterruptA1, MotorA1_Interrupt, HIGH);  //GPIO4  MotorA
  attachInterrupt(InterruptB1, MotorB1_Interrupt, HIGH);  //GPIO5  MotorB
  attachInterrupt(InterruptC1, MotorC1_Interrupt, HIGH);  //GPIO6  MotorC
  attachInterrupt(InterruptD1, MotorD1_Interrupt, HIGH);  //GPIO7  MotorD
}

void ServoMotorTest(void) {
  for (byte i = 0; i < 180; i++) {
    ServoA.write(i);
    // ServoB.write(i);
    // ServoC.write(i);
    // ServoD.write(i);
    delay(10);
  }
  delay(200);
  for (byte i = 180; i > 0; i--) {
    ServoA.write(i);
    // ServoB.write(i);
    // ServoC.write(i);
    // ServoD.write(i);
    delay(10);
  }
  delay(200);
}

