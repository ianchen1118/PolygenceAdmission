typedef uint8_t u8;

u8 cmd[5] = {0x55, 0xAA, 0x81, 0x00, 0xFA};  //获取距离指令

typedef struct {
  int distance;
  u8 ErrorCode; //TOF错误码请参考使用说明书
  boolean receiveComplete;
} TF;
TF Lidar = {0,0,false};

/***************************************
 *  通讯协议：
 *  2 byte : 帧头 0x55 0xAA
 *  1 byte : 功能码 (详细参考使用说明) 例：0x81 获取距离值 单位:mm
 *  1 byte : 后面参数的长度
 *  N byte : 设定参数
 *  1 byte : 帧尾 0xFA
 *  ***************************************
 *  例：获取距离值
 *  Arduino 发送：55 AA 81 00 FA
 *  TOF模组回复 ： 55 AA 81 03 01 55 00 FA
 **************************************/
void getLidarData(TF* lidar) {
  static char i = 0;
  static int rx[8];
  if (Serial.available())
  {
    rx[i] = Serial.read();
    if (rx[0] != 0x55)
    {
      i = 0;
    } else if (i == 1 && rx[1] != 0xAA)
    {
      i = 0;
    } else if (i == 7)
    {
      i = 0;
      if (rx[7] == 0xFA)
      {
        lidar->distance = rx[5] + rx[4] * 256;
        lidar->ErrorCode  = rx[6];
        lidar->receiveComplete = true;
      }
    } else
    {
      i++;
    }
  }
}

void setup() {
/********************************
 *  TOF串口协议：TTL
 *  波特率：115200
 *  数据位：8
 *  停止位：1
 *  奇偶校验：无
 *  流控：无
 **************************************/
  Serial.begin(115200);       //通过硬件串口来获取实时性要求比较高的雷达数据，软串口容易出现掉帧的情况   
  Serial.begin(115200, SERIAL_5N1, 17, 18);

  pinMode(17, OUTPUT); 
  pinMode(18, INPUT); 
}

void loop() {
  if (!Lidar.receiveComplete)
  {
    Serial.write(cmd, 5);
  } else
  {
    Port_Print_Ascii(&Lidar);          // Ascii 打印输出结果
    //Port_Print_Benewake_9Byte(&Lidar);   // 北醒通用9Byte打印
    Lidar.receiveComplete = false;
    delay(33);                       //延时33ms,雷达探测速率最快33ms
  }
}

void Port_Print_Ascii(TF* lidar)
{
  Serial.print("Dist = ");
  Serial.println(lidar->distance);
  if(lidar->ErrorCode)
  {
    Serial.print("ErrorCode = ");
    Serial.println(lidar->ErrorCode,HEX);
  }
}

void SerialEvent() {
  getLidarData(&Lidar);
}
