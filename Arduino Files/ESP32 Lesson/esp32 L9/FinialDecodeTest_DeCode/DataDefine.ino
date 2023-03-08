void SetBitTime(int unit)
{
  BitLongDelay = unit * 6 / 10;
  BitShortDelay = unit * 4 / 10;
}

int GetKey(long Long, long Short)
{
  byte key;
  long temp;
  temp = Long + Short;
  if (temp <= KeyTimeScale + 100)
    key = 1;
  else if (temp <= (KeyTimeScale * 2) + 100)
    key = 2;
  else if (temp <= (KeyTimeScale * 3) + 100)
    key = 3;
  else if (temp <= (KeyTimeScale * 4) + 100)
    key = 4;
  else if (temp <= (KeyTimeScale * 5) + 100)
    key = 5;
  else if (temp <= (KeyTimeScale * 6) + 100)
    key = 6;
  else if (temp <= (KeyTimeScale * 7) + 100)
    key = 7;
  else if (temp <= (KeyTimeScale * 8) + 100)
    key = 8;
  else if (temp <= (KeyTimeScale * 9) + 100)
    key = 9;
  else if (temp <= (KeyTimeScale * 10) + 100)
    key = 10;
  else if (temp <= (KeyTimeScale * 11) + 100)
    key = 11;
  return key;
}

int GetData(byte key, long n7, long n6, long n5, long n4, long n3, long n2, long n1, long n0)
{
  int Data = 0;
  if ((key * KeyTimeScale / 2) < n7)
    Data = Data + pow(2, 7);
  if ((key * KeyTimeScale / 2) < n6)
    Data = Data + pow(2, 6);
  if ((key * KeyTimeScale / 2) < n5)
    Data = Data + pow(2, 5);
  if ((key * KeyTimeScale / 2) < n4)
    Data = Data + pow(2, 4);
  if ((key * KeyTimeScale / 2) < n3)
    Data = Data + pow(2, 3);
  if ((key * KeyTimeScale / 2) < n2)
    Data = Data + pow(2, 2);
  if ((key * KeyTimeScale / 2) < n1)
    Data = Data + pow(2, 1);
  if ((key * KeyTimeScale / 2) < n0)
    Data = Data + pow(2, 0);
  return Data;
}

void Bit1(void)
{
  ledcWrite(0, dutycycle);
  digitalWrite(CodePin, HIGH);
  delayMicroseconds(BitLongDelay);
  ledcWrite(0, 0);
  digitalWrite(CodePin, LOW);
  delayMicroseconds(BitShortDelay);
}

void Bit0(void)
{
  ledcWrite(0, dutycycle);
  digitalWrite(CodePin, HIGH);
  delayMicroseconds(BitShortDelay);
  ledcWrite(0, 0);
  digitalWrite(CodePin, LOW);
  delayMicroseconds(BitLongDelay);
}

void SendPreamble(byte num)
{
  pinMode(CodePin, OUTPUT);
  for (int i = 0 ; i < num; i ++)
  {
    Bit1();
    Bit0();
  }
}

void SendTrailer(byte num)
{
  pinMode(CodePin, OUTPUT);
  for (int i = 0 ; i < num; i ++)
  {
    Bit0();
    Bit1();
  }
}

void SendData(byte txd)
{
  for (int i = 0; i < 8; i++)
  {
    if ((txd & 0x80) >> 7)
      Bit1();
    else
      Bit0();
    txd = txd << 1;
  }
}

char EnCode(char txd, byte key)
{
  // a = 97;  z = 122
  return CodeTable[key - 1][txd - 97];
}

void AckCorrect(void)
{
  Bit1();
  Bit1();
  Bit1();
  Bit1();
}

void AckError(void)
{
  Bit1();
  Bit0();
  Bit0();
  Bit1();
}

void DeCodeMode(void)
{
  pinMode(CodePin, INPUT_PULLUP);
}

char DeCode(void)
{
  byte key;
  char encodeChar;
  char decodeChar;
  long temp = 0;
  //delayMicroseconds(KeyTimeScale / 2);                            //passthrough first preamble 0b1
  PeriodArray[2] = pulseIn(CodePin, HIGH, KeyNum * KeyTimeScale * 2); //second preamble 0
  PeriodArray[3] = pulseIn(CodePin, HIGH, KeyNum * KeyTimeScale * 2); //third preamble 1
  key = GetKey(PeriodArray[3], PeriodArray[2]);
  Serial.print("key = ");
  Serial.print(key);
  Serial.print(" | Decoding........");
  for (int i = 4; i < 26; i++)
  {
    PeriodArray[i] = pulseIn(CodePin, HIGH, key * KeyTimeScale * 2);
    //    if (PeriodArray[i] == 0)
    //      i = 0;
  }
  encodeChar = GetData(key, PeriodArray[9], PeriodArray[10], PeriodArray[11], PeriodArray[12], PeriodArray[13], PeriodArray[14], PeriodArray[15], PeriodArray[16]);
  //  if (encodeChar < ('a' + KeyNum))//k
  //    encodeChar += (KeyNum);
  for (int i = 0; i < 26; i++)
  {
    if (encodeChar == CodeTable[key - 1][i])
      temp = i;
  }
  decodeChar = CodeTable[0][temp];

  Serial.print(" || encodeChar = ");
  Serial.print(encodeChar);
  return decodeChar;
}
