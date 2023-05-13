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

#define BAND 915E6

String LoRaData = ""; 

void setup() {
  Serial.begin(115200);
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0); 

  if(!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while(1); 
  }

  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, 0, 0)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay(); 
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LoRa Receiver ");
  display.display(); 
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if(packetSize) {
    Serial.print("Recieved packet ");

    while(LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }
    int rssi = LoRa.packetRssi();
    Serial.print(" with RSSI ");
    Serial.println(rssi); 
    
    display.clearDisplay();
    display.setTextSize(1.5);
    display.setCursor(0,0);
    display.println("LoRa Receiver");
    display.setCursor(0, 20);
    display.print("Received Packet:");
    display.setCursor(0,30);
    display.print(LoRaData);
    display.setCursor(0, 40);
    display.print("RSSI:");
    display.setCursor(30, 40);
    display.print(rssi);
    display.display(); 
  }
}