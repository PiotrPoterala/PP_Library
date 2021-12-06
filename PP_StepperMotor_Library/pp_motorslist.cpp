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

#include "pp_motorslist.h"


defOMotorsList::defOMotorsList(){
	
	
}

vector<defOStepperMotorDriver*>* defOMotorsList::getMotors(void){
	
	return &motors;
	
}

defOStepperMotorDriver* defOMotorsList::getMotor(char acronim){

	vector<defOStepperMotorDriver*>::iterator it=getIterator(acronim);
	
	if(it!=motors.end()) return (*it);
	
	return nullptr;
}

vector<defOStepperMotorDriver*>::iterator defOMotorsList::getIterator(){

	return motors.begin();
	
}


vector<defOStepperMotorDriver*>::iterator defOMotorsList::getIterator(char acronim){

	vector<defOStepperMotorDriver*>::iterator it;
	
	for(it=motors.begin(); it!=motors.end(); it++){
		if((*it)->getAcronim()==acronim) break;
		
	}
	
	return it;
}

void defOMotorsList::clearCounters(){

	vector<defOStepperMotorDriver*>::iterator it;
	
	for(it=motors.begin(); it!=motors.end(); ++it){
	//	(*it)->counter=0;
	}
	
}