//************************* OLED *************************//
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c  //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16
static const unsigned char PROGMEM logo16_glcd_bmp[] = { B00000000, B11000000,
                                                         B00000001, B11000000,
                                                         B00000001, B11000000,
                                                         B00000011, B11100000,
                                                         B11110011, B11100000,
                                                         B11111110, B11111000,
                                                         B01111110, B11111111,
                                                         B00110011, B10011111,
                                                         B00011111, B11111100,
                                                         B00001101, B01110000,
                                                         B00011011, B10100000,
                                                         B00111111, B11100000,
                                                         B00111111, B11110000,
                                                         B01111100, B11110000,
                                                         B01110000, B01110000,
                                                         B00000000, B00110000 };

void setup() {
  // put your setup code here, to run once:
OLEDSetup();

}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(5);
  display.print("Test");
  display.display();

  delay(3000); 
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(5);
  display.print("123");
  display.display();

  delay(3000);  
}


void OLEDSetup(void) {
  display.begin(i2c_Address, true);  // Address 0x3C default

  // 顯示Adafruit的LOGO，算是開機畫面
  display.display();
  delay(100);  // 停0.1秒

  // 清除畫面
  display.clearDisplay();

  // 測試文字
  display.clearDisplay();
  display.setTextSize(2);   // 設定文字大小
  display.setTextColor(1);  // 1:OLED預設的顏色(這個會依該OLED的顏色來決定)

  display.setCursor(0, 0);
  display.print("Welcome");

  display.setCursor(10, 20);
  display.print("OwlLab");

  display.setCursor(15, 40);
  display.print("UI System");

  display.display();  // 要有這行才會把文字顯示出來

  delay(500);
  display.clearDisplay();
  display.setTextSize(1);
  display.display();
}