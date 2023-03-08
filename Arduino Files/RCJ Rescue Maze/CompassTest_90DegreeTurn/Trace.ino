void Trace(void)
{
  /*************************************************************************************/
  /*
                          @ Algorithm_A
     Simple Mode
  */
  /*************************************************************************************/

  Abs_Direction_Total_Eye_Value = abs(Direction_Total_Eye_Value);
  Div_Abs_Direction_Total_Eye_Value = map(Abs_Direction_Total_Eye_Value, 0, Const_BoundaryTotalValue, MinMotorPWM, MaxMotorPWM);
  if (Div_Abs_Direction_Total_Eye_Value > MaxMotorPWM)
    Div_Abs_Direction_Total_Eye_Value = MaxMotorPWM;
  if (Div_Abs_Direction_Total_Eye_Value < MinMotorPWM)
    Div_Abs_Direction_Total_Eye_Value = MinMotorPWM;
  /*
    Serial.print("Direction_Total_Eye_Value = ");
    Serial.print(Direction_Total_Eye_Value);
    Serial.print("  ||  Div_Abs_Direction_Total_Eye_Value = ");
    Serial.println(Div_Abs_Direction_Total_Eye_Value);
  */

  if (Direction_Total_Eye_Value >= Const_MidTotalValue_Area)          //left     go to right
  {
    Motor.MotorX_CW_DirectMode(MaxMotorPWM);
    Motor.MotorY_CW_DirectMode(MaxMotorPWM - Div_Abs_Direction_Total_Eye_Value);
  }
  else if (Direction_Total_Eye_Value < (-1 * Const_MidTotalValue_Area))                                      //right     go to left
  {
    Motor.MotorX_CW_DirectMode(MaxMotorPWM - Div_Abs_Direction_Total_Eye_Value);
    Motor.MotorY_CW_DirectMode(MaxMotorPWM);
  }
  else
  {
    Motor.MotorX_CW_DirectMode(MaxMotorPWM - 30);                     //S
    Motor.MotorY_CW_DirectMode(MaxMotorPWM - 30);
  }

}
