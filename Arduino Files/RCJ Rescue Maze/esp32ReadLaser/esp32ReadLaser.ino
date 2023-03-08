/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

int SDA1[2] = {17, 19};
int SCL1[2] = {16, 18};
int result;
int result1;
int corResult;
int corResult1;


VL53L0X sensor(0);
VL53L0X sensor1(1); 

void setup()
{
  Serial.begin(9600);
  Wire.begin(SDA1[0], SCL1[0]);
  Wire1.begin(SDA1[1], SCL1[1]);

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  sensor1.setTimeout(500);
  if (!sensor1.init())
  {
    Serial.println("Failed to detect and initialize sensor1!");
    while (1) {}
  }

  sensor.startContinuous();
  sensor1.startContinuous();

  ledcSetup(0,3000,8);
  ledcAttachPin(12,0);

  ledcSetup(1,3000,8);
  ledcAttachPin(14,1);
}

void loop()
{

  result = sensor.readRangeContinuousMillimeters();
  Serial.println("Sensor: ");
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  corResult = map(result, 0,1000,0,255);
  ledcWrite(0, corResult);
  Serial.print("  result: ");
  Serial.println(result); 
  Serial.print("  CorResult: ");
  Serial.println(corResult);

  result1 = sensor1.readRangeContinuousMillimeters();
  Serial.println("Sensor1: ");
  if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  corResult1 = map(result1, 0,1000,0,255);
  ledcWrite(1, corResult1);
  Serial.print("  result1: ");
  Serial.println(result1); 
  Serial.print("  CorResult1: ");
  Serial.println(corResult1);
}
