void PIDValueCalculate(){
  cTime = millis();
  eTime = (float)(cTime - pTime) / 1000;  // how many seconds had past from the last calculation
  //changed to FuturePosError
  P_error = FuturePosError;
  I_error = I_error * 2 / 3;
  I_error += P_error * eTime;
  D_error = (FuturePosError - LastError) / eTime; 

  PID_value =  Kp * P_error + Ki * I_error + Kd * D_error; 

  LastError = P_error; //last error update
  pTime = cTime; //pervious time update


  //now we have the PID_Value for the motor to move accordingly
  //positive PID means the robot is to the left of the middle line; thus, leftspeed > rightspeed
}