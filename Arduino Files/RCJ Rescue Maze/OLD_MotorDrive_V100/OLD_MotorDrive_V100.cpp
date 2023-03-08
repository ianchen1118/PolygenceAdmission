/*
 *   The Following Firmware is support Arduino and ESP32 MainBoard 
 *                          
 *   support IC: TB6612、TB6552        
 */
 /*! 
 * \file       OLD_MotorDrive_V100
 * \brief      DC Motor Driver Function
 *
 * \last edition	popo_Mega2560_MotorDrive_V3
 * \version 	    100
 * \date       		Nov 10 2022
 * \author     		Popo Wu
 *	
 *
 * \Note(100)        First Edition	1.
 *									2.
 *									3.
 *
 *
 * Last modified by Popo on Nov 12 2022
 */ 

#include "Arduino.h"
#include "OLD_MotorDrive_V100.h"


/*****************************************************************************
                              General Init
							  
note:ESP32 does not allow more than 6~16 PWMs

*****************************************************************************/
void OLD_MotorDrive_V100Class::Motor_Reverse(bool R_Flag)						
{
	if(R_Flag == Enable)
		_gobalReverse_Flag = Enable;	
	else
		_gobalReverse_Flag = Disable;
}

#if (ESP32)
int OLD_MotorDrive_V100Class::InitInBrake(byte i1, byte i2, byte pwmpin, byte channel)
{
	Serial.print("OLD_MotorDrive use ESP32 platform, firmware version is V");
	Serial.println(FirmwareVersion);
	Serial.println("Warning: ESP32 C3 does not allow more than 6 PWMs");
	Serial.println("Warning: ESP32 S does not allow more than 16 PWMs");
	Serial.println("Warning: ESP32 S2 does not allow more than 8 PWMs");	
	Serial.println("Warning: ESP32 S3 does not allow more than 8 PWMs");
	
  
  _inputPin1 = i1;
  _inputPin2 = i2;
  _pwmOutputPin = pwmpin;
  _pwmChannel = channel;
  
  pinMode(_inputPin1,OUTPUT);
  pinMode(_inputPin2,OUTPUT);

	ledcSetup(_pwmChannel, 1000, 8);   //ledChannel, freq, resolution
	ledcAttachPin(_pwmOutputPin, _pwmChannel);	//Pin, ledChannel

  Brake_Lock();
  
  DirectMode_Enable();
  _interruptCounter = 0;
  Motor_Reverse(Disable);
  
  return 1;
}
#else
int OLD_MotorDrive_V100Class::InitInBrake(byte i1, byte i2, byte pwmpin)
{

	Serial.print("OLD_MotorDrive use other platform, firmware version is V");
	Serial.println(FirmwareVersion);
	Serial.println("If you want use ESP32 platform, you must use API: InitInBrake(byte i1, byte i2, byte pwmpin, byte channel)");
	
  _inputPin1 = i1;
  _inputPin2 = i2;
  _pwmOutputPin = pwmpin;
  
  pinMode(_inputPin1,OUTPUT);
  pinMode(_inputPin2,OUTPUT);

	pinMode(_pwmOutputPin, OUTPUT);
  
  Brake_Lock();
  
  DirectMode_Enable();
  _interruptCounter = 0;
  Motor_Reverse(Disable);
  
  return 1;
}
#endif

void OLD_MotorDrive_V100Class::DirectMode_Enable(void)
{ 
  _interruptCounter = 0;
}

void OLD_MotorDrive_V100Class::DirectMode_Disable(void)
{
  _interruptCounter = 0;
}

/*****************************************************************************
                              Motor_DirectMode(Via Interrupt)

*****************************************************************************/
bool OLD_MotorDrive_V100Class::CW_DirectMode(int level)
{
  if(_gobalReverse_Flag == Enable)	
  {
	digitalWrite(_inputPin1,HIGH);
    digitalWrite(_inputPin2,LOW);
  }
  else
  {
	digitalWrite(_inputPin1,LOW);
    digitalWrite(_inputPin2,HIGH);   
  }
  #if (ESP32)
	ledcWrite(_pwmChannel, level);	//ledChannel, dutyCycle
  #else
	analogWrite(_pwmOutputPin, level);
  #endif
  
  return 1;
}

bool OLD_MotorDrive_V100Class::CCW_DirectMode(int level)
{
  if(_gobalReverse_Flag == Enable)
  {
	digitalWrite(_inputPin1,LOW);
    digitalWrite(_inputPin2,HIGH);
  }
  else
  {
	digitalWrite(_inputPin1,HIGH);
    digitalWrite(_inputPin2,LOW);
  }
  
  #if (ESP32)
	ledcWrite(_pwmChannel, level);	//ledChannel, dutyCycle
  #else
	analogWrite(_pwmOutputPin, level);
  #endif
  
  return 1;
}

/*****************************************************************************
                            Motor_WaitMode(Wait for whilelopp)

*****************************************************************************/
void OLD_MotorDrive_V100Class::CW_WaitMode(int level, long step)
{
  _interruptCounter = 0;
  DirectMode_Disable();
  
  if(_gobalReverse_Flag == Enable)	
  {
	digitalWrite(_inputPin1,HIGH);
    digitalWrite(_inputPin2,LOW);
  }
  else
  {
	digitalWrite(_inputPin1,LOW);
    digitalWrite(_inputPin2,HIGH);   
  }
  
  #if (ESP32)
	ledcWrite(_pwmChannel, level);	//ledChannel, dutyCycle
  #else
	analogWrite(_pwmOutputPin, level);
  #endif
  
  while(_interruptCounter <= step)
  {
//    Serial.println("_interruptCounter");
  }Brake_Lock();_interruptCounter = 0;
}

void OLD_MotorDrive_V100Class::CCW_WaitMode(int level, long step)
{
  _interruptCounter = 0;
  DirectMode_Disable();
  
  if(_gobalReverse_Flag == Enable)
  {
	digitalWrite(_inputPin1,LOW);
    digitalWrite(_inputPin2,HIGH);
  }
  else
  {
	digitalWrite(_inputPin1,HIGH);
    digitalWrite(_inputPin2,LOW);
  }
  
  #if (ESP32)
	ledcWrite(_pwmChannel, level);	//ledChannel, dutyCycle
  #else
	analogWrite(_pwmOutputPin, level);
  #endif
  
  while(_interruptCounter <= step)
  {
//    Serial.println("_interruptCounter");
  }Brake_Lock();_interruptCounter = 0;
}

/*****************************************************************************
                              Motor_Brake
*****************************************************************************/

void OLD_MotorDrive_V100Class::Brake_Lock(void)
{
  #if (ESP32)
	ledcWrite(_pwmChannel, 0);	//ledChannel, dutyCycle
  #else
	analogWrite(_pwmOutputPin, 0);
  #endif
  
  digitalWrite(_inputPin1,LOW);
  digitalWrite(_inputPin2,HIGH);
}


void OLD_MotorDrive_V100Class::Brake_Slide(void)
{
  #if (ESP32)
	ledcWrite(_pwmChannel, 255);	//ledChannel, dutyCycle
  #else
	analogWrite(_pwmOutputPin, 255);
  #endif
  
  digitalWrite(_inputPin1,LOW);
  digitalWrite(_inputPin2,LOW);
}

/*****************************************************************************
                              Motor_Interrupt
*****************************************************************************/

long OLD_MotorDrive_V100Class::interrupt(void)
{
  _interruptCounter++;
  GobalStep = _interruptCounter;
  //Serial.print("_interruptCounter = ");Serial.println(_interruptCounter);
  return _interruptCounter;
}
