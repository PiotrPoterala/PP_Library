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

DriveStatus defORTX5driveAlgorithms::drive(){

	int tick = osKernelGetTickCount(); 

	status=DriveStatus::DRIVE_IN_PROGRESS;
//	phyIndirectPoint.axes.clear();
//	phyIndirectPoint=phyEndPoint;


	while(status!=DriveStatus::DRIVE_COMPLETED && status!=DriveStatus::DRIVE_ABORTED){		

		tick += OS_TICK_FREQ /BASE_FREQUENCY_OF_TIMdrive;   
		
		for(auto it=phyStartPoint.axes.begin(); it != phyStartPoint.axes.end(); it++){
			
			if(motors->find((*it).first)!=motors->end()){
				auto cnt_it=counter.find((*it).first);
				if(cnt_it!=counter.end()){
					auto step=phyCoord->getParamPrecision((*it).first);
					auto actualPos=phyCoord->getParamValue((*it).first);
					if(cnt_it->second>=getClockDividerResponsibleForDriveSpeed(abs(actualPos-(*it).second)/step, 
																																		abs(phyEndPoint.axes.find((*it).first)->second-actualPos)/step, 
																																		motors->find((*it).first)->second->getAccelerationMMperSEC2Value(), 
																																		motors->find((*it).first)->second->getVelocityUMperSECValue(), 
																																		BASE_FREQUENCY_OF_TIMdrive, step*pow(10,6-phyCoord->getParamUnit((*it).first)))){
																												
																																			
						if(phyVector.axes.find((*it).first)->second>0){
							motors->find((*it).first)->second->rotateForward();
						}else if(phyVector.axes.find((*it).first)->second<0){
							motors->find((*it).first)->second->rotateBackwards();
						}
						(*cnt_it).second=1;
					}else{
						(*cnt_it).second++;
					}
				}
			}
			
		}

		if(phyEndPoint==phyCoord->getParamsValues())status=DriveStatus::DRIVE_COMPLETED;
		
		osDelayUntil(tick);
		
	}
	
	return status;

}

