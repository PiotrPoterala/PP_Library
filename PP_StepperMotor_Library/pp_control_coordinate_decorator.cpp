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

#include "pp_control_coordinate_decorator.h"

defOControlCoordinateDecorator::defOControlCoordinateDecorator(defOStepperMotorDriverShdPtr stepMotorDriver, PParamPair pCoord, defOParamGeneralShdPtr bCoord, int corrUM):
																															defOStepperMotorDriverDecorator(stepMotorDriver), baseCoord(bCoord){
																						
		defOStepperMotorDriverDecorator::setAcronim(pCoord.first);																							
																																
		phyCoord=pCoord.second;																																
																																
	if(corrUM>0){
		correctionUM=corrUM;
		typeOfCorrection=ADD_STEP;
	}else if(corrUM<0){
		correctionUM=abs(corrUM);
		typeOfCorrection=SUBTRACT_STEP;
	}else{
		correctionUM=0;
		typeOfCorrection=DO_NOTHING_WITH_STEP;
	}																									
																																
}




void defOControlCoordinateDecorator::rotateBackwards(){	

		if(typeOfCorrection==SUBTRACT_STEP && !(phyCoord->getValue()%static_cast<int>(pow(10, phyCoord->getUnit()-3)*correctionUM))){
			phyCoord->decrementValue();
			baseCoord->decrementValue();
		}else{
			defOStepperMotorDriverDecorator::rotateBackwards();
	
			if(typeOfCorrection!=ADD_STEP || (phyCoord->getValue()%static_cast<int>(pow(10, phyCoord->getUnit()-3)*correctionUM))){
				phyCoord->decrementValue();
				baseCoord->decrementValue();
			}
			
		}
		
}

void defOControlCoordinateDecorator::rotateForward(){	

		if(typeOfCorrection==SUBTRACT_STEP && !(phyCoord->getValue()%static_cast<int>(pow(10, phyCoord->getUnit()-3)*correctionUM))){
			phyCoord->incrementValue();
			baseCoord->incrementValue();
		}else{
			
			defOStepperMotorDriverDecorator::rotateForward();
			
			if(typeOfCorrection!=ADD_STEP || (phyCoord->getValue()%static_cast<int>(pow(10, phyCoord->getUnit()-3)*correctionUM))){
				phyCoord->incrementValue();
				baseCoord->incrementValue();
			}
			
		}
		
}


