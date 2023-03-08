#include <Wire.h>

void setup() {
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(0x04);
  Wire.write(0x88);  
  Wire.endTransmission(true);
  delay(1); 
}


/*
I2C
  #inclde <Wire.h>
  Wire.begin(); 

Command 
  Wire.beginTransmissio(adress)
  Wire.write(data)
  Wire.endTransmission(State); 
  */ 