typedef uint8_t u8;

u8 cmd[5] = { 0x55, 0xAA, 0x81, 0x00, 0xFA };

typedef struct {
  int distance;
  u8 ErrorCode;  //TOF错误码请参考使用说明书
  boolean receiveComplete;
} TF;

TF Lidar = { 0, 0, false };

int rx[8] = {};

int laserDist() {
  int frx[8] = {}; 
  int dist = 0; 
  while (1) {
    Serial2.write(cmd, 5);

    if (Serial2.available()) {
      for (int i = 0; i < 8; i++) {
        frx[i] = Serial2.read();
        //Serial.println(rx[i], HEX);
      }
      if (frx[6] == 0) {
        dist = frx[5] + (frx[4] * 256);
        return dist; 
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 18, 17);
}

void loop() {
  Serial.print("dist = ");
  Serial.println(laserDist()); 
}


  // if(!Lidar.receiveComplete) {
  //   Serial2.write(cmd, 5);
  // }
  // else{
  //   Serial.print("dist = ");
  //   Serial.println(Lidar.distance);
  //   Lidar.receiveComplete = false;
  // }

  // if(Serial2.available()) {
  //   for(int i=0; i<8; i++) {
  //     rx[i] = Serial2.read();
  //     //Serial.println(rx[i], HEX);
  //   }
  //   if(rx[6] == 0) {
  //     Lidar.distance = rx[5] + (rx[4] * 256);
  //     Lidar.receiveComplete = true;
  //   }
  // }
