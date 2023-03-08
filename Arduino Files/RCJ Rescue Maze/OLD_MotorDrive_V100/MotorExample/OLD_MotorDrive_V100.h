/*
 *   The Following Firmware is support Arduino and ESP32 MainBoard 
 *                          
 *   support IC: TB6612、TB6552        
 */
 /*! 
 * \file       OLD_MotorDrive_V100
 * \brief      DC Motor Driver Function
 *
 * \last edition  popo_Mega2560_MotorDrive_V3
 * \version       100
 * \date          Nov 10 2022
 * \author        Popo Wu
 *  
 *
 * \Note(100)        First Edition  1.
 *                  2.
 *                  3.
 *
 *
 * Last modified by Popo on Nov 12 2022
 */ 

#ifndef OLD_MotorDrive_V100
#define OLD_MotorDrive_V100

  #define FirmwareVersion 100
  
  #define Enable 1
  #define Disable 0
  #define NonReverse 1
  #define Reverse 0
/*
  #define PwmOutputA 8              //Motor A PWM
  #define PwmOutputB 11             //Motor B PWM
  #define PwmOutputX 7              //Motor X PWM
  #define PwmOutputY 13             //Motor Y PWM
  #define AI1 17                //Motor A BI1
  #define AI2 16                //Motor A BI2
  #define BI1 15                //Motor B BI1
  #define BI2 14                //Motor B BI2
  #define XI1 24                //Motor X BI1
  #define XI2 22                //Motor X BI2
  #define YI1 23                //Motor Y BI1
  #define YI2 25                //Motor Y BI2
*/  

class OLD_MotorDrive_V100Class
{
  public:
      
    void Motor_Reverse(bool);
    #if (ESP32) 
      int InitInBrake(byte, byte, byte, byte);
    #else
      int InitInBrake(byte, byte, byte);
    #endif
    void DirectMode_Enable(void);
    void DirectMode_Disable(void);
    bool CW_DirectMode(int);
    bool CCW_DirectMode(int);
    void CW_WaitMode(int, long);
    void CCW_WaitMode(int, long);
    void Brake_Lock(void);
    void Brake_Slide(void);

    long interrupt(void);
    
    volatile long GobalStep = 0;
    
  private:
  //protected:
  
    byte _inputPin1 = 0;
    byte _inputPin2 = 0;
    byte _pwmOutputPin = 0;
    byte _pwmChannel = 0;
    bool _gobalReverse_Flag = 0;  

    volatile long _interruptCounter = 0;

};

#endif
