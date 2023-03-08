void LEDSetup(void)
{
  for (byte i = 0; i <= NumberOfPin_LED - 1; i ++)
  {
    pinMode(TestLED_Array[i], OUTPUT);
    //digitalWrite(TestLED_Array[i], HIGH);
    analogWrite(TestLED_Array[i], LEDBrightness);
    delay(100);
  }

  for (byte i = 0; i <= NumberOfPin_LED - 1; i ++)
  {
    digitalWrite(TestLED_Array[i], LOW);
  }
  POWER_ON;
}
