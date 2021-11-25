#ifndef _PP_STEPPER_MOTOR_DRIVER_H
	#define _PP_STEPPER_MOTOR_DRIVER_H

#include "pp_param.h"

using namespace std;

class defOStepperMotorDriver{
	
	
	public:
	
		defOStepperMotorDriver(){};	
			
		virtual void rotateForward() =0;
		virtual void rotateBackwards() =0;

		virtual void setAcronim(char pacronim)=0;
		virtual char getAcronim()=0;
			
		virtual int getAccelerationMMperSEC2Value()=0;
		virtual int getVelocityUMperSECValue()=0;
			
		virtual int getSignalMask()=0;
	
};


#endif
