int numRegister = 4;
bool data[8] = {0, 0, 0, 0, 0, 0, 0 ,0};

int a = 1;
int sec = 0; 
int miniute = 0;
int day = 0;
int date = 0; 
int month = 0;
int year = 0; 
String days[7] = {"Mon", "Tues", "Wed", "Thu", "Fri", "Sat", "Sun"};

void Start() {
  pinMode(A4, OUTPUT);
  digitalWrite(A4, 0);
  delayMicroseconds(2);
  digitalWrite(A5, 0);
  delayMicroseconds(2);
}

void Stop() {
  pinMode(A4, OUTPUT);
  digitalWrite(A4, 0);
  digitalWrite(A5, 0);
  delayMicroseconds(2);
  digitalWrite(A5, 1);
  digitalWrite(A4, 1);

  delay(10);
  //Serial.println();
}

void hexToBi(int hex) {
  int bitMask = 0x80;
  for(int i = 0; i < 8; i++) {
    if(hex&(bitMask >> i)) {
      data[i] = 1;
    }
    else {
      data[i] = 0;
    }
  }
}

void Write(int hex) {
  pinMode(A4, OUTPUT);
  hexToBi(hex);
  for (int i = 0; i < 8; i++) {
    digitalWrite(A4, data[i]);
    digitalWrite(A5, 1);
    delayMicroseconds(2);
    digitalWrite(A5, 0);
    delayMicroseconds(2);
  }
}

int Read() {
  byte back = 0; 
  pinMode(A4, INPUT);
  //Serial.print("ReadBinary: ");
  for(int i=0; i<8; i++) {
    digitalWrite(A5, 1);
    delayMicroseconds(1);
    //Serial.print(digitalRead(A4));
    back <<= 1;
    if(digitalRead(A4) == 1) {
      back |= 1;
    }
    else {
      back &= 0xfe;
    }
    delayMicroseconds(1);
    digitalWrite(A5, 0);
    delayMicroseconds(2);
  }
  //Serial.println();
  //Serial.print("back: ");
  //Serial.println(back);
  return back;
}

void WriteAck() {
  int a = 0;
  pinMode(A4, INPUT);
  digitalWrite(A5, 1);
  while(a==1) {
    a = digitalRead(A4);
  }
  //Serial.println(a);
  a = 1;
  pinMode(A4, OUTPUT);

  digitalWrite(A5, 0);
  digitalWrite(A4, 0);
  delayMicroseconds(2);
}

void ReadAck() {
  pinMode(A4, OUTPUT);
  digitalWrite(A4, 0);
  digitalWrite(A5, 1);
  delayMicroseconds(2);
  digitalWrite(A5, 0);
  delayMicroseconds(2);
}

void setSec(int x){
  int num = x%10; 
  int ten = x/10;
  Start();
  Write((0x68) << 1);
  WriteAck();
  Write(0x00);
  WriteAck();
  Write((ten << 4) + num);
  WriteAck();
  Stop();
}

void setMin(int x){
  int num = x%10; 
  int ten = x/10;
  Start();
  Write((0x68) << 1);
  WriteAck();
  Write(0x01);
  WriteAck();
  Write((ten <<4)+num);
  WriteAck();
  Stop();
}

void setHour(int x){
  int num = x%10; 
  int ten = x/10;
  Start();
  Write((0x68) << 1);
  WriteAck();
  Write(0x02);
  WriteAck();
  Write((ten <<4)+num);
  WriteAck();
  Stop();
}

void setDay(int x){
  int num = x%10; 
  int ten = x/10;
  Start();
  Write((0x68) << 1);
  WriteAck();
  Write(0x03);
  WriteAck();
  Write((ten <<4)+num);
  WriteAck();
  Stop();
}

void setDate(int x){
  int num = x%10; 
  int ten = x/10;
  Start();
  Write((0x68) << 1);
  WriteAck();
  Write(0x04);
  WriteAck();
  Write((ten <<4)+num);
  WriteAck();
  Stop();
}

void setMonth(int x){
  int num = x%10; 
  int ten = x/10;
  Start();
  Write((0x68) << 1);
  WriteAck();
  Write(0x05);
  WriteAck();
  Write((ten <<4)+num);
  WriteAck();
  Stop();
}

