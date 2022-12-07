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

	
			status=makeStep();
				
			auto masterPhyCoordAux=motorsList->getPhyCoordClone(masterAxis);
			auto startPmasterAx=phyStartPoint.getAx(masterAxis);
			auto endPmasterAx=phyEndPoint.getAx(masterAxis);
			auto nextStepPmasterAx=phyNextStepPoint.getAx(masterAxis);
			
			auto velocityAux=motorsList->getVelocityXperSECClone(masterAxis);
			auto accelerateAux=motorsList->getAccelerationXperSEC2Clone(masterAxis);

				
			tick += (OS_TICK_FREQ /BASE_FREQUENCY_OF_TIMdrive)*getClockDividerResponsibleForDriveSpeed(abs_pp(nextStepPmasterAx.front()-startPmasterAx.front())/masterPhyCoordAux.front()->getPrecision(), 
																											abs_pp(nextStepPmasterAx.front()-endPmasterAx.front())/masterPhyCoordAux.front()->getPrecision(), 
																											fs_mulBy10_pp(accelerateAux.front()->getValue(), masterPhyCoordAux.front()->getUnit()-3-accelerateAux.front()->getUnit()),
																											fs_mulBy10_pp(velocityAux.front()->getValue(), masterPhyCoordAux.front()->getUnit()-3-velocityAux.front()->getUnit()), 
																											BASE_FREQUENCY_OF_TIMdrive, masterPhyCoordAux.front()->getPrecision());
														

			
			osDelayUntil(tick);
		
	}
	
	return status;

}

