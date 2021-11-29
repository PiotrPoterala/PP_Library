#ifndef _CONTROL_2CLOCK_SIGNALS_DECORATOR_H
	#define _CONTROL_2CLOCK_SIGNALS_DECORATOR_H

#include "pp_stepper_motor_driver_decorator.h"
#include <vector>
#include <map>

using namespace std;

typedef struct{
	GPIO_TypeDef* port;
	int pin;
}uPin;

typedef struct{
	int clrMask;
	int mask;
}uPortMask;

class defOControl2ClockSignalsDecorator : public defOStepperMotorDriverDecorator{
	
	
	#define PHASAES_MASK			0x3
	#define MICROSTEPPING_MASK				0xff
	
	private:
		void setStateOfPins();
	
	
		vector<uPin> *inputsPins;
		map<GPIO_TypeDef*, uPortMask*> portMask;
	
	public:
		defOControl2ClockSignalsDecorator(defOStepperMotorDriver* stepMotorDriver, vector<uPin> *iPins);	
	
		virtual void rotateForward();
		virtual void rotateBackwards();
	
};


#endif
