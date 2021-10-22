#ifndef _PP_STEPPER_MOTOR_DRIVER_H
	#define _PP_STEPPER_MOTOR_DRIVER_H

#include "pp_param.h"

using namespace std;

class defOStepperMotorDriver{
	
	
	public:
		defOStepperMotorDriver(){};	
			
		int signalsMask;

		virtual void rotateForward() =0;
		virtual void rotateBackwards() =0;

	
};


#endif
