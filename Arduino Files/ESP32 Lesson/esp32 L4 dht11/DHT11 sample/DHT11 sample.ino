int in[100];

void MCUstart() {
  pinMode(32, OUTPUT);
  digitalWrite(32, 0); 
  delay(20);
  pinMode(32, INPUT);
  delayMicroseconds(50);
}

void DHTstart() {
  pinMode(32, INPUT);
  read(); 
}

void input() {
  for(int i=0; i<50; i++) {
    in[i] = read(); 
  }
}

int read() {
  pinMode(32, INPUT);
  int length = pulseIn(32, HIGH, 150);
  if(length <= 30) {
    return 0;
  }
  return 1;
}

int readHumidity() {
  int humidity = 0; 
  int currentBit = 0;
  for (int i=0; i<8; i++) {
    currentBit = in[i];
    humidity <<= 1;
    humidity += currentBit; 
  }

  return humidity;
}

int readTemperature() {
  int temperature = 0; 
  int currentBit = 0;
  for (int i=0; i<8; i++) {
    currentBit = in[16+i];
    temperature <<= 1;
    temperature += currentBit; 
  }

  return temperature; 
}

int readCheckSum() {
  int checkSum = 0; 
  int currentBit = 0; 
  for (int i=0; i<8; i++) {
    currentBit = in[32+i];
    checkSum <<= 1;
    checkSum += currentBit; 
  }

  return checkSum; 
}

void setup() {
  pinMode(32, OUTPUT);
  digitalWrite(32, 1);
  Serial.begin(115200);
}

void loop() {
  /*
  MCUstart();
  DHTstart();
  for(int i=0; i<40; i++) {
    test[i] = read(); 
  }

  for(int i=0; i<40; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(test[i]); 
  }

  delay(1000); 
  
  */
  
  //01000000
  //00000000
  //00011010
  //00000110
  //01100000
  //0000000000

  MCUstart();
  DHTstart();
  input();
  for(int i=0; i<50; i++) {
    Serial.print(in[i]); 
  }
  Serial.println();

  
  Serial.print("Humidity: ");
  Serial.println(readHumidity());
  Serial.print("Temperature: ");
  Serial.println(readTemperature());
  readCheckSum(); 
  delay(500);
  
}
