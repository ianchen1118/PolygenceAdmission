#include <OLD_MotorDrive_V100.h>
#include <vector>
#include <list>
/////////////////////////////////////////////////////////Version Note////////////////////////////////////////////////////////////////////////
/*
v3.0.2 is adapted to only ESP32 S3, with the use of vectors and list. Thus, any arduino series can not be used with this program. 
This program is designed for RCJ Maze 2022.
v3.0.2 Features:
Algorithm up to 128 nodes at max. Only serial input/output at the moment. Low dependency
Motor Control and Movements are adapted to ESP32 S3
Follow Wall are working for both sides.

v3.0.2 Non-Functional / Untested / Uncompleted Methods:
Blind Follow

v3.0.2 To be Added Methods:
ReadWall
Turn90
MoveOneBlock
ReadOCR
*/


////////////////////////////////////////////////////////// Motor Define //////////////////////////////////////////////////////////////////////
#define AI1 40                //Motor A I1
#define AI2 41                //Motor A I2
#define PwmOutputA 42                //Motor A PWM
#define InterruptA1 4                //Motor A Interrupt1
//#define InterruptA2                //Motor A Interrupt2
#define BI1 37                //Motor B I1
#define BI2 38                //Motor B I2
#define PwmOutputB 39                //Motor B PWM
#define InterruptB1 5                //Motor B Interrupt1
//#define InterruptB2                //Motor B Interrupt2
#define XI1 45                //Motor X I1
#define XI2 36                 //Motor X I2
#define PwmOutputX 35                //Motor X PWM
#define InterruptX1 6                //Motor X Interrupt1
//#define InterruptX2                //Motor X Interrupt2 
#define YI1 21                //Motor Y I1
#define YI2 47                //Motor Y I2
#define PwmOutputY 48                //Motor Y PWM
#define InterruptY1 7                //Motor Y Interrupt1
//#define InterruptY2                //Motor Y Interrupt2

long MotorA_Counter = 0;          //Motor position//
long MotorB_Counter = 0;          //X             A
long MotorX_Counter = 0;          //|             |
long MotorY_Counter = 0;          //Y             B

OLD_MotorDrive_V100Class MotorA;
OLD_MotorDrive_V100Class MotorB;
OLD_MotorDrive_V100Class MotorX;
OLD_MotorDrive_V100Class MotorY;

////////////////////////////////////////////////////////// PID Cal //////////////////////////////////////////////////////////////////////
#define Kp 1.68  //1.68
#define Ki 0.6   //0.6
#define Kd 0.8   //0.8
#define rightMaxSpeed 120
#define leftMaxSpeed 120
#define cos45 0.7071067812
#define sin45 0.7071067812
#define piover8 0.39269908169
#define RtoD 57.29578

float PosError;  //
float FuturePosError;
float LastError = 0;
unsigned long cTime, pTime;
float eTime;
float P_error;
float I_error;
float D_error;
float PID_value;
int leftMotorSpeed;
int rightMotorSpeed;
////////////////////////////////////////////////////////////////// lazer ///////////////////////////////////////////////////////////////////////////
int RecivePin[4] = { 15, 16, 8, 3 };  //38 front left 40 back left
int distancePWM[4] = {};
int distance[4] = {};
#define TIMEOUT 10000

/////////////////////////////////////////////////////////////////algroithm//////////////////////////////////////////////////////////
int nextNode = 1;
int currentNode = 0;
char facing = 'N';  // N ,S W ,E  //this is not always true, you might have to update this mighttt
int8_t Map[200][200]; //int8_t -128 to 127
int posx = 100;
int posy = 100;
std::vector<int8_t> adj[500];  //changed

////////////////////////////////////////////////////////////Long Lazer/////////////////////////////////////////////////////////
int dist;  //actual distance measurements of LiDAR
int i;
int check;
int uart[9];              //save data measured by LiDAR
const int HEADER = 0x59;  //frame header of data package

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 18, 17);
  MotorSetup();
  for(int i=0; i<4; i++) {
    pinMode(RecivePin[i], INPUT);
  }
/*
  for(int i = 0; i < 10; i++){
    lazerRead();
    posErrorCalculate();
    PIDValueCalculate();
  }*/

  // 200, 200 is the starting node ( node 0 );
  /*
  for (int i = 0; i < 200; i++) {
    for (int j = 0; j < 200; j++) {
      Map[i][j] = -1;  //-1 means the cord has no node
    }
  }
  //read node 0; // 200, 200 is the starting node ( node 0 );
  Map[100][100] = 0;
  DFS(adj, 0, 500);
  */
  for(int i = 0; i < 1000; i++){
    longLaserRead();
    delay(1);
  }
  moveOneBlock(); 
}

void loop() {
  
}
