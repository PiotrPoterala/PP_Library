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

#include "pp_drive_algorithms.h"

 
defODriveAlgorithms::defODriveAlgorithms(defOMotorsListShdPtr mot):motors(mot){
	
	
}


//funkcje związane z przejazdami w pracy ręcznej
void defODriveAlgorithms::driveToEndPoint(map<char, int> &endPoint){

	phyStartPoint.axes.clear();
	phyEndPoint.axes.clear();
//	phyVector.axes.clear();
	counter.clear();
	
//	phyStartPoint=phyCoord->getParamsValues();
//	phyEndPoint=phyStartPoint;
	
	
	for(auto it=motors->begin(); it != motors->end(); it++){
		
		if(endPoint.find(it->first)!=endPoint.end()){
			auto phyCoordAux=it->second->getPhyCoordClone();

			if(!phyCoordAux.empty()){
				auto startP=PPointIntPair(it->first, phyCoordAux.front()->getValue());
				auto endP=endPoint.find(it->first);
				
				endP->second-=endP->second%phyCoordAux.front()->getPrecision();

				if(endP->second!=startP.second){
					phyStartPoint.axes.insert(startP);
					phyEndPoint.axes.insert(*endP);
					counter.insert(pair<char, int>(it->first, 0));
				}
			}
		}
	}
	
//	for(auto it=phyVector.axes.begin(); it != phyVector.axes.end(); it++){
//		printf("%s=%i, ", &((*it).first), (*it).second);
//		
//	}
//	printf("\r\n");
	if(phyEndPoint.axes.size()>0){
		phyIndEndPoint=phyEndPoint;
		drive();
	}
														
}

//void defODriveAlgorithms::setParToDriveToBaseCoordinates(map<char, int> &values){
//	
//	phyStartPoint.axes.clear();
//	phyEndPoint.axes.clear();
//	phyVector.axes.clear();
//	counter.clear();
//	
//	phyStartPoint.axes=phyCoord->getParamsValues();
//	phyEndPoint=phyStartPoint;
//	
//	for(auto it=phyStartPoint.axes.begin(); it != phyStartPoint.axes.end(); it++){
//		if(motors->find((*it).first)!=motors->end()){
//			auto values_it=values.find((*it).first);
//			if(values_it!=values.end()){
//				phyEndPoint.axes.find((*it).first)->second=phyCoord->getParam((*it).first).front()->correctData(phyEndPoint.axes.find((*it).first)->second+values_it->second-baseCoord->getParamValue((*it).first));
//			}
//			phyVector.axes.insert(pair<char, int>((*it).first, phyEndPoint.axes.find((*it).first)->second-phyStartPoint.axes.find((*it).first)->second));
//			counter.insert(pair<char, int>((*it).first, 0));
//		}
//	}
//	
//	drive();
//																			
//}


unsigned int defODriveAlgorithms::getFrequencykResponsibleForDriveSpeed(unsigned int nrOfStepsFromStart, unsigned int nrOfStepsToEnd, unsigned int accelerationXperSEC2, unsigned int velocityXperSEC, unsigned int stepMX){
			unsigned int accelerateNumberOfSteps;
			unsigned int nrOfSteps=0;
			unsigned int frequencyOfDriveVelocity=0;

			//k - step

			//s=0.5*V*t	- pole pod wykresem V(t)
			//a=V/t	
			//s=V^2/(2*a)
			//Lk=s/k=V^2/(2*a*k)

			//V=s/t=k/(1/f) => V=kf => f=V/k => f=sqrt(2*a*Lk/k)

			accelerateNumberOfSteps=calculateAccelerateNumberOfSteps(accelerationXperSEC2, velocityXperSEC, stepMX);

			nrOfSteps=(nrOfStepsFromStart<=nrOfStepsToEnd)?nrOfStepsFromStart:nrOfStepsToEnd;
			if(nrOfSteps<=accelerateNumberOfSteps){
				if(stepMX!=0 && accelerationXperSEC2!=0){
					unsigned int freq=(2*1000*accelerationXperSEC2)/stepMX;
					freq*=(nrOfSteps+1);
					frequencyOfDriveVelocity=sqrt(freq);
				}else{
					frequencyOfDriveVelocity=1;
				}
			}else{
				frequencyOfDriveVelocity=getFrequencyOfDriveInUniformMovement(velocityXperSEC, stepMX);
			}
			

			if(frequencyOfDriveVelocity>80 && frequencyOfDriveVelocity<240){	//wycięcie 100 [Hz]
				frequencyOfDriveVelocity=240;
			}else if(frequencyOfDriveVelocity<60){	//wycięcie 50 [Hz]
				frequencyOfDriveVelocity=60;
			}
			
			
			return frequencyOfDriveVelocity;
}


unsigned int defODriveAlgorithms::getClockDividerResponsibleForDriveSpeed(unsigned int nrOfStepsFromStart, unsigned int nrOfStepsToEnd, unsigned int accelerationXperSEC2, unsigned int velocityXperSEC, unsigned int frequencyOfClock, unsigned int stepMX){

			//fmax/x=f
			//x=fmax/f=>x=fmax/sqrt(2*a*Lk/k)

			unsigned int freq=getFrequencykResponsibleForDriveSpeed(nrOfStepsFromStart, nrOfStepsToEnd, accelerationXperSEC2, velocityXperSEC, stepMX);
	
			if(freq==0)freq=1;
			else if(freq>frequencyOfClock)freq=frequencyOfClock;
			
	
			return frequencyOfClock/freq;
}

unsigned int defODriveAlgorithms::getFrequencyOfDriveInUniformMovement(unsigned int velocityXperSEC, unsigned int stepMX){
		unsigned int freq=1;
		if(stepMX!=0)freq=1000*velocityXperSEC/stepMX;
		
		return freq;	
}


unsigned int defODriveAlgorithms::getClockDividerInUniformMovement(unsigned int velocityXperSEC, unsigned int frequencyOfClock, unsigned int stepMX){

			unsigned int freq=getFrequencyOfDriveInUniformMovement(velocityXperSEC, stepMX);
	
			if(freq==0)freq=1;
			else if(freq>frequencyOfClock)freq=frequencyOfClock;
	
			return frequencyOfClock/freq;
}




unsigned int defODriveAlgorithms::calculateAccelerateNumberOfSteps(unsigned int accelerationXperSEC2, unsigned int velocityXperSEC, unsigned int stepMX){
		unsigned int noOfSteps=0;
		if(accelerationXperSEC2!=0 && stepMX!=0){
					
			noOfSteps=velocityXperSEC*velocityXperSEC/accelerationXperSEC2;
			noOfSteps*=1000;
			noOfSteps/=(2*stepMX);
			
		}
			
	
		return noOfSteps;
}

