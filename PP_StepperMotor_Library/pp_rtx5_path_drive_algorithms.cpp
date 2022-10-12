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

#include "pp_rtx5_path_drive_algorithms.h"
//#include "pp_iodevice.h"
#include "RTX_Config.h"

#include "pp_math.h"

DriveStatus defORTX5pathDriveAlgorithms::drive(){

	int tick = osKernelGetTickCount(); 

	while(status!=DriveStatus::DRIVE_COMPLETED && status!=DriveStatus::DRIVE_ABORTED){		

	
		auto masterPhyCoordAux=motorsList->getPhyCoordClone(masterAxis);
			
			//jeżeli oś wiodąca dojechała do swojej pozycji, to wszystkimi osiami najkrótszą drogą podążamy do punktu docelowego
		if(!masterPhyCoordAux.empty()){
			if(masterPhyCoordAux.front()->getPrecision()>0){
				PPpoint<int> phyVector{};
				
				for(auto it:phyStartPoint.axes){
					auto endAx=phyEndPoint.axes.find(it.first);
					if(endAx!=phyEndPoint.axes.end()){
						phyVector.axes.insert(PPointIntPair(it.first, endAx->second-it.second));
					}
				}
				
				
				auto startPmasterAx=phyStartPoint.axes.find(masterAxis);
				auto endPmasterAx=phyEndPoint.axes.find(masterAxis);
				auto nextStepPmasterAx=phyNextStepPoint.axes.find(masterAxis);
				auto vectorMasterAx=phyVector.axes.find(masterAxis);
				
				
				double nPt=(vectorMasterAx->second>0)?nextStepPmasterAx->second+masterPhyCoordAux.front()->getPrecision():nextStepPmasterAx->second-masterPhyCoordAux.front()->getPrecision();		//obliczenie wartości współrzędnych dla kolejnych punktów trajektorii na podstawie wzorów opisujących prostą w przestrzeni
				if(abs_pp((int)nPt-startPmasterAx->second)<=abs_pp(vectorMasterAx->second)){ //jeżeli jesteśmy w zakresie ruchu to oblicz kolejny punkt trajektorii

					auto velocityAux=motorsList->getVelocityXperSECClone(masterAxis);
					auto accelerateAux=motorsList->getAccelerationXperSEC2Clone(masterAxis);

					
					tick += (OS_TICK_FREQ /BASE_FREQUENCY_OF_TIMdrive)*getClockDividerResponsibleForDriveSpeed(abs_pp(nPt-startPmasterAx->second)/masterPhyCoordAux.front()->getPrecision(), 
																												abs_pp(nPt-endPmasterAx->second)/masterPhyCoordAux.front()->getPrecision(), 
																												fs_mulBy10_pp(accelerateAux.front()->getValue(), masterPhyCoordAux.front()->getUnit()-3-accelerateAux.front()->getUnit()),
																												fs_mulBy10_pp(velocityAux.front()->getValue(), masterPhyCoordAux.front()->getUnit()-3-velocityAux.front()->getUnit()), 
																												BASE_FREQUENCY_OF_TIMdrive, masterPhyCoordAux.front()->getPrecision());
														
																					
					double t=(nPt-startPmasterAx->second)/vectorMasterAx->second;	
												

					for(auto vector:phyVector.axes){
						auto auxMotor=motorsList->motors.find(vector.first);
						if(auxMotor!=motorsList->motors.end()){
							auto phyCoordAux=auxMotor->second->getPhyCoordClone();
							double nextStepValue=0;

							if(vector.first==masterAxis){
								nextStepValue=nPt;
							}else{		
								auto startP=phyStartPoint.axes.find(vector.first);
								
								nextStepValue=t*(vector.second)+startP->second;
							}
							phyNextStepPoint.setAxValue(vector.first, nextStepValue);
							
							double halfStep=((double)phyCoordAux.front()->getPrecision())/2; 
							
							if((double)(phyCoordAux.front()->getValue())+halfStep<nextStepValue)auxMotor->second->rotateForward();
							else if((double)(phyCoordAux.front()->getValue())-halfStep>nextStepValue)auxMotor->second->rotateBackwards();	
						}	
					}	
																						
				}else{
					for(auto mot:motorsList->motors){
						auto phyCoordAux=mot.second->getPhyCoordClone();
						auto endP=phyEndPoint.axes.find(mot.first);

						if(!phyCoordAux.empty() && endP!=phyEndPoint.axes.end()){
							int vectorAx=endP->second-phyCoordAux.front()->getValue();

							if(vectorAx>0)mot.second->rotateForward();
							else if(vectorAx<0)mot.second->rotateBackwards();	
						}	
						
					}
				}
			}
		}
	
			map<char, int> phyCoordValues=motorsList->getPhyCoordValues();
		
			if(phyIndEndPoint.compare(phyCoordValues)){	//jezeli wszystkie silniki zrealizowaly swoje przejazdy do punktu spauzowania ruchu
					if(phyEndPoint==phyIndEndPoint){	//jezeli wszystkie silniki zrealizowaly swoje przejazdy to ustaw flage kończącą przejazd
						status=DriveStatus::DRIVE_COMPLETED;	
					}else{
						status=DriveStatus::DRIVE_PAUSED;
					}
				}
			

			
			osDelayUntil(tick);
		
	}
	
	return status;

}

