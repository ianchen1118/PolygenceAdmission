
void ADCsetP16(void)
{
  ADCSRA |=  (1 << ADPS2);   // 1
  ADCSRA &=  ~(1 << ADPS1);  // 0
  ADCSRA &=  ~(1 << ADPS0);  // 0
}

void IRSetup(void)
{
  for (byte i = 0; i < Eye_Numbers; i ++)
  {
    pinMode(IR_eye[i], INPUT);
  }
  ADCsetP16();
}

volatile byte IRCalculate(void)
{
  Direction_Total_Eye_Value = 0;
  for (byte i = 0; i < Eye_Numbers; i ++)
  {
    Eye_Value[i] = analogRead(IR_eye[i]);
    Eye_CorValue[i] = map(Eye_Value[i], Eye_ValueMin[i], Eye_ValueMAX[i], 0, EyeCor_Maxvalue);
    if (Eye_CorValue[i] <= 0)
      Eye_CorValue[i] = 0;
    else if (Eye_CorValue[i] >= EyeCor_Maxvalue)
      Eye_CorValue[i] = EyeCor_Maxvalue;

    //    Serial.print(Eye_Value[i]);
    //    Serial.print(";");
    //
    //    Serial.print(Eye_CorValue[i]);
    //    Serial.print(";");

    Direction_Eye_Value[i] = Eye_CorValue[i] * Eye_Weighted[i];
    Direction_Total_Eye_Value = Direction_Total_Eye_Value +  Direction_Eye_Value[i];
  }
  // Serial.print("Direction_Total_Eye_Value : ");
  // Serial.print(Direction_Total_Eye_Value);
  //Serial.println("");

  if (Eye_CorValue[0] >= (EyeCor_Maxvalue - 20))
  {
    if (Eye_CorValue[1] >= (EyeCor_Maxvalue - 20))
    {
      if (Eye_CorValue[2] >= (EyeCor_Maxvalue - 20))
      {
        if (Eye_CorValue[3] >= (EyeCor_Maxvalue - 20))
        {
          if (Eye_CorValue[4] >= (EyeCor_Maxvalue - 20))
          {
            if (Eye_CorValue[5] >= (EyeCor_Maxvalue - 20))
            {
              if (Eye_CorValue[7] >= (EyeCor_Maxvalue - 20))
              {
                if (Eye_CorValue[8] >= (EyeCor_Maxvalue - 20))
                {
                  if (Eye_CorValue[9] >= (EyeCor_Maxvalue - 20))
                  {
                    if (Eye_CorValue[10] >= (EyeCor_Maxvalue - 20))
                    {
                      if (Eye_CorValue[11] >= (EyeCor_Maxvalue - 20))
                      {
                        if (Eye_CorValue[12] >= (EyeCor_Maxvalue - 20))
                        {
                          return CrossUpdateFlag;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
