#ifndef _MOTOR_PARALLEL_DRIVER_H
	#define _MOTOR_PARALLEL_DRIVER_H

#include "motor_driver.h"
#include <vector>

using namespace std;

class defOParallelMotorDriver : public defOMotorDriver{
	
	
	
	#define PHASAES_MASK			0x3
	#define INPUTS_MASK				0xff
	
	private:
		int posOfSequence;
		int previousPosOfSequence;
		vector<int>* maskStep;
		vector<int> maskFullStep={0x1,0x3,0x2,0x0};
		vector<int> maskHalfStep={0x3C,0x1DD,0x3C1,0x1DF,0x3F,0x1DE,0x3C2,0x1DC};
		vector<int> maskMicroStep={2,2,2,2};
	
	public:
		defOParallelMotorDriver(pair<char, defOParam*> pCoord, pair<char, defOParam*> bCoord, int tOfStep=FULL_STEP, int corrUM=0);	
	
		int inputsMask;
	
		void setTypeOfStep(int tOfStep);
	
		virtual void rotateForward();
		virtual void rotateBackwards();

		virtual bool confirmRotateForward();
		virtual bool confirmRotateBackwards();
	
	int metoda_test();
};


#endif
