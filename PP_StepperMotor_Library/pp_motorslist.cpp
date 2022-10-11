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

PMotorsList::PMotorsList(const PMotorsList &other){
	
		copyListOfMotors(other.motors);
	
}

PMotorsList::PMotorsList(const PMotorsMap& map){

    copyListOfMotors(map);

}

PMotorsList& PMotorsList::operator=(const PMotorsList& other){
		
	copyListOfMotors(other.motors);
	return (*this);
}

PMotorsList::~PMotorsList(){
	
	clear();
	
}

void PMotorsList::clear(){
	
		 if(motors.empty()==false){
       motors.clear();
    }	
}

void PMotorsList::copyListOfMotors(const PMotorsMap &copyMotors){

    clear();
		for (auto it=copyMotors.begin(); it != copyMotors.end(); ++it){
			motors.insert(PMotorsPair((*it).first, (*it).second->clone()));
		}
		
}

map<char, int> PMotorsList::getPhyCoordValues(){
	map<char, int> values;
	
	for(auto it=motors.begin(); it != motors.end(); ++it){
		auto phyCoordAux=it->second->getPhyCoordClone();
		values.insert(pair<char,int>(it->first, phyCoordAux.front()->getValue()));
		
	}
	
	return values;
	
}

map<char, int> PMotorsList::getBaseCoordValues(){
	map<char, int> values;
	
	for(auto it=motors.begin(); it != motors.end(); ++it){
		auto baseCoordAux=it->second->getBaseCoordClone();
		values.insert(pair<char,int>(it->first, baseCoordAux.front()->getValue()));
		
	}
	
	return values;
	
}
	