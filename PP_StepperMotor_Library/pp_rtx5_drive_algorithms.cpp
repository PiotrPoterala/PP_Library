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

#include "pp_rtx5_drive_algorithms.h"
//#include "pp_iodevice.h"
#include "RTX_Config.h"

#include "pp_math.h"

DriveStatus defORTX5driveAlgorithms::drive(){

	int tick = osKernelGetTickCount(); 

	status=DriveStatus::DRIVE_IN_PROGRESS;
//	phyIndirectPoint.axes.clear();
//	phyIndirectPoint=phyEndPoint;


	while(status!=DriveStatus::DRIVE_COMPLETED && status!=DriveStatus::DRIVE_ABORTED){		

		tick += OS_TICK_FREQ /BASE_FREQUENCY_OF_TIMdrive;   
		
		for(auto it=phyStartPoint.axes.begin(); it != phyStartPoint.axes.end(); it++){

				auto motor=motors->find(it->first);
				auto indEndP=phyIndEndPoint.axes.find(it->first);
				auto cnt_it=counter.find(it->first);
				if(motor!=motors->end() && cnt_it!=counter.end() && indEndP!=phyIndEndPoint.axes.end()){
					auto phyCoordAux=motor->second->getPhyCoordClone();
					if(!phyCoordAux.empty()){
						int vector=indEndP->second-phyCoordAux.front()->getValue();
						if(vector!=0){
							auto velocityAux=motor->second->getVelocityXperSECClone();
							auto accelerateAux=motor->second->getAccelerationXperSEC2Clone();
							if(!velocityAux.empty() && !accelerateAux.empty()){
								
								if(cnt_it->second>=getClockDividerResponsibleForDriveSpeed(abs_pp(phyCoordAux.front()->getValue()-it->second)/phyCoordAux.front()->getPrecision(), 
																																					abs_pp(indEndP->second-phyCoordAux.front()->getValue())/phyCoordAux.front()->getPrecision(), 
																																					fs_mulBy10_pp(accelerateAux.front()->getValue(), phyCoordAux.front()->getUnit()-3-accelerateAux.front()->getUnit()),
																																					fs_mulBy10_pp(velocityAux.front()->getValue(), phyCoordAux.front()->getUnit()-3-velocityAux.front()->getUnit()), 
																																					BASE_FREQUENCY_OF_TIMdrive, phyCoordAux.front()->getPrecision())){
																															
																																						
									if(vector>0){
										motor->second->rotateForward();
									}else{
										motor->second->rotateBackwards();
									}
									(*cnt_it).second=1;
								}else{
									(*cnt_it).second++;
								}
							}
						}
					}
				}
			
			
		}

		if(pDrive.algorithm.params.phyIndEndPoint.comparePointWithValTab(&pDrive.algorithm.params.phyIndEndPoint.data, phyCoord.getParamValues(&phyCoord.data, tabToComp, MAX_NO_MOTORS), MAX_NO_MOTORS)){	//jezeli wszystkie silniki zrealizowaly swoje przejazdy do punktu spauzowania ruchu
				if(pDrive.algorithm.params.phyEndPoint.exacComparePoints(&pDrive.algorithm.params.phyEndPoint.data, &pDrive.algorithm.params.phyIndEndPoint.data)){	//jezeli wszystkie silniki zrealizowaly swoje przejazdy to ustaw flage kończącą przejazd
					status=DriveStatus::DRIVE_COMPLETED;	
				}else{
					status=DriveStatus::DRIVE_PAUSED;
				}
			}
		
		
		if(phyEndPoint==phyCoord->getParamsValues())status=DriveStatus::DRIVE_COMPLETED;
		
		osDelayUntil(tick);
		
	}
	
	return status;

}

