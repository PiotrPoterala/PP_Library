#include "pp_rtx5_control_dir_clock_signals_decorator.h"
 #include "RTX_Config.h"
 #include "cmsis_os2.h"    

defORTX5ControlDirClockSignalsDecorator::defORTX5ControlDirClockSignalsDecorator(defOStepperMotorDriver* stepMotorDriver, vector<uPin> *iPins):
																																		defOStepperMotorDriverDecorator(stepMotorDriver), inputsPins(iPins){																																																																		
}

void defORTX5ControlDirClockSignalsDecorator::setStateOfPins(){	
		int dirMask, dirClrMask;
	
	
	if(inputsPins->size()==2){
		dirMask=(defOStepperMotorDriverDecorator::getSignalMask() & 0x1)<< inputsPins->at(0).pin;
		dirClrMask=(1<<inputsPins->at(0).pin);
	
		if((inputsPins->at(0).port->ODR & dirClrMask)!=dirMask){
			inputsPins->at(0).port->ODR=(inputsPins->at(0).port->ODR & ~dirClrMask) | dirMask;	
			osDelay(OS_TICK_FREQ/100000); 
		}
		inputsPins->at(1).port->ODR|= (1<<inputsPins->at(1).pin);
		osDelay(OS_TICK_FREQ/100000); 
		inputsPins->at(1).port->ODR&= ~(1<<inputsPins->at(1).pin);
	}
}


void defORTX5ControlDirClockSignalsDecorator::rotateBackwards(){	

		defOStepperMotorDriverDecorator::rotateBackwards();
		setStateOfPins();
		
}

void defORTX5ControlDirClockSignalsDecorator::rotateForward(){	

		defOStepperMotorDriverDecorator::rotateForward();
		setStateOfPins();	
}


