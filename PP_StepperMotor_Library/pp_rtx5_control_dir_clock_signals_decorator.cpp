/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Piotr Poterała, 2021
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */

#include "pp_rtx5_control_dir_clock_signals_decorator.h"
 #include "RTX_Config.h"
 #include "def_pins.h"



defORTX5ControlDirClockSignalsDecorator::defORTX5ControlDirClockSignalsDecorator(defOStepperMotorDriver* stepMotorDriver, vector<uPin> *iPins, osTimerId_t poffClockTimer):
																																		defOStepperMotorDriverDecorator(stepMotorDriver), inputsPins(iPins), offClockTimer(poffClockTimer){	


																																			
}
																																		

void defORTX5ControlDirClockSignalsDecorator::setStateOfPins(){	
		int dirMask, dirClrMask;
	
	
	if(inputsPins->size()==2){
		dirMask=(defOStepperMotorDriverDecorator::getSignalMask() & 0x1)<< inputsPins->at(0).pin;
		dirClrMask=(1<<inputsPins->at(0).pin);
	
		if((inputsPins->at(0).port->ODR & dirClrMask)!=dirMask){
			inputsPins->at(0).port->ODR=(inputsPins->at(0).port->ODR & ~dirClrMask) | dirMask;	
			osDelay(OS_TICK_FREQ/FREQUENCY_OF_CLOCK_SIG); 
		}
		if(offClockTimer!=nullptr){
			osTimerStart(offClockTimer, OS_TICK_FREQ/FREQUENCY_OF_CLOCK_SIG);
			PIN_SET(inputsPins->at(1).port, (1<<inputsPins->at(1).pin));
		}else{
			PIN_SET(inputsPins->at(1).port, (1<<inputsPins->at(1).pin));
			osDelay(OS_TICK_FREQ/FREQUENCY_OF_CLOCK_SIG); 
			PIN_CLR(inputsPins->at(1).port, (1<<inputsPins->at(1).pin));
		}
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


