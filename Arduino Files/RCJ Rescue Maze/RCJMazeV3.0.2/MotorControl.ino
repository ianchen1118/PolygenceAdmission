void MotorSetup(void) {

#if (ESP32)
  MotorA.InitInBrake(AI1, AI2, PwmOutputA, 0);
  MotorB.InitInBrake(BI1, BI2, PwmOutputB, 1);
  MotorX.InitInBrake(XI1, XI2, PwmOutputX, 2);
  MotorY.InitInBrake(YI1, YI2, PwmOutputY, 3);

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
}

void MotorB1_Interrupt(void) {
  MotorB_Counter = MotorB.interrupt();
}

void MotorX1_Interrupt(void) {
  MotorX_Counter = MotorX.interrupt();
}

void MotorY1_Interrupt(void) {
  MotorY_Counter = MotorY.interrupt();
}