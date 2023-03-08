int data; 

void setup() {
  Serial.begin(115200); 
  Serial2.begin(115200); 
}

void loop() {
  if(Serial.available()) {
    data = Serial.read();
    Serial2.write(data); 
  }
  if(Serial2.available()) {
    Serial.println(Serial2.read()); 

  }
}
