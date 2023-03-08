void setup() {
  Serial.begin(115200); 
  Serial2.begin(9600); 
}

void loop() {
  Serial.print("Test"); 
  Serial2.print("Test2"); 
  delay(1); 
}
