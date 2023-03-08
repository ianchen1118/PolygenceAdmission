void setup() {
  Serial.begin(9600); 

}

void loop() {
  Serial.print(123, BIN); 
  delay(1); 
  Serial.print(123, OCT); 
  delay(1); 
  Serial.print(123, DEC); 
  delay(1);
  Serial.print(123, HEX); 
  delay(1); 
}
