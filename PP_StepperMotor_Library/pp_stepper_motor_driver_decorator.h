#ifndef _PP_STEPPER_MOTOR_DRIVER_DECORATOR_H
	#define _PP_STEPPER_MOTOR_DRIVER_DECORATOR_H

#include "pp_stepper_motor_driver.h"

using namespace std;

class defOStepperMotorDriverDecorator : public defOStepperMotorDriver{
	
	protected:

		defOStepperMotorDriver* stepperMotorDriver;
	
	public:
		defOStepperMotorDriverDecorator(defOStepperMotorDriver* stepMotorDriver):stepperMotorDriver(stepMotorDriver){};
	
		virtual void rotateForward(){stepperMotorDriver->rotateBackwards();};
		virtual void rotateBackwards(){stepperMotorDriver->rotateForward();};
	
		virtual void setAcronim(char pacronim){stepperMotorDriver->setAcronim(pacronim);};
		virtual char getAcronim(){return stepperMotorDriver->getAcronim();};
		
		virtual int getSignalMask(){return stepperMotorDriver->getSignalMask();};

	
};


#endif
