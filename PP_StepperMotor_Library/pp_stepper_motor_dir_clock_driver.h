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
#ifndef _MOTOR_PARALLEL_DRIVER_H
	#define _MOTOR_PARALLEL_DRIVER_H

#include "pp_stepper_motor_driver.h"

using namespace std;

class defOStepperMotorDirClockDriver : public defOStepperMotorDriverPar{
	
	private:
		int maskStep;
	
	public:
		defOStepperMotorDirClockDriver(defOParamGeneralShdPtr paccelerationMMperSEC2, defOParamGeneralShdPtr pvelocityUMperSECdefOParamGeneralShdPtr pphyCoord, defOParamGeneralShdPtr pbaseCoord, ):
																	defOStepperMotorDriverPar(paccelerationMMperSEC2, pvelocityUMperSEC, pphyCoord, pbaseCoord){};	
	
		virtual void rotateForward()override{maskStep=0;};
		virtual void rotateBackwards()override{maskStep=1;};
		virtual int getSignalMask()override{return maskStep;};

		virtual defOStepperMotorDriverShdPtr undecorate()override{return make_shared<defOStepperMotorDirClockDriver>(*this);};
};


#endif
