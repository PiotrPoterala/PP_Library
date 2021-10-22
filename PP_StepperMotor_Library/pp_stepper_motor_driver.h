#ifndef _PP_STEPPER_MOTOR_DRIVER_H
	#define _PP_STEPPER_MOTOR_DRIVER_H

#include "pp_param.h"

using namespace std;

class defOStepperMotorDriver{
	
	
	#define FULL_STEP		0
	#define HALF_STEP		1
	#define MICRO_STEP	2
	
	#define DO_NOTHING_WITH_STEP			0
	#define ADD_STEP									1
	#define SUBTRACT_STEP							2
	
//	protected:
	
//		int correctionUM;
//		int typeOfCorrection;
//		bool relizeLeapStep;
//		bool relizeSubstractStepInTravelForward;
//		bool relizeSubstractStepInTravelBack;
	
	public:
		defOStepperMotorDriver(){};	
//	defOStepperMotorDriver(pair<char, defOParam*> pCoord, pair<char, defOParam*> bCoord, int tOfStep=FULL_STEP, int corrUM=0);	
//		pair<char, defOParam*> phyCoord;
//		pair<char, defOParam*> baseCoord;
	
	
		virtual void rotateForward() =0;
		virtual void rotateBackwards() =0;

//		virtual bool confirmRotateForward() =0;
//		virtual bool confirmRotateBackwards() =0;
	
};


#endif
