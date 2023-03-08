/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
#include <SoftwareSerial.h>

int rxPin =2; 
int txPin =3; 

VL53L0X sensor;
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

void setup()
{
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT); 
  
  Serial.begin(9600);
  mySerial.begin(115200);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    mySerial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  
  sensor.startContinuous();
}

void loop()
{
  int distance = ((int)sensor.readRangeContinuousMillimeters()); // -38
  mySerial.print(distance);
  mySerial.print(",");
  Serial.println(distance); 
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
}
