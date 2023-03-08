void setup() {
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  Serial.begin(115200);
  digitalWrite(A5, 1);
  digitalWrite(A4, 1);

  setTime(2, 5, 1, 2, 1, 10, 22);
}

void loop() {
  getTime();
}
