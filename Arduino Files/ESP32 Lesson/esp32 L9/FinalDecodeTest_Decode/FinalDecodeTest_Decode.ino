/*
char key[11][26] {
  {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z}, //1
  {b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a}, //2
  {c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a, b}, //3 
  {d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a, b, c}, //4
  {e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a, b, c, d}, //5
  {f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a, b, c, d, e}, //6
  {g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a, b, c, d, e, f}, //7
  {h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a, b, c, d, e, f, g}, //8
  {i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a, b, c, d, e, f, g, h}, //9
  {j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a, b, c, d, e, f, g, h, i}, //10
  {k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, a, b, c, d, e, f, g, h, i, j}  //11
}
*/

/*

int a[5] = {}; 

void decodeChar(int num) {

}

void setup() {
  pinMode(17, INPUT); 
  Serial.begin(2000000);
}

void loop() {
  if(digitalread(17)) {
    for (int j = 0; j<5; j++) {
      //Serial.println("loop"); 
      int letterBit[8] = {}; 
      long letterEncrypted = 0; 
      long letter = 0; 
      long charHighLow = 0;
      long charHighHigh = 0;
      long charTotal = 0;
      long charKey = 0; 
      charHighLow = pulseIn(17, 0);
      //Serial.print("charHighLow: "); 
      //Serial.println(charHighLow); 
      charTotal = charHighLow/0.4; 
      //Serial.print("charTotal: "); 
      //Serial.println(charTotal);
      charKey = charTotal / 10000;
      //Serial.print("charKey: "); 
      //Serial.println(charKey);
      charHighHigh = charTotal*0.6;
      //Serial.print("charHighHigh: "); 
      //Serial.println(charHighHigh);
      
      //delay(char1Total/1000 * 7);

      for(int i=0; i<6; i++) {
        pulseIn(17, 1);
      }

      for(int i = 0; i<8; i++) {
        long charBitLength = pulseIn(17, 1)/1000;
        //Serial.print("charBitLength");
        //Serial.println(charBitLength); 
        if(charBitLength == charHighHigh/1000) {
          letterBit[i] = 1; 
          //Serial.print('1'); 
          delay(charTotal/1000 * 0.4);
        }
        else {
          letterBit[i] = 0; 
          //Serial.print('0'); 
          delay(charTotal/1000 * 0.6);
        }
      }
      //Serial.println(); 
      for (int i = 0; i<8; i++) {
        //Serial.print(letterBit[i]); 
        letterEncrypted <<= 1; 
        if(letterBit[i] == 1) {
          letterEncrypted += 1; 
        }
      }
      //Serial.println();
      //Serial.print("LetterEncrypted: "); 
      //Serial.println(letterEncrypted);
       
      
      letter = letterEncrypted - (charKey - 1); 
      if(letter < 97) {
        letter += 26;
      }

      //Serial.println(letter); 
      Serial.write(letter); 
      

      for(int i=0; i<8; i++) {
        delay(charTotal/1000);
      }
      delay(500); 
    }
    Serial.println();
  }
}
*/

/*
for (int i = 0; i<8; i++) {
  letterEncrypted <<= letterBit[i]; 
}
    
letter = letterEncrypted - char1key
*/

/*
while pulseIn < 40ms 
  stay in same iteration 
*/

int decode(char x, int key) {
  int letter;
  letter = x - (key - 1);
  if (letter < 97) {
    letter += 26;
  }
  return letter;
}

void setup() {
  pinMode(17, INPUT);
  Serial.begin(2000000);
}

void loop() {
  if (digitalRead(27)) {
    Serial.println("loop");
    long dataTime[25] = {};
    int encodedChar = 0;
    int decodedChar = 0;

    dataTime[1] = pulseIn(27, 1, 11 * 10000 * 2);
    dataTime[2] = pulseIn(27, 1, 11 * 10000 * 2);

    long bitTotalTime = dataTime[1] + dataTime[2];
    Serial.print("bitTotalTime = ");
    Serial.print(bitTotalTime);
    Serial.println();

    long key = bitTotalTime / 10000;
    Serial.print("key = ");
    Serial.println(key);

    for (int i = 3; i < 25; i++) {
      dataTime[i] = pulseIn(27, 1, 11 * 10000 * 2);
    }
    for(int i = 0; i < 24; i++) {
      if(dataTime[i] > bitTotalTime /2) {
        Serial.print("1");        
      }
      else{
        Serial.print("0"); 
      }
    }
    Serial.println();
    //encodedChar = getChar(bitTotalTime, dataTime[8], dataTime[9], dataTime[10], dataTime[11], dataTime[12], dataTime[13], dataTime[14], dataTime[15]);

    for(int i=8; i<16; i++) {
      encodedChar <<= 1; 
      if(dataTime[i] > bitTotalTime / 2) {
        encodedChar += 1; 
      }
    }
    
    Serial.print("encoded = ");
    Serial.print(encodedChar, BIN);
    Serial.print(" | ");
    Serial.write(encodedChar); 
    Serial.println();

    decodedChar = decode(encodedChar, key);

    Serial.print("decoded = ");
    Serial.write(decodedChar);
    Serial.println();
  }
}