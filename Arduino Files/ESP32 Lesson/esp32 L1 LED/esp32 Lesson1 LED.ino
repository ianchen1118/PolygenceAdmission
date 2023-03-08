int LED1_GPIO = 2;
int Btn1_GPIO = 25;


void IRAM_ATTR LED_Blink() {
  digitalWrite(LED1_GPIO, !digitalRead(LED1_GPIO));
  delay(10);
}

void setup() {
  pinMode(LED1_GPIO, OUTPUT);
  pinMode(Btn1_GPIO, INPUT);
  attachInterrupt(Btn1_GPIO, LED_Blink, LOW);
  Serial.begin(9600);
}

void loop() {
  Serial.print("");
}


//attachInterrupt(GPIO, function, mode)
/*
Mode:
  LOW: active when low 
  HIGH: active when high 
  CHANGE: low/high alter 
  FALLING: From high to low
  RISING: From low to high 
*/
