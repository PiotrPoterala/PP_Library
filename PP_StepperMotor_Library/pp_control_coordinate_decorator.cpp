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
#include "pp_math.h"

defOControlCoordinateDecorator::defOControlCoordinateDecorator(defOStepperMotorDriverShdPtr stepMotorDriver, defOParamGeneralShdPtr corr):
																															defOStepperMotorDriverDecorator(stepMotorDriver), correction(corr){
													

	phyCoord=defOStepperMotorDriverDecorator::getPhyCoord();
	baseCoord=defOStepperMotorDriverDecorator::getBaseCoord();
																																
//		defOStepperMotorDriverDecorator::setAcronim(pCoord.first);																							
//																																
//		phyCoord=pCoord.second;																																
//																																
//	if(corrUM>0){
//		correctionUM=corrUM;
//		typeOfCorrection=ADD_STEP;
//	}else if(corrUM<0){
//		correctionUM=abs(corrUM);
//		typeOfCorrection=SUBTRACT_STEP;
//	}else{
//		correctionUM=0;
//		typeOfCorrection=DO_NOTHING_WITH_STEP;
//	}																									
																																
}

bool defOControlCoordinateDecorator::isLeapStep(){
	bool leapStep=false;
	
	defOParamGeneralShdPtr phyCoord=defOStepperMotorDriverDecorator::getPhyCoord();
	
	if(!(phyCoord->getValue()%(pow_pp(10, phyCoord->getUnit()-correction->getUnit())*correction->getValue())))leapStep=true;

	
	return leapStep;
}


void defOControlCoordinateDecorator::rotateBackwards(){	

	
		if(correction->getValue()<0 && isLeapStep()){
			phyCoord->decrementValue();
			baseCoord->decrementValue();
		}else{
			defOStepperMotorDriverDecorator::rotateBackwards();
		
			if(correction->getValue()>0 && isLeapStep() && leapStepFlag==false){
				leapStepFlag=true;
			}else{
				phyCoord->decrementValue();
				baseCoord->decrementValue();
				leapStepFlag=false;
			}
			
		}
		
}

void defOControlCoordinateDecorator::rotateForward(){	

			if(correction->getValue()<0 && isLeapStep()){
				phyCoord->incrementValue();
				baseCoord->incrementValue();
			}else{			
				defOStepperMotorDriverDecorator::rotateForward();
				
				if(correction->getValue()>0 && isLeapStep() && leapStepFlag==false){
					leapStepFlag=true;
				}else{
					phyCoord->incrementValue();
					baseCoord->incrementValue();
					leapStepFlag=false;
				}
				
			}
		
}


