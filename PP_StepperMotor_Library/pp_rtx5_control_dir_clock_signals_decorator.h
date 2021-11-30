#ifndef _RTX5_CONTROL_DIR_CLOCK_SIGNALS_DECORATOR_H
	#define _RTX5_CONTROL_DIR_CLOCK_SIGNALS_DECORATOR_H

#include "pp_stepper_motor_driver_decorator.h"
#include <vector>
#include <map>

using namespace std;


class defORTX5ControlDirClockSignalsDecorator : public defOStepperMotorDriverDecorator{
	
	
	
	private:
		void setStateOfPins();
	
		vector<uPin> *inputsPins;
	
	public:
		defORTX5ControlDirClockSignalsDecorator(defOStepperMotorDriver* stepMotorDriver, vector<uPin> *iPins);	
	
		virtual void rotateForward();
		virtual void rotateBackwards();
	
};


#endif
