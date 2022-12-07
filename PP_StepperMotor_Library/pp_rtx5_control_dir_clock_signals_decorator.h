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

#ifndef _RTX5_CONTROL_DIR_CLOCK_SIGNALS_DECORATOR_H
	#define _RTX5_CONTROL_DIR_CLOCK_SIGNALS_DECORATOR_H

#include "cmsis_os2.h"
#include "def_pins.h"

#include "pp_stepper_motor_driver_decorator.h"
#include <vector>

using namespace std;

#define FREQUENCY_OF_CLOCK_SIG	50000 //20us

class defORTX5ControlDirClockSignalsDecorator : public defOStepperMotorDriverDecorator{
	
	
	
	private:
		osTimerId_t offClockTimer;	
	
		void setStateOfPins();
	
		vector<uPin> *inputsPins;
	
	public:
		defORTX5ControlDirClockSignalsDecorator(defOStepperMotorDriverShdPtr stepMotorDriver, vector<uPin> *iPins, osTimerId_t poffClockTimer=nullptr);	
	
		defOStepperMotorDriverShdPtr clone()override{return make_shared<defORTX5ControlDirClockSignalsDecorator>(*this);};
	
		virtual void rotateForward() override;
		virtual void rotateBackwards()override;
	
	
};


#endif
