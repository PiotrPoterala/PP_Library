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
#ifndef _PP_CONTROL_COORDINATE_DECORATOR_H
	#define _PP_CONTROL_COORDINATE_DECORATOR_H

#include "pp_stepper_motor_driver_decorator.h"
#include <vector>

using namespace std;

class defOControlCoordinateDecorator : public defOStepperMotorDriverDecorator{
	
	#define DO_NOTHING_WITH_STEP			0
	#define ADD_STEP									1
	#define SUBTRACT_STEP							2
	
private:
		int correctionUM;
		int typeOfCorrection;

		defOParamGeneral* phyCoord;
		defOParamGeneral* baseCoord;
	
	public:
		defOControlCoordinateDecorator(defOStepperMotorDriver* stepMotorDriver, pair<char,defOParamGeneral*> pCoord, defOParamGeneral* bCoord, int corrUM=0);	
	
		virtual void rotateForward()override;
		virtual void rotateBackwards()override;

	
};


#endif
