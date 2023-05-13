
void LED_Setup(void) {
  pinMode(LightSource, OUTPUT);
  strip.begin();                       // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();                        // Turn OFF all pixels ASAP
  strip.setBrightness(EyeBrightness);  // Set BRIGHTNESS to about 1/5 (max = 255)
  pinMode(WLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(Debug0LED, OUTPUT);
  pinMode(Debug1LED, OUTPUT);

  WLED_OFF;
  RLED_OFF;
  GLED_OFF;
  BLED_OFF;
  Debug0LED_OFF;
  Debug1LED_OFF;

  WLED_ON;
  delay(200);
  RLED_ON;
  delay(200);
  GLED_ON;
  delay(200);
  BLED_ON;
  delay(200);
  Debug0LED_ON;
  delay(200);
  Debug1LED_ON;
  delay(200);

  colorWipe(strip.Color(255, 0, 0), 10);      // Red
  colorWipe(strip.Color(0, 255, 0), 10);      // Green
  colorWipe(strip.Color(0, 0, 255), 10);      // Blue
  colorWipe(strip.Color(255, 255, 0), 10);    // yellow
  colorWipe(strip.Color(255, 255, 255), 10);  // white
}

void ButtonSWRES_Setup(void) {
  pinMode(Button0, INPUT);
  pinMode(Button1, INPUT);

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);

  pinMode(RES, INPUT);
}

void ButtonSWRES_Test(void) {
  Serial1.print("Button0: ");
  Serial1.print(digitalRead(Button0));
  Serial1.print("  Button1: ");
  Serial1.print(digitalRead(Button1));

  Serial1.print("  SW1: ");
  Serial1.print(digitalRead(SW1));
  Serial1.print("  SW2: ");
  Serial1.print(digitalRead(SW2));
  Serial1.print("  SW3: ");
  Serial1.print(digitalRead(SW3));
  Serial1.print("  SW4: ");
  Serial1.print(digitalRead(SW4));

  Serial1.print("  RES: ");
  Serial1.print(analogRead(RES));

  Serial1.println();
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {  // For each pixel in strip...
    strip.setPixelColor(i, color);               //  Set pixel's color (in RAM)
    strip.show();                                //  Update strip to match
    if (wait > 0)
      delay(wait);  //  Pause for a moment
  }
}
