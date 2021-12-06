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
#ifndef PP_MOTOR_LIST_H
#define PP_MOTOR_LIST_H

#include "stm32xx.h"
#include <vector>
#include "pp_stepper_motor_driver.h"

using namespace std;

class defOMotorsList
{

private:
    vector<defOStepperMotorDriver*> motors;

public:
    defOMotorsList();

		vector<defOStepperMotorDriver*>* getMotors(void);
    defOStepperMotorDriver* getMotor(char acronim);
		vector<defOStepperMotorDriver*>::iterator getIterator();
		vector<defOStepperMotorDriver*>::iterator getIterator(char acronim);
		void clearCounters();

};

#endif 