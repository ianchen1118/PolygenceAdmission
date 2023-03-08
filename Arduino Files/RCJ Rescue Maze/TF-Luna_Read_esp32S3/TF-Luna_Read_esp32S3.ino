/* For Arduinoboards with multiple serial ports like DUEboard, interpret above two pieces of code and
directly use Serial1 serial port*/
int dist;  //actual distance measurements of LiDAR
int i;
int check;
int uart[9];              //save data measured by LiDAR
const int HEADER = 0x59;  //frame header of data package

void setup() {
  Serial.begin(9600);     //set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200, SERIAL_8N1, 18, 17);   //set bit rate of serial port connecting LiDAR with Arduino
}

void loop() {
  //Serial.println("69");
  if (Serial1.available()) {         //check if serial port has data input
    if (Serial1.read() == HEADER) {  //assess data package frame header 0x59
      uart[0] = HEADER;
      if (Serial1.read() == HEADER) {  //assess data package frame header 0x59
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) {  //save data in array
          uart[i] = Serial1.read();
        }

        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];

        if (uart[8] == (check & 0xff)) {   //verify the received data as per protocol
          dist = uart[2] + uart[3] * 256;  //calculate distance value
          Serial.print("dist = ");
          Serial.println(dist);  //output measure distance value of LiDAR
        }
      }
    }
    
  }
  
}
