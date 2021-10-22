#ifndef _CONTROL_2CLOCK_SIGNALS_DECORATOR_H
	#define _CONTROL_2CLOCK_SIGNALS_DECORATOR_H

#include "pp_stepper_motor_driver_decorator.h"
#include <array>

using namespace std;

class defOControl2ClockSignalsDecorator : public defOStepperMotorDriverDecorator{
	
	
	#define PHASAES_MASK			0x3
	#define MICROSTEPPING_MASK				0xff
	
	private:
		void setStateOfPins();
	
		GPIO_TypeDef* phasesPort;
		GPIO_TypeDef* inputsPort;
	
		array<int, 2> *phasesPins;
		array<int, 8> *inputsPins;
	
	public:
		defOControl2ClockSignalsDecorator(defOStepperMotorDriver* stepMotorDriver, GPIO_TypeDef* pPort, array<int, 2> *pPins, GPIO_TypeDef* iPort, array<int, 8> *iPins);	
	
		virtual void rotateForward();
		virtual void rotateBackwards();
	
};


#endif
