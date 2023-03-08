void MotorSetup(void)
{
  Motor.TB6612_InitInBrake();

  attachInterrupt(4, interrupt4, HIGH);//D19
  attachInterrupt(5, interrupt5, HIGH);//D18
}

void interrupt4(void)
{
  interrupt4Counter = Motor.interrupt4();
  //Serial.print("interrupt4Counter = ");Serial.print(interrupt4Counter);Serial.print(" || ");
}

void interrupt5(void)
{
  interrupt5Counter = Motor.interrupt5();
  //Serial.print("interrupt5Counter = ");Serial.print(interrupt5Counter);Serial.print(" || ");
}
