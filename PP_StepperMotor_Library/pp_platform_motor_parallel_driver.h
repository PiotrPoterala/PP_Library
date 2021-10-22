#ifndef _PLATFORM_MOTOR_PARALLEL_DRIVER_H
	#define _PLATFORM_MOTOR_PARALLEL_DRIVER_H

#include "motor_parallel_driver.h"
#include <array>

using namespace std;

class defOPlatformParallelMotorDriver: public defOParallelMotorDriver{
	
	
	private:
//		defOParallelMotorDriver *driver;
	
		void setStateOfPins();
	
		GPIO_TypeDef* phasesPort;
		GPIO_TypeDef* inputsPort;
	
		array<int, 2> *phasesPins;
		array<int, 8> *inputsPins;
	
	public:
		defOPlatformParallelMotorDriver(pair<char, defOParam*> pCoord, pair<char, defOParam*> bCoord, GPIO_TypeDef* pPort, array<int, 2> *pPins, GPIO_TypeDef* iPort, array<int, 8> *iPins, int tOfStep=FULL_STEP, int corrUM=0);	
	
		virtual void rotateForward();
		virtual void rotateBackwards();

		virtual bool confirmRotateForward();
		virtual bool confirmRotateBackwards();
	
};


#endif
