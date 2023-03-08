#include <Wire.h> 

void setup() {
  Wire.begin(); 
  Serial.begin(115200); 
}

void loop() {
  int data = 0; 
  Wire.beginTransmission(0x62); 
  Wire.write(0x01);
  Wire.endTransmission(true); 
  Wire.requestFrom(0x62, 4);
  while(Wire.available()) {
    data = Wire.read();  
    Serial.print(data); 
  }
  Serial.println("");
  delay(10);
}

/* 
I2C recieve:
  Wire.requestFrom(adress, length);
    adress: memory adress 
    length: unit in byte 
  val = Wire.available();
    val: number of data 
  data = Wire.read();
*/
