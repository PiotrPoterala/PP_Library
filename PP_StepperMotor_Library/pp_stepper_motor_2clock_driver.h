#ifndef _PP_STEPPER_MOTOR_2CLOCK_DRIVER_H
	#define _PP_STEPPER_MOTOR_2CLOCK_DRIVER_H

#include "pp_stepper_motor_driver.h"
#include <vector>

using namespace std;

class defOStepperMotor2clockDriver : public defOStepperMotorDriver{
	
	
	#define PHASAES_MASK			0x3
	#define INPUTS_MASK				0xff
	
	private:
		int typeOfStep;	
	
		int posOfSequence;
		int previousPosOfSequence;
		vector<int>* maskStep;
		vector<int> maskFullStep={0x1,0x3,0x2,0x0};
		vector<int> maskHalfStep={0x3C,0x1DD,0x3C1,0x1DF,0x3F,0x1DE,0x3C2,0x1DC};
		vector<int> maskMicroStep={2,2,2,2};
	
	public:
		defOStepperMotor2clockDriver(int tOfStep=FULL_STEP);	
	
		int phasesMask;
		int microsteppingMask;
	
		void setTypeOfStep(int tOfStep);
	
		virtual void rotateForward();
		virtual void rotateBackwards();

//		virtual bool confirmRotateForward();
//		virtual bool confirmRotateBackwards();
	
};


#endif
