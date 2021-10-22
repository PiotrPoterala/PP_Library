#include <stdbool.h>
#include "pp_stepper_motor_driver_decorator.h"


defOStepperMotorDriverDecorator::defOStepperMotorDriverDecorator(defOStepperMotorDriver* stepMotorDriver):stepperMotorDriver(stepMotorDriver){
	
}

//ustawienie maski powodującej obrót silnika o jeden krok do tylu
void defOStepperMotorDriverDecorator::rotateBackwards(){	

	stepperMotorDriver->rotateBackwards();
		
}

void defOStepperMotorDriverDecorator::rotateForward(){	

	stepperMotorDriver->rotateForward();
		
}


