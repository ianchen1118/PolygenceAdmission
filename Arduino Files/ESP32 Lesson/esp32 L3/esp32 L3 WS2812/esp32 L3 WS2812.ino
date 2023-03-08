void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
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

void loop() {
  data(0x004D00);
  data(0x005BAE);
  data(0xFFFFFF);
  RES(); 
}

//REG_WRITE(GPIO_OUT_W1TS_REG, BIT13); HIGH
//REG_WRITE(GPIO_OUT_W1TC_REG, BIT13); LOW

/*
0x4D0000 00 4D 00
0x5B00AE 00 5B AE
0xFFFFFF FF FF FF
*/

/*

void first() {
  for(int i=0; i<8; i++) {
    bitLOW(); 
  }

  bitLOW();
  bitHIGH();
  bitLOW();
  bitLOW();
  bitHIGH();
  bitHIGH();
  bitLOW();
  bitHIGH();

  for(int i=0; i<8; i++) {
    bitLOW(); 
  }

}

void sec() {
  for(int i=0; i<8; i++) {
    bitLOW(); 
  }

  bitLOW();
  bitHIGH();
  bitLOW();
  bitHIGH();
  bitHIGH();
  bitLOW();
  bitHIGH();
  bitHIGH();
  
  bitHIGH();
  bitLOW();
  bitHIGH();
  bitLOW();
  bitHIGH();
  bitHIGH();
  bitHIGH();
  bitLOW();

}

void third() {
  for(int i=0; i<24; i++) {
    bitHIGH(); 
  }

}

void run() {
  first();
  sec(); 
  third(); 
  RES(); 
}
*/
