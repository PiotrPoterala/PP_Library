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

#include "pp_stepper_motor_2clock_driver.h"

defOStepperMotor2clockDriver::defOStepperMotor2clockDriver(defOParamGeneralShdPtr paccelerationMMperSEC2, defOParamGeneralShdPtr pvelocityUMperSEC,
																													defOParamGeneralShdPtr pphyCoord, defOParamGeneralShdPtr pbaseCoord, int tOfStep):
																													defOStepperMotorDriverPar(paccelerationMMperSEC2, pvelocityUMperSEC, pphyCoord, pbaseCoord){
	
	
	setTypeOfStep(tOfStep);
	
}

void defOStepperMotor2clockDriver::setTypeOfStep(int tOfStep){
	
	typeOfStep=tOfStep;
	
	switch(typeOfStep){
		case FULL_STEP:
			maskStep=&maskFullStep;
			break;
		case HALF_STEP:
			maskStep=&maskHalfStep;
			break;
		case MICRO_STEP:
			maskStep=&maskMicroStep;
			break;
	}
	maskIter=maskStep->begin();
}



//ustawienie maski powodującej obrót silnika o jeden krok do tylu
void defOStepperMotor2clockDriver::rotateBackwards(){	

		if(maskIter==maskStep->begin())maskIter=maskStep->end()-1;
		else maskIter--;
				
}

void defOStepperMotor2clockDriver::rotateForward(){	

			maskIter++;
			if(maskIter==maskStep->end())maskIter=maskStep->begin();
}

