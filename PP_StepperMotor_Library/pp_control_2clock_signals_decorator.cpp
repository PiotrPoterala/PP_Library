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

#include "pp_control_2clock_signals_decorator.h"

defOControl2ClockSignalsDecorator::defOControl2ClockSignalsDecorator(defOStepperMotorDriverShdPtr stepMotorDriver, vector<uPin> iPins, uPin enPin, int enPolar):
																																		defOStepperMotorDriverDecorator(stepMotorDriver), inputsPins(iPins), enablePin(enPin), enablePolar(enPolar){
	
		setEnable(false);																																
																																			
		for(auto it: iPins){		
			auto it_portMask=portMask.find(it.port);
			if(it_portMask==portMask.end())portMask.insert(PortMaskPair{it.port, {1<<it.pin,0}});
			else it_portMask->second.clrMask|=(1<<it.pin);
		}			
		
		setStateOfPins();
		setEnable(true);	
																																																																			
}

void defOControl2ClockSignalsDecorator::setStateOfPins(){	
	
		for(int i=0; i<inputsPins.size(); i++){
			auto it=portMask.find(inputsPins.at(i).port);
			it->second.mask|= (((defOStepperMotorDriverDecorator::getSignalMask()>>i) & 0x1)<<inputsPins.at(i).pin);
		}
		
		for(auto&& it:portMask){	
			it.first->ODR=(it.first->ODR & ~(it.second.clrMask)) | it.second.mask;
			it.second.mask=0;
		}
			
}


//ustawienie maski powodującej obrót silnika o jeden krok do tylu
void defOControl2ClockSignalsDecorator::rotateBackwards(){	
	
		defOStepperMotorDriverDecorator::rotateBackwards();
		setStateOfPins();
		
}

void defOControl2ClockSignalsDecorator::rotateForward(){	

		defOStepperMotorDriverDecorator::rotateForward();
		setStateOfPins();	
}


void defOControl2ClockSignalsDecorator::setEnable(bool enable){
			defOStepperMotorDriverDecorator::setEnable(enable);
			
			if(enable){
				if(enablePolar==B_LOW)PIN_CLR(enablePin.port, (1<<enablePin.pin));
				else PIN_SET(enablePin.port, (1<<enablePin.pin));
			}else{
				if(enablePolar==B_LOW)PIN_SET(enablePin.port, (1<<enablePin.pin));
				else PIN_CLR(enablePin.port, (1<<enablePin.pin));
			}
			
		};