int RecivePin[4] = {15,16,17,18}; 
int distancePWM[4]; 
int distance[4]; 
const unsigned long TIMEOUT = 10000;
int readPWM(int pin);

void setup() {
  Serial.begin(9600);
  for(int i=0; i<4; i++) {
    pinMode(RecivePin[i], INPUT);
  }
}

void loop() {
  for(int i = 0; i<4; i++) {
    distancePWM[i] = readPWM(RecivePin[i]);
    distance[i] = map(distancePWM[i], 0, 255, 0, 1000);
    Serial.print(i); 
    Serial.print(": "); 
    Serial.println(distance[i]);
  }
}

int readPWM(int pin)
{
  unsigned long highDuration = pulseIn(pin, HIGH, TIMEOUT); 
  unsigned long lowDuration = pulseIn(pin, LOW, TIMEOUT);

  //Serial.print(highDuration);
  //Serial.print(", ");
  //Serial.print(lowDuration);
  //Serial.print(" -> ");

  if (highDuration == 0 || lowDuration == 0)
    return digitalRead(pin) == HIGH ? 255 : 0;

  return (highDuration * 255) / (highDuration + lowDuration);
}
