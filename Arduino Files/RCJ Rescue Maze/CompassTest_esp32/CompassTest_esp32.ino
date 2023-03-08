#include <QMC5883LCompass.h>

QMC5883LCompass compass;

int aMax = 0, aMin = 999999;
double fieldToDegree;
int startingField;

void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(115200);
  compass.init();
  Wire.begin(); 

  callibrate();
  fieldToDegree = abs(aMax) + abs(aMin);
  fieldToDegree /= 180;
  compass.read();
}

void loop() {
  compass.read();
  Serial.print("Max: ");
  Serial.print(aMax);
  Serial.print(" Min: ");
  Serial.print(aMin);
  Serial.print(" Field: ");
  Serial.print(compass.getY());
  Serial.print("  Angle: ");
  Serial.println(aMax / fieldToDegree - compass.getY() / fieldToDegree);
}

void callibrate(){
  Serial.println("Callibrating");
  int v;
  for(int i = 0; i < 10000; i++){
    compass.read();
    v = compass.getY();
    if(v > aMax){
        aMax = v; 
    }
    if(v < aMin){
        aMin = v;
    }
    if(i % 200 == 0){
      digitalWrite(13,HIGH);
    } else {
      digitalWrite(13,LOW);
     }
    delay(1);
  }
}
