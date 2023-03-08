#include <esp_task_wdt.h>

void setup() {
  Serial.begin(115200);

  esp_task_wdt_init(3, 1);
  esp_task_wdt_add(NULL);
  Serial.println("Config WDT");
}

void loop() {
  for(int i=0; i<5; i++) {
    Serial.println("Resetting WDT");
    esp_task_wdt_reset();
    delay(1000);
  }

  while(true) {
    Serial.println("Stopping WDT");
    delay(1000);
  }
 
}


/*
esp_task_wdt_init(TIMEOUT, enable);
  TIMEOUT: limit time(sec)
  enable: if reset code 
esp_task_wdt_add(task)
  Which task to moderate (current NULL)
esp_task_wdt_reset()
  Reset WDT counter 
*/
