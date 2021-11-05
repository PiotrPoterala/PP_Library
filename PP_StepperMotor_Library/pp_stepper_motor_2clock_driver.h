#ifndef _PP_STEPPER_MOTOR_2CLOCK_DRIVER_H
	#define _PP_STEPPER_MOTOR_2CLOCK_DRIVER_H

#include "pp_stepper_motor_driver.h"
#include <vector>

using namespace std;

class defOStepperMotor2clockDriver : public defOStepperMotorDriver{
	
	#define FULL_STEP		0
	#define HALF_STEP		1
	#define MICRO_STEP	2
	
	private:
		int typeOfStep;	
	
		int posOfSequence;

		vector<int>* maskStep;
		vector<int> maskFullStep={0x1,0x3,0x2,0x0};
		vector<int> maskHalfStep={0x3C,0x1DD,0x3C1,0x1DF,0x3F,0x1DE,0x3C2,0x1DC};
		vector<int> maskMicroStep={2,2,2,2};
	
	public:
		defOStepperMotor2clockDriver(int paccelerationMMperSEC2, defOParam* pvelocityUMperSEC, int tOfStep=FULL_STEP);	
	
		void setTypeOfStep(int tOfStep);
	
		virtual void rotateForward();
		virtual void rotateBackwards();

//		virtual bool confirmRotateForward();
//		virtual bool confirmRotateBackwards();
	
};


#endif
