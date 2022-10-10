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

#include "pp_control_coordinate_range_decorator.h"
#include "pp_math.h"

defOControlCoordinateRangeDecorator::defOControlCoordinateRangeDecorator(defOStepperMotorDriverShdPtr stepMotorDriver):
																															defOStepperMotorDriverDecorator(stepMotorDriver){
													

	phyCoord=defOStepperMotorDriverDecorator::getPhyCoord();
	baseCoord=defOStepperMotorDriverDecorator::getBaseCoord();
																																																						
																																
}

void defOControlCoordinateRangeDecorator::rotateBackwards(){	


	if(!phyCoord->tryDecrementValue())defOStepperMotorDriverDecorator::setError(PHY_COORD_ERROR);
	else if(!baseCoord->tryDecrementValue())defOStepperMotorDriverDecorator::setError(BASE_COORD_ERROR);
	else{ 
	
			defOStepperMotorDriverDecorator::rotateBackwards();
		
	}	
}

void defOControlCoordinateRangeDecorator::rotateForward(){	


		if(!phyCoord->tryIncrementValue())defOStepperMotorDriverDecorator::setError(PHY_COORD_ERROR);
		else if(!baseCoord->tryIncrementValue())defOStepperMotorDriverDecorator::setError(BASE_COORD_ERROR);
		else{ 
				
			defOStepperMotorDriverDecorator::rotateForward();	

		}
}


