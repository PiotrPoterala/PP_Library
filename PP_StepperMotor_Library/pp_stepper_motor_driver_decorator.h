#ifndef _PP_STEPPER_MOTOR_DRIVER_DECORATOR_H
	#define _PP_STEPPER_MOTOR_DRIVER_DECORATOR_H

#include "pp_stepper_motor_driver.h"

using namespace std;

class defOStepperMotorDriverDecorator : public defOStepperMotorDriver{
	
	private:

		defOStepperMotorDriver* stepperMotorDriver;
	
	public:
		defOStepperMotorDriverDecorator(defOStepperMotorDriver* stepMotorDriver);	
	
		virtual void rotateForward();
		virtual void rotateBackwards();

	
};


#endif
