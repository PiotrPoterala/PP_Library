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

 
defODriveAlgorithms::defODriveAlgorithms(PMotorsListShdPtr mot):motorsList(mot){
	
	
}


//funkcje związane z przejazdami w pracy ręcznej
void defODriveAlgorithms::driveToEndPoint(PPpoint<int> &endP, PPpoint<int> &startP){

	phyStartPoint.clear();
	phyEndPoint.clear();
	counter.clear();
	
	for(auto it:endP.rGetAxes()){
		auto startAx=startP.rGetAxes().find(it.first);
		if(startAx!=startP.rGetAxes().end()){
			if(it.second!=startAx->second){
				phyStartPoint.addAx(*startAx);
				phyEndPoint.addAx(it);
				counter.insert(pair<char, int>(it.first, 0));
			}
		}
	}
	
//	for(auto it=phyVector.axes.begin(); it != phyVector.axes.end(); it++){
//		printf("%s=%i, ", &((*it).first), (*it).second);
//		
//	}
//	printf("\r\n");
	if(phyEndPoint.rGetAxes().size()>0){
		phyIndEndPoint=phyEndPoint;
		phyNextStepPoint=phyStartPoint;
		calculateMasterAxis();

		status=DriveStatus::DRIVE_IN_PROGRESS;
		drive();
	}
														
}

void defODriveAlgorithms::driveForValue(map<char, int> &values){
	PPpoint<int> val=values;
	driveForValue(val);
	
}

void defODriveAlgorithms::driveForValue(PPpoint<int> &values){
	
	PPpoint<int> startP=motorsList->getPhyCoordValues();
	PPpoint<int> endP=startP;
	endP+=values;
	
	driveToEndPoint(endP, startP);
}

void defODriveAlgorithms::driveToBaseCoordinates(map<char, int> &values){
		PPpoint<int> val=values;
		driveToBaseCoordinates(val);
}

void defODriveAlgorithms::driveToBaseCoordinates(PPpoint<int> &values){
	
	PPpoint<int> startP=motorsList->getPhyCoordValues();
	PPpoint<int> endP=startP;
	endP+=values;
	endP-=motorsList->getBaseCoordValues();
	
	driveToEndPoint(endP, startP);
}

void defODriveAlgorithms::driveToPhyCoordinates(PPpoint<int> &values){
	
	PPpoint<int> startP=motorsList->getPhyCoordValues();
	
	driveToEndPoint(values, startP);
}

char defODriveAlgorithms::calculateMasterAxis(){
			char master=0;
			int maxSteps=0;
	
			auto vector=phyEndPoint;
			vector-=phyStartPoint;
	
			for(auto motor:motorsList->motors){
				auto phyCoordAux=motorsList->getPhyCoordClone(motor.first);
				int steps=abs(vector.getAxValue(motor.first))/phyCoordAux.front()->getPrecision();
				
				if(steps>maxSteps){
					maxSteps=steps;
					master=motor.first;
				}
			}
	
	
			return master;
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

