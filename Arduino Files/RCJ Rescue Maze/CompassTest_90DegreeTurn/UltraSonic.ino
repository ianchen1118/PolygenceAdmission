void UltraSonicSetup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int UltraSonicDistance()
{
  long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH, 11000);

  return ((duration / 2) / 29.1);
}
