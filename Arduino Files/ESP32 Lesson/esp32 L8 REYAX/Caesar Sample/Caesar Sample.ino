void setup() {
  Serial.begin(115200); 
}

void loop() {
  int letter;
  if(Serial.available()) {
    letter = Serial.read(); 
    if(letter + 9 <= 90) {
      Serial.write(letter + 9); 
    }
    else {
      Serial.write(letter - 26 + 9); 
    }
  }
}
