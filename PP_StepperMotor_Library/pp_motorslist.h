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

#include <map>
#include "pp_stepper_motor_driver.h"

using PMotorsList = map<char, defOStepperMotorDriverShdPtr>;
using PMotorsPair = pair<char, defOStepperMotorDriverShdPtr>;

//using PMotorsVector = vector<defOStepperMotorDriverShdPtr>;
//using PMotorsVectorItr=vector<defOStepperMotorDriverShdPtr>::iterator; 
//using PMotorsData = vector<defOStepperMotorDriverShdPtr>;

//using namespace std;

//class defOMotorsList
//{

//private:
//   PMotorsVector motors;

//public:
//    defOMotorsList();
//		defOMotorsList(const defOMotorsList& list)=delete;
//		defOMotorsList& operator=(const defOMotorsList& list)=delete;

//		PMotorsVector getMotors(void);
//    PMotorsData getMotor(char acronim);

//		void insert(defOStepperMotorDriverShdPtr motor);

//		PMotorsVectorItr getIterator();
//		PMotorsVectorItr getIterator(char acronim);

//};

using defOMotorsListShdPtr = shared_ptr<PMotorsList>;
#endif 