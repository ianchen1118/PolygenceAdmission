int LED = 15; 
long res = 32767;

void setup() {
  ledcSetup(0, 1000, 15);
  ledcAttachPin(LED, 0);
}

void loop() {
  for(long i = 0; i< res; i++) {
    ledcWrite(0, i);
  }
  for(long i = 0; i< res; i++) {
    ledcWrite(0, res-i);
  }
}


  /* 
  ledcSetup(LEDChannel, freq, resoluion)
    LEDChannel: Use which channel(0-15)
    freq: PWM frequency (limited by resolution)
    resolution: PWM resolution (1-15, biger higher)
  ledcAttachPin(ledPin, LEDChannel)
    lenPin: GPIO Pin 
    LEDChannel: What channel to attach to 
  ledcWrite(LEDChannel, dutyCycle)
    LEDChannel: Select Channel 
    dutyCycle: time for positive wave(divide by the resolution)
  */
