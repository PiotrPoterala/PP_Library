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
		vector<int> maskMicroStep={0x3D,0x39,0x75,0xB1,0xED,0x129,0x165,0x1A1,
															0x1DD,0x219,0x255,0x291,0x2CD,0x309,0x345,0x381,
															0x3C3,0x383,0x347,0x30B,0x2CF,0x293,0x257,0x21B,
															0x1DF,0x1A3,0x167,0x12B,0xEF,0xB3,0x77,0x3B,
			
															0x3E,0x3A,0x76,0xB2,0xEE,0x12A,0x166,0x1A2,
															0x1DE,0x21A,0x256,0x292,0x2CE,0x30A,0x346,0x382,
															0x3C0,0x380,0x344,0x308,0x2CC,0x290,0x254,0x218,
															0x1DC,0x1A0,0x164,0x128,0xEC,0xB0,0x74,0x38};
	
	public:
		defOStepperMotor2clockDriver(defOParam* paccelerationMMperSEC2, defOParam* pvelocityUMperSEC, int tOfStep=FULL_STEP);	
	
		void setTypeOfStep(int tOfStep);
	
		virtual void rotateForward()override;
		virtual void rotateBackwards()override;
		
		virtual int getSignalMask()override{return *maskIter;};
	
};


#endif
