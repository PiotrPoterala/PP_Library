/**
 * @author  Piotr Poterała
 * @email   poterala.piotr@gmail.com
 * @website http://zappp.pl
 * @version v1.0
 * @ide     Keil uVision 5
 * @license GNU GPL v3
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Piotr Poterała, 2021
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */
#ifndef _RTX5_SELECT_CURRENT_DECORATOR_H
	#define _RTX5_SELECT_CURRENT_DECORATOR_H

#include "def_pins.h"
#include "cmsis_os2.h"
 #include "RTX_Config.h"
#include "pp_stepper_motor_driver_decorator.h"
using namespace std;

class defORTX5SelectCurrentDecorator : public defOStepperMotorDriverDecorator{
	
	
	
	private:
		osTimerId_t offClockTimer;	
	
		uPin *selectPin;
		int selPolar;
	
		int ticksToOff;
	
	public:
		defORTX5SelectCurrentDecorator(defOStepperMotorDriverShdPtr stepMotorDriver, uPin *sPin, osTimerId_t poffClockTimer, int sPolar=B_LOW, int ptimeToOff_MS=10000):
																	defOStepperMotorDriverDecorator(stepMotorDriver), selectPin(sPin),offClockTimer(poffClockTimer), selPolar(sPolar){
																	
																	ticksToOff=ptimeToOff_MS*OS_TICK_FREQ/1000;
																	};	
	
		defOStepperMotorDriverShdPtr clone()override{return make_shared<defORTX5SelectCurrentDecorator>(*this);};
																	
		virtual void rotateForward()override{
			defOStepperMotorDriverDecorator::rotateForward();
			osTimerStart(offClockTimer, ticksToOff);
			if(selPolar==B_LOW)PIN_SET(selectPin->port, (1<<selectPin->pin));
			else PIN_CLR(selectPin->port, (1<<selectPin->pin));
			
		};
		
		virtual void rotateBackwards()override{
			defOStepperMotorDriverDecorator::rotateBackwards();
			osTimerStart(offClockTimer, ticksToOff);
			if(selPolar==B_LOW)PIN_SET(selectPin->port, (1<<selectPin->pin));
			else PIN_CLR(selectPin->port, (1<<selectPin->pin));
			
		}
	
};


#endif
