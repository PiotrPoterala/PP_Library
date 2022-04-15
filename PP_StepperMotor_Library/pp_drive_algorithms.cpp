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

 
defODriveAlgorithms::defODriveAlgorithms(defOMotorsListShdPtr mot, defOParamListShdPtr pCoord, defOParamListShdPtr bCoord):motors(mot), phyCoord(pCoord), baseCoord(bCoord){
	
	
}




//funkcje związane z przejazdami w pracy ręcznej
void defODriveAlgorithms::setParToDriveForValue(map<char, int> &values){

	phyStartPoint.axes.clear();
	phyEndPoint.axes.clear();
	phyVector.axes.clear();
	counter.clear();
	
	phyStartPoint=phyCoord->getParamsValues();
	phyEndPoint=phyStartPoint;
	
	
	for(auto it=phyStartPoint.axes.begin(); it != phyStartPoint.axes.end(); it++){
		if(motors->find((*it).first)!=motors->end()){
			auto values_it=values.find((*it).first);
			if(values_it!=values.end()){
				phyEndPoint.axes.find((*it).first)->second=phyCoord->getParam((*it).first).front()->correctData(phyEndPoint.axes.find((*it).first)->second+values_it->second);
			}
			phyVector.axes.insert(pair<char, int>((*it).first, phyEndPoint.axes.find((*it).first)->second-phyStartPoint.axes.find((*it).first)->second));
			counter.insert(pair<char, int>((*it).first, 0));
		}
	}
	
//	for(auto it=phyVector.axes.begin(); it != phyVector.axes.end(); it++){
//		printf("%s=%i, ", &((*it).first), (*it).second);
//		
//	}
//	printf("\r\n");
	drive();
	
														
}

void defODriveAlgorithms::setParToDriveToBaseCoordinates(map<char, int> &values){
	
	phyStartPoint.axes.clear();
	phyEndPoint.axes.clear();
	phyVector.axes.clear();
	counter.clear();
	
	phyStartPoint.axes=phyCoord->getParamsValues();
	phyEndPoint=phyStartPoint;
	
	for(auto it=phyStartPoint.axes.begin(); it != phyStartPoint.axes.end(); it++){
		if(motors->find((*it).first)!=motors->end()){
			auto values_it=values.find((*it).first);
			if(values_it!=values.end()){
				phyEndPoint.axes.find((*it).first)->second=phyCoord->getParam((*it).first).front()->correctData(phyEndPoint.axes.find((*it).first)->second+values_it->second-baseCoord->getParamValue((*it).first));
			}
			phyVector.axes.insert(pair<char, int>((*it).first, phyEndPoint.axes.find((*it).first)->second-phyStartPoint.axes.find((*it).first)->second));
			counter.insert(pair<char, int>((*it).first, 0));
		}
	}
	
	drive();
																			
}


unsigned int defODriveAlgorithms::getFrequencykResponsibleForDriveSpeed(unsigned int nrOfStepsFromStart, unsigned int nrOfStepsToEnd, int accelerationMMperSEC2, int velocityUMperSEC, unsigned int stepPM){
			int accelerateNumberOfSteps;
			int nrOfSteps=0;
			unsigned int frequencyOfDriveVelocity=0;

			//k - step

			//s=0.5*V*t	- pole pod wykresem V(t)
			//a=V/t	
			//s=V^2/(2*a)
			//Lk=s/k=V^2/(2*a*k)

			//V=s/t=k/(1/f) => V=kf => f=V/k => f=sqrt(2*a*Lk/k)

			accelerateNumberOfSteps=calculateAccelerateNumberOfSteps(accelerationMMperSEC2, velocityUMperSEC, stepPM);

			nrOfSteps=(nrOfStepsFromStart<=nrOfStepsToEnd)?nrOfStepsFromStart:nrOfStepsToEnd;
			if(nrOfSteps<=accelerateNumberOfSteps){
				frequencyOfDriveVelocity=sqrt(static_cast<double>(2*accelerationMMperSEC2*(nrOfSteps+1))/stepPM)*1000;
			}else{
				frequencyOfDriveVelocity=getFrequencyOfDriveInUniformMovement(velocityUMperSEC, stepPM);
			}
			
			return frequencyOfDriveVelocity;
}


unsigned int defODriveAlgorithms::getClockDividerResponsibleForDriveSpeed(unsigned int nrOfStepsFromStart, unsigned int nrOfStepsToEnd, int accelerationMMperSEC2, int velocityUMperSEC, unsigned int frequencyOfClock, unsigned int stepPM){

			//fmax/x=f
			//x=fmax/f=>x=fmax/sqrt(2*a*Lk/k)

			return frequencyOfClock/getFrequencykResponsibleForDriveSpeed(nrOfStepsFromStart, nrOfStepsToEnd, accelerationMMperSEC2, velocityUMperSEC, stepPM);
}

unsigned int defODriveAlgorithms::getFrequencyOfDriveInUniformMovement(int velocityUMperSEC, unsigned int stepPM){

		if(velocityUMperSEC<=0)velocityUMperSEC=1;
		
		return ((1000*velocityUMperSEC)/stepPM);	
}


unsigned int defODriveAlgorithms::getClockDividerInUniformMovement(int velocityUMperSEC, unsigned int frequencyOfClock, unsigned int stepPM){

		if(velocityUMperSEC<=0)velocityUMperSEC=1;
		
		return stepPM*frequencyOfClock/(1000*velocityUMperSEC);	
}


//unsigned int defODriveAlgorithms::getClockDividerInUniformMovementWithSecurity(int velocityUMperSEC, int defValue, unsigned int frequencyOfClock, unsigned int stepPM){

//		if(defValue<=0)defValue=1;
//		if(velocityUMperSEC<=0)velocityUMperSEC=defValue;
//		
//		return stepPM*frequencyOfClock/(1000*velocityUMperSEC);	
//}


unsigned int defODriveAlgorithms::calculateAccelerateNumberOfSteps(int accelerationMMperSEC2, int velocityUMperSEC, unsigned int stepPM){

		return (velocityUMperSEC*velocityUMperSEC/(2*accelerationMMperSEC2*stepPM));
}

