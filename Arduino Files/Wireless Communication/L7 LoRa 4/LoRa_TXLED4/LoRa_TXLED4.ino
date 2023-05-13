#include <SPI.h>
#include <LoRa.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26

#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST 16
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST); 

#define BAND 922E6

hw_timer_t* timer;
String LoRaData = ""; 
String SlaveCounter= ""; 
String printData = ""; 
int counter = 0; 
bool flag = 1; 
int rssi = -1; 
long long lastTime = 0; 
long long lastLED = 0; 
bool LEDState = 0; 

void IRAM_ATTR onTimer() {
  digitalWrite(13, LEDState); 
  LEDState = !LEDState; 
}

void setup() {
  Serial.begin(115200);

  pinMode(25, OUTPUT); 
  pinMode(13, OUTPUT); 

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0); 

  if(!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while(1); 
  }

  LoRa.setPreambleLength(6); 
  LoRa.setTxPower(20, PA_OUTPUT_PA_BOOST_PIN); 
  LoRa.setFrequency(922E6); 
  LoRa.setSpreadingFactor(12); 
  LoRa.setSignalBandwidth(125000); 
  LoRa.setCodingRate4(5); 

  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, 0, 0)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  timer = timerBegin(0, 80, 1);
  timerAttachInterrupt(timer, &onTimer, 1);
  timerAlarmWrite(timer, 400000, 1);
  timerAlarmEnable(timer);

  display.clearDisplay(); 
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LoRa Transmitter ");
  display.display(); 
}

void loop() {
  display.clearDisplay();

  Serial.print("Sending packet: ");
  Serial.println("A"); 

  if((millis() - lastTime > 2000)) {
    digitalWrite(25, 1); 
    delay(200); 
    digitalWrite(25, 0); 
    LoRa.beginPacket();
    LoRa.print("A ");
    LoRa.print(counter); 
    LoRa.endPacket();
    counter++; 
    lastTime = millis(); 
  }
  
  display.setTextSize(1.5);
  display.setCursor(0,0);
  display.println("LoRa Transmitter");
  display.setCursor(0, 20);
  display.print("Sending Packet:");
  display.setCursor(0,30);
  display.print("A");
  display.display(); 
}
