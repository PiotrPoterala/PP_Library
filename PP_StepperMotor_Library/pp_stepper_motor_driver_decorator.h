#ifndef _PP_STEPPER_MOTOR_DRIVER_DECORATOR_H
	#define _PP_STEPPER_MOTOR_DRIVER_DECORATOR_H

#include "pp_stepper_motor_driver.h"

using namespace std;

class defOStepperMotorDriverDecorator : public defOStepperMotorDriver{
	
	protected:

		defOStepperMotorDriver* stepperMotorDriver;
	
	public:
		defOStepperMotorDriverDecorator(defOStepperMotorDriver* stepMotorDriver):stepperMotorDriver(stepMotorDriver){};
	
		virtual void rotateForward()override{stepperMotorDriver->rotateForward();};
		virtual void rotateBackwards()override{stepperMotorDriver->rotateBackwards();};
	
		virtual void setAcronim(char pacronim)override{stepperMotorDriver->setAcronim(pacronim);};
		virtual char getAcronim()override{return stepperMotorDriver->getAcronim();};
		
		virtual int getAccelerationMMperSEC2Value()override{return stepperMotorDriver->getAccelerationMMperSEC2Value();};
		virtual int getVelocityUMperSECValue()override{return stepperMotorDriver->getVelocityUMperSECValue();};
		
		virtual int getSignalMask()override{return stepperMotorDriver->getSignalMask();};

	
};


#endif
