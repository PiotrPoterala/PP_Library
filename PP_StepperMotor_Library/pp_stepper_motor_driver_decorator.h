/**
 * @author  Piotr Poterała
 * @email   poterala.piotr@gmail.com
 * @website http://zappp.pl
 * @version v1.0
 * @ide     Keil uVision 5
 * @license GNU GPL v3
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Piotr Poterała, 2021
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */
#ifndef _PP_STEPPER_MOTOR_DRIVER_DECORATOR_H
	#define _PP_STEPPER_MOTOR_DRIVER_DECORATOR_H

#include "pp_stepper_motor_driver.h"
#include "def_pins.h"

using namespace std;


class defOStepperMotorDriverDecorator : public defOStepperMotorDriver{
	
	protected:

		defOStepperMotorDriverShdPtr stepperMotorDriver;
	
		virtual defOParamGeneralShdPtr getPhyCoord()final{return stepperMotorDriver->getPhyCoord();};
		virtual defOParamGeneralShdPtr getBaseCoord()final{return stepperMotorDriver->getBaseCoord();};
	
	public:
		defOStepperMotorDriverDecorator(defOStepperMotorDriverShdPtr stepMotorDriver):stepperMotorDriver(stepMotorDriver){};
	
		virtual void rotateForward()override{stepperMotorDriver->rotateForward();};
		virtual void rotateBackwards()override{stepperMotorDriver->rotateBackwards();};
	
//		virtual void setAcronim(char pacronim)override{stepperMotorDriver->setAcronim(pacronim);};
//		virtual char getAcronim()override{return stepperMotorDriver->getAcronim();};
		
		virtual void setError(char pacronim)final{stepperMotorDriver->setError(pacronim);};
		virtual char getError()final{return stepperMotorDriver->getError();};
		
		virtual PParamData getAccelerationXperSEC2Clone()final{return stepperMotorDriver->getAccelerationXperSEC2Clone();};
		virtual PParamData getVelocityXperSECClone()final{return stepperMotorDriver->getVelocityXperSECClone();};
		
		virtual PParamData getPhyCoordClone()final{return stepperMotorDriver->getPhyCoordClone();};
		virtual PParamData getBaseCoordClone()final{return stepperMotorDriver->getBaseCoordClone();};
		
		virtual int getSignalMask()override{return stepperMotorDriver->getSignalMask();};

		virtual void setEnable(bool enable)override{stepperMotorDriver->setEnable(enable);};
		virtual bool isEnable()override{ return stepperMotorDriver->isEnable();};
		
		defOStepperMotorDriverShdPtr undecorate()override{return stepperMotorDriver;}
		
};


#endif
