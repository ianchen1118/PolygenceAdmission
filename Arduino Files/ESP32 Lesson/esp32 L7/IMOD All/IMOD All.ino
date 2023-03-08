#include <Wire.h> 

int data[100] = {}; 

int functions(int address, int command, int returnLength) { 
  int counter = 0; 
  int dataLength = 0; 
  Wire.beginTransmission(address); 
  Wire.write(command);
  Wire.endTransmission(true); 
  if(returnLength == 0) {
    return dataLength; 
  }
  Wire.requestFrom(address, returnLength);
  dataLength = Wire.available(); 
  while(Wire.available()) {
    data[counter] = Wire.read(); 
    counter++; 
  }
  delay(10);
  return dataLength; 
}

void setup() {
  Wire.begin(); 
  Serial.begin(115200); 
}

void loop() {
  char commandNum = 'N'; 
  int dataLength1 = 0; 
  if(Serial.available()) {
    commandNum = Serial.read();
    Serial.print(commandNum);  
  }
  switch (commandNum) {
    case 'a':
      dataLength1 = functions(0x62, 0x01, 4);
      //Serial.println("case 1"); 
      break;
    case 'b':
      dataLength1 = functions(0x62, 0x10, 2);
      break;
    case 'c':
      dataLength1 = functions(0x62, 0x11, 1);
      break;
    case 'd':
      dataLength1 = functions(0x62, 0x20, 0);
      break;
    case 'e':
      dataLength1 = functions(0x62, 0x30, 0);
      break;
  } 
  for(int i = 0; i<dataLength1; i++) {
    Serial.print(data[i]);
  }
  //Serial.println(""); 
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
