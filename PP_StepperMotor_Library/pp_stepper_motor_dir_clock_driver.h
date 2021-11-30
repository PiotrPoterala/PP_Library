#ifndef _MOTOR_PARALLEL_DRIVER_H
	#define _MOTOR_PARALLEL_DRIVER_H

#include "pp_stepper_motor_driver.h"

using namespace std;

class defOStepperMotorDirClockDriver : public defOStepperMotorDriverPar{
	
	private:
		int maskStep;
	
	public:
		defOStepperMotorDirClockDriver(defOParam* paccelerationMMperSEC2, defOParam* pvelocityUMperSEC):defOStepperMotorDriverPar(paccelerationMMperSEC2, pvelocityUMperSEC){};	
	
		virtual void rotateForward()override{maskStep=0;};
		virtual void rotateBackwards()override{maskStep=1;};
		virtual int getSignalMask()override{return maskStep;};

};


#endif
