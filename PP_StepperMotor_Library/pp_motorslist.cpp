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
#include <vector>

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
		for (auto&& it:copyMotors){
			motors.insert(PMotorsPair(it.first, it.second->clone()));
		}
		
}

map<char, int> PMotorsList::getPhyCoordValues(){
	map<char, int> values;
	
	for(auto&& it:motors){
		auto phyCoordAux=it.second->getPhyCoordClone();
		values.insert(pair<char,int>(it.first, phyCoordAux.front()->getValue()));
		
	}
	
	return values;
	
}

map<char, int> PMotorsList::getBaseCoordValues(){
	map<char, int> values;
	
	for(auto&& it:motors){
		auto baseCoordAux=it.second->getBaseCoordClone();
		values.insert(pair<char,int>(it.first, baseCoordAux.front()->getValue()));
		
	}
	
	return values;
	
}
	
PParamMap PMotorsList::getPhyCoordClone(){
	PParamMap coordList;
			
	for(auto&& it:motors){
		auto phyCoordAux=it.second->getPhyCoordClone();
		if(phyCoordAux.size()>0){
			coordList.insert(PParamPair(it.first, phyCoordAux.front()));
		}
		
	}	
	return coordList;
}


PParamMap PMotorsList::getBaseCoordClone(){
	PParamMap coordList;
			
	for(auto&& it:motors){
		auto phyCoordAux=it.second->getBaseCoordClone();
		if(phyCoordAux.size()>0){
			coordList.insert(PParamPair(it.first, phyCoordAux.front()));
		}
		
	}	
	return coordList;
}


PParamData PMotorsList::getPhyCoordClone(char acronim){
	PParamData data;
	
	auto motor=motors.find(acronim);
	if(motor!=motors.end())data=motor->second->getPhyCoordClone();
	
	return data;
}
		
PParamData PMotorsList::getBaseCoordClone(char acronim){
	PParamData data;
	
	auto motor=motors.find(acronim);
	if(motor!=motors.end())data=motor->second->getBaseCoordClone();
	
	return data;
	
}


PParamData PMotorsList::getAccelerationXperSEC2Clone(char acronim){
	PParamData data;
	
	auto motor=motors.find(acronim);
	if(motor!=motors.end())data=motor->second->getAccelerationXperSEC2Clone();
	
	return data;
}
	
PParamData PMotorsList::getVelocityXperSECClone(char acronim){
	PParamData data;
	
	auto motor=motors.find(acronim);
	if(motor!=motors.end())data=motor->second->getVelocityXperSECClone();
	
	return data;
}