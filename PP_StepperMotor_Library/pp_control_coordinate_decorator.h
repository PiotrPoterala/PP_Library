#ifndef _PP_CONTROL_COORDINATE_DECORATOR_H
	#define _PP_CONTROL_COORDINATE_DECORATOR_H

#include "pp_stepper_motor_driver_decorator.h"
#include <vector>

using namespace std;

class defOControlCoordinateDecorator : public defOStepperMotorDriverDecorator{
	
	#define DO_NOTHING_WITH_STEP			0
	#define ADD_STEP									1
	#define SUBTRACT_STEP							2
	
private:
		int correctionUM;
		int typeOfCorrection;

		defOParam* phyCoord;
		defOParam* baseCoord;
	
	public:
		defOControlCoordinateDecorator(defOStepperMotorDriver* stepMotorDriver, pair<char,defOParam*> pCoord, defOParam* bCoord, int corrUM=0);	
	
		virtual void rotateForward();
		virtual void rotateBackwards();

	
};


#endif
