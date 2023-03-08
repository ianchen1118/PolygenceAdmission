#include <Wire.h>

int data = 0; 

void setup() {
  Wire.begin(); 
  Serial.begin(115200);
}

void loop() {
  Wire.requestFrom(0x04, 1);
  int val = Wire.available();
  Serial.println(val);
  while (Wire.available()) {
    int data = Wire.read(); 
  } 
  Serial.println(data);
  delay(1); 
}
