void posErrorCalculate() {
  bool X_Accessible = false;
  bool Y_Accessible = false;


  if(distance[2] < 350){
    X_Accessible = true;
  } else {
    X_Accessible = false;
  }
  // if(distance[2] > 500){
  //   Y_Accessible = false;
  // } else {
  //   Y_Accessible = true;
  // }
  //X_Accessible = true;
  if(X_Accessible){
    readRightSide();
  } else {
    readLeftSide();
  } 

}

int readPWM(int pin) {
  unsigned long highDuration = pulseIn(pin, HIGH, TIMEOUT);
  unsigned long lowDuration = pulseIn(pin, LOW, TIMEOUT);

  if (highDuration == 0 || lowDuration == 0)
    return digitalRead(pin) == HIGH ? 255 : 0;

  return (highDuration * 255) / (highDuration + lowDuration);
}

void lazerRead() {
  for (int i = 0; i < 4; i++) {
    distancePWM[i] = readPWM(RecivePin[i]);
    distance[i] = map(distancePWM[i], 0, 255, 0, 1000);
  }
  distance[0] -= 28;
  distance[1] -= 16;
  distance[2] -= 40;
  distance[3] -= 15;
  // for (int i = 0; i < 4; i++) {
  //   Serial.print(" ");
  //   Serial.print(i);  //left forward 0 left back 3 right forward 1 right back 2
  //   Serial.print(": ");
  //   Serial.print(distance[i]);
  // }
  // Serial.println(" ");
}

void readLeftSide(){
  // only x distance
  int Ydistance1;
  int Ydistance2;
  double angleY = 0;  // in radian
  double top;
  double bottom;
  Ydistance1 = distance[0] + 20;  //a  in mm left forward
  Ydistance2 = distance[3] + 20;  // 25 to cal to the midpoint of the car left back

  Ydistance1 = Ydistance1 * 100;  //exanding calculation resolution
  Ydistance2 = Ydistance2 * 100;
  top = Ydistance1 * cos45 - Ydistance2;
  bottom = Ydistance1 * sin45;
  angleY = atan(top / bottom);
  //angleY += piover8; //correct offset value
  Ydistance2 /= 100;
  PosError = Ydistance2 * cos(angleY);
  PosError = PosError - 150;  //155 is to correct offset //real error is now error + ACsin(angleY) ac is 8
  FuturePosError = PosError + 150 * sin(angleY * 1);

  // Serial.print("Ydistance1: ");
  // Serial.print(Ydistance1 / 100);
  // Serial.print("  Ydistance2: ");
  // Serial.print(Ydistance2);
  // Serial.print("  angleY: ");
  // Serial.print(angleY * RtoD);
  // Serial.print(" PosError:");
  // Serial.print(PosError);
  // Serial.print(" FuturePosError:");
  // Serial.println(FuturePosError);
}

void readRightSide(){
  // only x distance
  int Xdistance1;
  int Xdistance2;
  double angleX = 0;  // in radian
  double top;
  double bottom;
  Xdistance1 = distance[1] + 20;  //a  in mm right forward  
  Xdistance2 = distance[2] + 20;  // 25 to cal to the midpoint of the car right back

  Xdistance1 = Xdistance1 * 100;  //exanding calculation resolution
  Xdistance2 = Xdistance2 * 100;
  top = Xdistance1 * cos45 - Xdistance2;
  bottom = Xdistance1 * sin45;
  angleX = atan(top / bottom);
  //angleY += piover8; //correct offset value
  Xdistance2 /= 100;
  PosError = Xdistance2 * cos(angleX);
  PosError = 150 - PosError;  //155 is to correct offset //real error is now error + ACsin(angleY) ac is 8
  FuturePosError = PosError + 150 * sin(angleX * -1);

  // Serial.print("Xdistance1: ");
  // Serial.print(Xdistance1 / 100);
  // Serial.print("  Xdistance2: ");
  // Serial.print(Xdistance2);
  // Serial.print("  angleX: ");
  // Serial.print(angleX * RtoD);
  // Serial.print(" PosError:");
  // Serial.print(PosError);
  // Serial.print(" FuturePosError:");
  // Serial.println(FuturePosError);
}

void blindForward(int angleOffSet){
  angleOffSet = 0; //LMAO
  PosError *= angleOffSet;
  FuturePosError *= angleOffSet;
}

int longLaserRead() {
  if (Serial1.available()) {         //check if serial port has data input
    if (Serial1.read() == HEADER) {  //assess data package frame header 0x59
      uart[0] = HEADER;
      if (Serial1.read() == HEADER) {  //assess data package frame header 0x59
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) {  //save data in array
          uart[i] = Serial1.read();
        }

        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];

        if (uart[8] == (check & 0xff)) {   //verify the received data as per protocol
          dist = uart[2] + uart[3] * 256;  //calculate distance value
          //Serial.print("dist = ");
          //Serial.println(dist);  //output measure distance value of LiDAR
          return dist+8;
        }
      }
    }
  }
  return dist+8;
}
