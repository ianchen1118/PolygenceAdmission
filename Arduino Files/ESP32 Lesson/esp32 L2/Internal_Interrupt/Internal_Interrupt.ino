hw_timer_t* timerA;
hw_timer_t* timerB;
hw_timer_t* timerC;

bool A = 0;
bool B = 0;
bool C = 0; 

void IRAM_ATTR onTimerA() {
  A = 1;
}

void IRAM_ATTR onTimerB() {
  B = 1;
}

void IRAM_ATTR onTimerC() {
  C = 1; 
}

void setup() {
  Serial.begin(115200);
  timerA = timerBegin(0, 80, 1);
  timerAttachInterrupt(timerA, &onTimerA, 1);
  timerAlarmWrite(timerA, 1000000, 1);
  timerAlarmEnable(timerA);

  timerB = timerBegin(1, 40, 1);
  timerAttachInterrupt(timerB, &onTimerB, 1);
  timerAlarmWrite(timerB, 1000000, 1);
  timerAlarmEnable(timerB);

  timerC = timerBegin(2, 80, 1);
  timerAttachInterrupt(timerC, &onTimerC, 1);
  timerAlarmWrite(timerC, 100000, 1);
  timerAlarmEnable(timerC);
}

void loop() {
  if(A) {
    Serial.println('A');
    A = 0;
  }
  if(B) {
    Serial.println('B');
    B = 0;
  }
  if(C) {
    Serial.println('C');
    C = 0;
  }
}

/*
Interrupt function 
IRAM_ATTR onTmer() {

}
  hw_timer_t * space;
  space = timerBegin(num, perscale, countType);
    num: the counter's number 
    perscale: (2-65535), decide the counter's time to count once 
      80MHz initially, 80M times per sec.
      if perscale = 80, 80M/80 = 1M = count 1M time per sec 
    countType: ascending or deceding, 1 ascend, 0 decend
  timerAttachInterrupt(space, &name, detectType);
    space: name of the space
    &name: name of the atttaching function
    detectType: how event is detected (true: edge, false: voltage)
  timerAlarmWrite(space, value, autoReloadType);
    space: timer struct 
    value: maximum of the counter/ value to generate event (64  bit)
    autoReloadType: auto reset timer 
  timerAlarmEnable(space);
    enable timer 
  */
