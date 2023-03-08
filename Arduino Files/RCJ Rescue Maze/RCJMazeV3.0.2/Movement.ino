void moveOneBlock() {
  int distToNext = longLaserRead()%30;
  int originalDist = longLaserRead();
  //Serial.println("a");
  while(originalDist - longLaserRead() <= distToNext + 15) {
    Serial.println(originalDist - longLaserRead());
    moveForward(); 
  }
  MotorA.CW_DirectMode(0);
  MotorB.CW_DirectMode(0);
  MotorX.CCW_DirectMode(0);
  MotorY.CCW_DirectMode(0); 
}

void moveForward() {
  MotorA.CW_DirectMode(40);
  MotorB.CW_DirectMode(40);
  MotorX.CCW_DirectMode(40);
  MotorY.CCW_DirectMode(40); 
}
