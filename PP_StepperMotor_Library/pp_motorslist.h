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
#include <vector>
#include "pp_stepper_motor_driver.h"

using PMotorsMap = map<char, defOStepperMotorDriverShdPtr>;
using PMotorsPair = pair<char, defOStepperMotorDriverShdPtr>;

//using PMotorsVector = vector<defOStepperMotorDriverShdPtr>;
//using PMotorsVectorItr=vector<defOStepperMotorDriverShdPtr>::iterator; 
//using PMotorsData = vector<defOStepperMotorDriverShdPtr>;

using namespace std;

class PMotorsList
{

private:
	
		void copyListOfMotors(const PMotorsMap &copyMotors);

public:
		PMotorsMap motors;

    PMotorsList();
		PMotorsList(const PMotorsList& list);
		PMotorsList(const PMotorsMap& map);
		PMotorsList& operator=(const PMotorsList& other);
		~PMotorsList();

		void clear(void);
		shared_ptr<PMotorsList> clone() const;

		map<char, int> getPhyCoordValues();
		map<char, int> getBaseCoordValues();


};

using PMotorsListShdPtr = shared_ptr<PMotorsList>;
#endif 