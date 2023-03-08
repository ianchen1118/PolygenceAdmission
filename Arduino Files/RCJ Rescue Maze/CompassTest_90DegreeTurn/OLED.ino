void OLEDSetup (void)
{
  int a = 0;
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);

  display.display();
  delay(100);

  display.clearDisplay();

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(1);

  display.setCursor(0, 0);
  display.print("Welcome");

  display.setCursor(10, 20);
  display.print("OwlLab");

  display.setCursor(15, 40);
  display.print("UI System");

  display.display();
}

void IR_OLEDDisplay (void)
{
  IRCalculate();
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("IR");

  display.setCursor(25, 0);
  display.print(Eye_Value[0]);
  display.setCursor(25, 9);
  display.print(Eye_Value[1]);
  display.setCursor(25, 18);
  display.print(Eye_Value[2]);
  display.setCursor(25, 27);
  display.print(Eye_Value[3]);
  display.setCursor(25, 36);
  display.print(Eye_Value[4]);
  display.setCursor(25, 45);
  display.print(Eye_Value[5]);
  display.setCursor(25, 54);
  display.print(Eye_Value[6]);


  display.setCursor(60, 0);
  display.print(Eye_Value[7]);
  display.setCursor(60, 9);
  display.print(Eye_Value[8]);
  display.setCursor(60, 18);
  display.print(Eye_Value[9]);
  display.setCursor(60, 27);
  display.print(Eye_Value[10]);
  display.setCursor(60, 36);
  display.print(Eye_Value[11]);
  display.setCursor(60, 45);
  display.print(Eye_Value[12]);

  display.setCursor(90, 8);
  display.print("T:");

  display.setCursor(100, 20);
  display.print(Direction_Total_Eye_Value);

  display.display();
}

void Color_OLEDDisplay (void)
{
  ColorCalculate();
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Color");

  display.setCursor(0, 10);
  display.print("RightColorMixValue");
  display.setCursor(10, 20);
  display.print(RightColorMixValue);
  display.setCursor(0, 40);
  display.print("LeftColorMixValue");
  display.setCursor(10, 50);
  display.print(LeftColorMixValue);

  display.display();
}

