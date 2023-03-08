#include <EEPROM.h>

void setup() {
  Serial.begin(115200);
  EEPROM.begin(10);
  for(int i =0; i<10; i++) {
    int value = EEPROM.read(i);
    Serial.print(i);
    Serial.print(": ");
    Serial.println(value);
  }

  for(int i = 0; i<10; i++) {
    EEPROM.write(i, i+10);
  }
  EEPROM.commit();
}

void loop() {
  
}

/*
EEPROM.begin(num)
  Seperate storage space(max 4096), byte 
  Smaller better, affect read speed 

EEPROM.write(addr, data)
  Adress in EEPROM, what data
value = EEPROM.read(addr) 
  Read from address to value 
EEPROM.commit()
  Actually start writing 
*/