void setYear(int x){
  int num = x%10; 
  int ten = x/10;
  Start();
  Write((0x68) << 1);
  WriteAck();
  Write(0x06);
  WriteAck();
  Write((ten <<4)+num);
  WriteAck();
  Stop();
}

int getSec() {
  Start();
  Write(((0x68) << 1));
  WriteAck();
  Write(0x00);
  WriteAck();
  Stop();
  Start();
  Write(((0x68) << 1) +1);
  WriteAck();
  int x = Read();
  Stop();

  int ten = (x >> 4) *10;
  int num = (x & 0x0F);
  return (ten + num);
}

int getMin() {
  Start();
  Write(((0x68) << 1));
  WriteAck();
  Write(0x01);
  WriteAck();
  Stop();
  Start();
  Write(((0x68) << 1) +1);
  WriteAck();
  int x = Read();
  Stop();

  int ten = (x >> 4) *10;
  int num = (x & 0x0F);
  return (ten + num);
}

int getHour() {
  Start();
  Write(((0x68) << 1));
  WriteAck();
  Write(0x02);
  WriteAck();
  Stop();
  Start();
  Write(((0x68) << 1) +1);
  WriteAck();
  int x = Read();
  Stop();

  int ten = (x >> 4) *10;
  int num = (x & 0x0F);
  return (ten + num);
}

int getDay() {
  Start();
  Write(((0x68) << 1));
  WriteAck();
  Write(0x03);
  WriteAck();
  Stop();
  Start();
  Write(((0x68) << 1) +1);
  WriteAck();
  int x = Read();
  Stop();

  int ten = (x >> 4) *10;
  int num = (x & 0x0F);
  return (ten + num);
}

int getDate() {
  Start();
  Write(((0x68) << 1));
  WriteAck();
  Write(0x04);
  WriteAck();
  Stop();
  Start();
  Write(((0x68) << 1) +1);
  WriteAck();
  int x = Read();
  Stop();

  int ten = (x >> 4) *10;
  int num = (x & 0x0F);
  return (ten + num);
}

int getMonth() {
  Start();
  Write(((0x68) << 1));
  WriteAck();
  Write(0x05);
  WriteAck();
  Stop();
  Start();
  Write(((0x68) << 1) +1);
  WriteAck();
  int x = Read();
  Stop();

  int ten = (x >> 4) *10;
  int num = (x & 0x0F);
  return (ten + num);
}

int getYear() {
  Start();
  Write(((0x68) << 1));
  WriteAck();
  Write(0x06);
  WriteAck();
  Stop();
  Start();
  Write(((0x68) << 1) +1);
  WriteAck();
  int x = Read();
  Stop();

  int ten = (x >> 4) *10;
  int num = (x & 0x0F);
  return (ten + num);
}

void setTime(int Sec, int Min, int Hour, int Day, int Date, int Month, int Year) {
  setSec(Sec);
  setMin(Min);
  setHour(Hour);
  setDay(Day);
  setDate(Date);
  setMonth(Month);
  setYear(Year);
}

void getTime() {
  /*
  Serial.print("Sec: ");
  Serial.println(getSec());
  Serial.print("Min: ");
  Serial.println(getMin());
  Serial.print("Hour: ");
  Serial.println(getHour());
  Serial.print("Day: ");
  Serial.println(getDay());
  Serial.print("Date: ");
  Serial.println(getDate());
  Serial.print("Month: ");
  Serial.println(getMonth());
  Serial.print("Year: ");
  Serial.println(getYear());
  Serial.println();
  */

  Serial.print(2000 + getYear());
  Serial.print("/");
  if(getMonth() /10 == 0){
    Serial.print(0);
  }
  Serial.print(getMonth());
  Serial.print("/");
  if(getDate() /10 == 0){
    Serial.print(0);
  }
  Serial.print(getDate());
  Serial.print(" ");
  if(getHour() /10 == 0){
    Serial.print(0);
  }
  Serial.print(getHour());
  Serial.print(":");
  if(getMin() /10 == 0){
    Serial.print(0);
  }
  Serial.print(getMin());
  Serial.print(":");
  if(getSec() /10 == 0){
    Serial.print(0);
  }
  Serial.print(getSec());
  Serial.print(" ");
  Serial.println(days[getDay()]);
  Serial.println();
}

  
