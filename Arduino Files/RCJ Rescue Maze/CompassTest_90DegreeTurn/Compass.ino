void CompassSetup() {
  while (!compass.begin())
  {
    Serial.println("Could not find a valid QMC5883 sensor, check wiring!");
    delay(500);
  }
  Serial.println("Initialize QMC5883");
  compass.setRange(QMC5883_RANGE_2GA);
  compass.setMeasurementMode(QMC5883_CONTINOUS); 
  compass.setDataRate(QMC5883_DATARATE_50HZ);
  compass.setSamples(QMC5883_SAMPLES_8);
  Serial.println("Finish init");
}

float CompassDegree() {
   Serial.println("In Degree"); 
   Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / PI);
  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0){
    heading += 2 * PI;
  }

  if (heading > 2 * PI){
    heading -= 2 * PI;
  }

  // Convert to degrees
  float headingDegrees = heading * 180/M_PI; 

  return headingDegrees; 
}

void Turn90R() {
  int oldDegree = CompassDegree();
  Serial.println(CompassDegree());
  Motor.MotorX_CW_DirectMode(MaxMotorPWM);
  Motor.MotorY_CCW_DirectMode(MaxMotorPWM);
  delay(30);
  while(1) {
    POWER_OFF;
    int c = CompassDegree();
    Serial.println(c); 
    if( c - oldDegree > 92) {
      RLED_ON;
      Motor.MotorX_CCW_DirectMode(MaxMotorPWM);
      Motor.MotorY_CW_DirectMode(MaxMotorPWM);
    }
    else if(c - oldDegree < 88) {
      GLED_ON;
      Motor.MotorX_CW_DirectMode(MaxMotorPWM);
      Motor.MotorY_CCW_DirectMode(MaxMotorPWM);
    }
    else{
      break; 
    }
  }
}
