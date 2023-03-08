void setup() {
  Serial.begin(9600); 
  Serial2.begin(9600); 
}

void loop() {
  if(Serial.available()) {
    int a = Serial.read(); 
    Serial2.write(a);
  }
  if(Serial2.available()) {
    char a = Serial2.read(); 
    Serial.print(a); 
  }
}
