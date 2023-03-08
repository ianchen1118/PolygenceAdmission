void setup() {
  pinMode(15, OUTPUT); 
  pinMode(2, OUTPUT); 
}

void loop() {
  for (int i=0; i<10;i++) {
    digitalWrite(15, 1); 
    delay(10);
    digitalWrite(15, 0); 
    delay(10); 
  }
  for (int i=0; i<10; i++) {
    digitalWrite(15, 1); 
    delay(1); 
    digitalWrite(15, 0); 
    delay(1); 
  }
  for (int i=0; i<10; i++) {
    digitalWrite(2, 1); 
    delay(2); 
    digitalWrite(2, 0);
    delay(2); 
  }
}
