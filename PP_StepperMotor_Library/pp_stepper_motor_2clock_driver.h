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
#ifndef _PP_STEPPER_MOTOR_2CLOCK_DRIVER_H
	#define _PP_STEPPER_MOTOR_2CLOCK_DRIVER_H

#include "pp_stepper_motor_driver.h"
#include <vector>

using namespace std;

class defOStepperMotor2clockDriver : public defOStepperMotorDriverPar{
	
	#define FULL_STEP		0
	#define HALF_STEP		1
	#define MICRO_STEP	2
	
	private:

		int typeOfStep;	
		vector<int>::iterator maskIter;
		vector<int>* maskStep;
		vector<int> maskFullStep={0x1,0x3,0x2,0x0};
		vector<int> maskHalfStep={0x3C,0x1DD,0x3C1,0x1DF,0x3F,0x1DE,0x3C2,0x1DC};
		vector<int> maskMicroStep={0x3D,0x39,0x75,0xB1,0xED,0x129};
	
	public:
		defOStepperMotor2clockDriver(defOParam* paccelerationMMperSEC2, defOParam* pvelocityUMperSEC, int tOfStep=FULL_STEP);	
	
		void setTypeOfStep(int tOfStep);
	
		virtual void rotateForward()override;
		virtual void rotateBackwards()override;
		
		virtual int getSignalMask()override{return *maskIter;};
	
};


#endif
