#include <Adafruit_NeoPixel.h>

#define PIN        48 
#define NUMPIXELS 3 

const int HPin = 10;
const int SPin = 11;
const int UPin = 12;
const int readyPin = 13;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void HarmedStop() {
  if(digitalRead(readyPin) || 1) { //Need add Not already detected, using map
    for(int i =0; i<5; i++) {
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      pixels.setPixelColor(1, pixels.Color(255, 0, 0));
      pixels.setPixelColor(2, pixels.Color(255, 0, 0));
      pixels.show();  
      delay(500); 
      pixels.clear(); 
      pixels.show(); 
      delay(500);
    }
  }
}

void StableStop() {
  if(digitalRead(readyPin) || 1) { //Need add Not already detected, using map
    for(int i =0; i<5; i++) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 255));
      pixels.setPixelColor(1, pixels.Color(0, 0, 255));
      pixels.setPixelColor(2, pixels.Color(0, 0, 255));
      pixels.show();  
      delay(500); 
      pixels.clear(); 
      pixels.show(); 
      delay(500);
    }
  }
}

void UnharmedStop() {
  if(digitalRead(readyPin) || 1) { //Need add Not already detected, using map
    for(int i =0; i<5; i++) {
      pixels.setPixelColor(0, pixels.Color(0, 255, 0));
      pixels.setPixelColor(1, pixels.Color(0, 255, 0));
      pixels.setPixelColor(2, pixels.Color(0, 255, 0));
      pixels.show();  
      delay(500); 
      pixels.clear(); 
      pixels.show(); 
      delay(500);
    }
  }
}

void victimStop() {
  //Motor Stop?
  if(digitalRead(HPin)) {
    HarmedStop(); 
  }
  else if(digitalRead(SPin)) {
    StableStop();
  }
  else if(digitalRead(UPin)) {
    UnharmedStop(); 
  }
}

void setup() {
  pinMode(HPin, INPUT);
  pinMode(SPin, INPUT);
  pinMode(UPin, INPUT);
  pinMode(readyPin, INPUT); 

  pixels.begin();
  pixels.clear();

  Serial.begin(9600);
}

void loop() {
  victimStop();
}

