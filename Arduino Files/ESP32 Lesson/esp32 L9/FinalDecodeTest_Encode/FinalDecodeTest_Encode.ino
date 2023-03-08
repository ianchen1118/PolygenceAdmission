#include <random>

const String x = "microsecond"; 
int keyNum = 0; 

void print1(int key) {
  digitalWrite(27, 1);
  delay(key * 10 * 0.6);
  digitalWrite(27, 0);
  delay(key * 10 * 0.4);
}

void print0(int key) {
  digitalWrite(27, 1);
  delay(key * 10 * 0.4);
  digitalWrite(27, 0);
  delay(key * 10 * 0.6);
}

void setup() {
  pinMode(27, OUTPUT); 
  Serial.begin(115200); 
}

void loop() {
  Serial.println("loop"); 
  for(int i=0; i<x.length(); i++) {
    if(keyNum > 11) {
      keyNum = 0; 
    }
    int key = keyNum; 
    for(int j=0; j<4; j++) {
      print1(key);
      print0(key); 
    }
    Serial.println("leave");
    int curLetter = x[i] + key - 2; 
    if(curLetter > 122) {
      curLetter -= 26; 
    }

    Serial.print("curLetter = ");
    Serial.write(curLetter); 
    Serial.println(); 
    
    for(int j=0; j<8; j++) {
      if((curLetter & (B10000000 >> j)) > 0) {
        print1(key);
      }
      else{
        print0(key);
      }
    }

    for(int j=0; j<4; j++) {
      print0(key);
      print1(key); 
    }

    keyNum++; 
    delay(500); 
  }
  delay(1000);
}
