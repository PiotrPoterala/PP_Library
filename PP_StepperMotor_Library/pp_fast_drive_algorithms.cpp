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

#include "pp_fast_drive_algorithms.h"

#include "pp_math.h"



DriveStatus defOFastDriveAlgorithms::makeStep(void){
			DriveStatus ans=DriveStatus::DRIVE_IN_PROGRESS;
			for(auto it:phyStartPoint.rGetAxes()){

				auto motor=motorsList->motors.find(it.first);
				auto indEndP=phyIndEndPoint.getAx(it.first);
				if(motor!=motorsList->motors.end() && !indEndP.empty()){
					auto phyCoordAux=motor->second->getPhyCoordClone();
					if(!phyCoordAux.empty()){
						int vector=indEndP.front()-phyCoordAux.front()->getValue();
						if(vector!=0){
							auto velocityAux=motor->second->getVelocityXperSECClone();
							auto accelerateAux=motor->second->getAccelerationXperSEC2Clone();
							if(!velocityAux.empty() && !accelerateAux.empty()){																												
									if(vector>0){
										motor->second->rotateForward();
									}else{
										motor->second->rotateBackwards();
									}
								}
							}
						}
					}
				}

		auto phyCoordValues=motorsList->getPhyCoordValues();
		
		if(phyIndEndPoint.compare(phyCoordValues)){	//jezeli wszystkie silniki zrealizowaly swoje przejazdy do punktu spauzowania ruchu
				if(phyEndPoint==phyIndEndPoint){	//jezeli wszystkie silniki zrealizowaly swoje przejazdy to ustaw flage kończącą przejazd
					ans=DriveStatus::DRIVE_COMPLETED;	
				}else{
					ans=DriveStatus::DRIVE_PAUSED;
				}
			}
	
	
	return ans;
	
}


DriveStatus defOFastDriveAlgorithms::drive(){


	while(status!=DriveStatus::DRIVE_COMPLETED && status!=DriveStatus::DRIVE_ABORTED){		

			status=makeStep();
				
	}
	
	return status;

}

