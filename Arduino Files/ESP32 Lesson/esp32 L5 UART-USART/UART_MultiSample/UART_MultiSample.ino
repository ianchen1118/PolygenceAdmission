void setup() {
  pinMode(2, OUTPUT); 
  pinMode(15, OUTPUT); 
  digitalWrite(2, 1);
  digitalWrite(15, 1); 
  delay(10);
}

void loop() {
  digitalWrite(2, 0);
  digitalWrite(15, 0);
  delayMicroseconds(52); 

  digitalWrite(2, 1);
  digitalWrite(15, 0);
  delayMicroseconds(52); 
  digitalWrite(2, 0);
  digitalWrite(15, 1);
  delayMicroseconds(52); 
  digitalWrite(2, 0);
  digitalWrite(15, 0);
  delayMicroseconds(52); 
  digitalWrite(2, 0);
  digitalWrite(15, 0);
  delayMicroseconds(52); 
  digitalWrite(2, 0);
  digitalWrite(15, 0);
  delayMicroseconds(52); 
  digitalWrite(2, 0);
  digitalWrite(15, 0);
  delayMicroseconds(52); 
  digitalWrite(2, 1);
  digitalWrite(15, 1);
  delayMicroseconds(52); 
  digitalWrite(2, 0);
  digitalWrite(15, 0);
  delayMicroseconds(52); 

  digitalWrite(2, 1);
  digitalWrite(15, 1);
  delayMicroseconds(52);

  delay(1); 
}
