#include <Wire.h>
#include <VL53L0X.h>

int PWMPin = 3; 

VL53L0X sensor;

void setup()
{
  pinMode(PWMPin, OUTPUT); 
  
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  
  sensor.startContinuous();
}

void loop()
{
  int distance = ((int)sensor.readRangeContinuousMillimeters()-38); // -38
  int distancePWM = map(distance, 0, 500, 0, 255);
  if(distancePWM > 255) {
    distancePWM = 255; 
  }
  analogWrite(PWMPin, distancePWM); 
  
  Serial.println(distance);
  //Serial.println(distancePWM); 
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
}
