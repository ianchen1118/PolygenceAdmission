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

void bitLOW() {
  REG_WRITE(GPIO_OUT_W1TS_REG, BIT13);
  for(int i=0; i<14; i++) {
    NOP(); 
  }
  REG_WRITE(GPIO_OUT_W1TC_REG, BIT13);
  for(int i=0; i<32; i++) {
    NOP(); 
  }
}

void bitHIGH() {
  REG_WRITE(GPIO_OUT_W1TS_REG, BIT13);
  for(int i=0; i<28; i++) {
    NOP(); 
  }
  REG_WRITE(GPIO_OUT_W1TC_REG, BIT13);
  for(int i=0; i<24; i++) {
    NOP(); 
  }
}

void RES() {
  delayMicroseconds(55);
}

void light() {
  for(int i =0; i<24; i++) {
    bitHIGH(); 
  }
  RES(); 
}

void data(long x) {
  for(int i=0; i<24; i++) {
    if(x & 0x800000) {
      bitHIGH();
    }
    else{
      bitLOW(); 
    }
    x = x << 1; 
  }
}

void colorDecision(int humidity, int temperature) {
  if(temperature <= 26) {
    data(0x00FF00); 
  }
  else if(temperature == 27) {
    data(0x7DFF00);
  }
  else if(temperature == 28) {
    data(0xFFFF00);
  }
  else if(temperature == 29) {
    data(0xFF0000);
  }
  else if(temperature >= 30) {
    data(0x0000FF);
  }

  switch(humidity) {
    case 50 ... 59:
      data(0x00FF00);
      break;
    case 60 ... 69:
      data(0x7DFF00);
      break;
    case 70 ...79:
      data(0xFFFF00);
      break;
    case 80 ... 89:
      data(0xFF0000);
      break; 
    case 90:
      data(0x0000FF);
      break;
  }

  RES(); 
}

void setup() {
  pinMode(32, OUTPUT);
  digitalWrite(32, 1);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  MCUstart();
  DHTstart();
  input();
  for(int i=0; i<50; i++) {
    Serial.print(in[i]); 
  }
  Serial.println();

  int humidity = readHumidity(); 
  int temperature = readTemperature(); 

  colorDecision(humidity, temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  readCheckSum(); 
  delay(500);
  
}
