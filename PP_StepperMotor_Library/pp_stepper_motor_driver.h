#ifndef _PP_STEPPER_MOTOR_DRIVER_H
	#define _PP_STEPPER_MOTOR_DRIVER_H

#include "pp_param.h"

using namespace std;

class defOStepperMotorDriver{
	
	
	public:
		char acronim;	
		int signalsMask;
		int counter;
	
		defOStepperMotorDriver(){acronim='0';};	
			

		virtual void rotateForward() =0;
		virtual void rotateBackwards() =0;

	
};


#endif
