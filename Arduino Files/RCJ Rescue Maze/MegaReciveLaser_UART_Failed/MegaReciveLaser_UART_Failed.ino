#include <SoftwareSerial.h>

int rxPin[6] = {52,11,53,13,50,51};
int txPin[6] = {8,3,9,5,6,7};

SoftwareSerial nano[6] = {SoftwareSerial(rxPin[0], txPin[0]), 
                          SoftwareSerial(rxPin[1], txPin[1]),
                          SoftwareSerial(rxPin[2], txPin[2]),
                          SoftwareSerial(rxPin[3], txPin[3]),
                          SoftwareSerial(rxPin[4], txPin[4]),
                          SoftwareSerial(rxPin[5], txPin[5])};

void setup() {
  for(int i= 0; i<6; i++) {
    pinMode(rxPin[i], INPUT);
    pinMode(txPin[i], OUTPUT);
  }

  Serial.begin(1000000); 
  Serial3.begin(9600);
}

void loop() {
  
  for (int i=0; i<6; i++) {
  Serial.print("Laser");
  Serial.print(i);
  Serial.print(": ");
  Serial.println(LaserDistance(i)); 
  
  }
  
  //Serial.println(LaserDistance(0));
}

int LaserDistance(int index) {
  nano[index].begin(115200);
  int result[10];
  int i=0;
  int out = 0; 
  while(true) {
    if (nano[index].available()) {
      result[i] = nano[index].read() - '0'; 
      //Serial.println(result[i]);
      if(result[i] == -4) { 
        for (int j=0; j<i; j++) {
          out += result[j] * powerTen(i-j-1);
        }
        nano[index].end();
        return out; 
      }
      i++;
    }
  }
}

int powerTen(int x) {
  int out = 1;
  for (int i=0; i<x; i++) {
    out *= 10; 
  }
  return out;
}
