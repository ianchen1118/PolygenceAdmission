void ColorSetup(void)
{
  for (int i = 0; i < 6; i++)
  {
    ColorArray[i] = (EEPROM.read(ColorBaseAddress + (2 * i))) * 256 + (EEPROM.read(ColorBaseAddress + (2 * i) + 1));
  }

  Color.TCS3200_Init(RightSide, ColorArray[0], ColorArray[1], ColorArray[2]);
  Color.TCS3200_Init(LeftSide, ColorArray[3], ColorArray[4], ColorArray[5]);
  if (digitalRead(SW2_pin) == LOW)
  {
    WLED_ON;
    Color.WhiteBalance(RightSide);
    Color.WhiteBalance(LeftSide);
    for (int i = 0; i < 6; i++)
    {
      EEPROM.write((ColorBaseAddress + (2 * i)), Color.ColorIndexArray[i] / 256);
      EEPROM.write((ColorBaseAddress + (2 * 1) + 1), Color.ColorIndexArray[i] % 256);
    }
    WLED_OFF;
    GLED_ON;
    while (1);
  }
}

void ColorCalculate(void)
{
  RightRedColorValue = Color.GetColorValue(RightSide, colorRedType);
  RightGreenColorValue = Color.GetColorValue(RightSide, colorGreenType);
  RightBlueColorValue = Color.GetColorValue(RightSide, colorBlueType);
  LeftRedColorValue = Color.GetColorValue(LeftSide, colorRedType);
  LeftGreenColorValue = Color.GetColorValue(LeftSide, colorGreenType);
  LeftBlueColorValue = Color.GetColorValue(LeftSide, colorBlueType);

  RightRedColorValue = Color.ColorValueCorrection(RightSide, colorRedType, RightRedColorValue);
  RightGreenColorValue = Color.ColorValueCorrection(RightSide, colorGreenType, RightGreenColorValue);
  RightBlueColorValue = Color.ColorValueCorrection(RightSide, colorBlueType, RightBlueColorValue);
  LeftRedColorValue = Color.ColorValueCorrection(LeftSide, colorRedType, LeftRedColorValue);
  LeftGreenColorValue = Color.ColorValueCorrection(LeftSide, colorGreenType, LeftGreenColorValue);
  LeftBlueColorValue = Color.ColorValueCorrection(LeftSide, colorBlueType, LeftBlueColorValue);

  RightColorMixValue = Color.HSL_Algorithm(RightRedColorValue, RightGreenColorValue, RightBlueColorValue);
  LeftColorMixValue = Color.HSL_Algorithm(LeftRedColorValue, LeftGreenColorValue, LeftBlueColorValue);

  //  Serial.print(RightColorMixValue);
  //  Serial.print("  ||  ");
  //  Serial.print(LeftColorMixValue);
  //  Serial.println();
}
