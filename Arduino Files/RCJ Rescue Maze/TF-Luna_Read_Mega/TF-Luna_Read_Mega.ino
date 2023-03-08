#include <TFMPlus.h>  // Include TFMini Plus Library v1.5.0
TFMPlus TF_Luna;         // Create a TFMini Plus object 

#define XI1 24
#define XI2 22
#define YI1 23
#define YI2 25  //  U|    Front     |X
#define UI1 15  //   |              |
#define UI2 14  //   |              |
#define ZI1 17  //  Z|              |Y
#define ZI2 16
#define PwmOutputX 7
#define PwmOutputY 13
#define PwmOutputU 11
#define PwmOutputZ 8
                                    
void setup()
{
    Serial.begin(115200);   // Intialize terminal serial port
    TF_Init(TF_Luna); 
}

// Initialize variables
int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;

// Use the 'getData' function to pass back device data.
void loop()
{
    delay(50);   // Loop delay to match the 20Hz data frame rate
    TF_Luna.getData(tfDist, tfFlux, tfTemp);
    Serial.print(tfDist);
    Serial.print(" -> ");
    Serial.println(tfFlux); 
}

void TF_Init(TFMPlus &tf){
    Serial1.begin(115200);  // Initialize TFMPLus device serial port.
    delay(20);               // Give port time to initalize
    tf.begin(Serial1);   // Initialize device library object and...
                             // pass device serial port to the object.
    delay(500);
}

void xAxisCalibrate(TFMPlus &tf) {
  int16_t tfDist = 0;    // Distance to object in centimeters
  int16_t tfFlux = 0;    // Strength or quality of return signal
  int16_t tfTemp = 0;
  int BlockEdgeDistance; 
  
  tf.getData(tfDist, tfFlux, tfTemp);
  BlockEdgeDistance = tfDist % 30;

  while(BlockEdgeDistance != 15) {
    if(BlockEdgeDistance > 15) {
      
    }
  }
}
