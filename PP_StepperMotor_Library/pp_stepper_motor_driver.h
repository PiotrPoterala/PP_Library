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
#ifndef _PP_STEPPER_MOTOR_DRIVER_H
	#define _PP_STEPPER_MOTOR_DRIVER_H

#include "pp_param.h"

using namespace std;

class defOStepperMotorDriver{
	
	
	public:
	
		defOStepperMotorDriver(){};	
			
		virtual void rotateForward() =0;
		virtual void rotateBackwards() =0;

		virtual void setAcronim(char pacronim)=0;
		virtual char getAcronim()=0;
			
		virtual int getAccelerationMMperSEC2Value()=0;
		virtual int getVelocityUMperSECValue()=0;
			
		virtual int getSignalMask()=0;
			
		virtual void setEnable(bool enable)=0;
		virtual bool isEnable()=0;
	
};

class defOStepperMotorDriverPar : public defOStepperMotorDriver{
	
	private:
		char acronim;
		bool enable=false;

		defOParam* accelerationMMperSEC2;
		defOParam* velocityUMperSEC;	
	
	public:
		defOStepperMotorDriverPar(defOParam* paccelerationMMperSEC2, defOParam* pvelocityUMperSEC):accelerationMMperSEC2(paccelerationMMperSEC2), velocityUMperSEC(pvelocityUMperSEC){};	
			
		virtual void rotateForward(){};
		virtual void rotateBackwards(){};

		virtual void setAcronim(char acronim) final {this->acronim=acronim;};
		virtual char getAcronim()final{return acronim;};
		
		virtual int getAccelerationMMperSEC2Value()final{return accelerationMMperSEC2->getValue();};
		virtual int getVelocityUMperSECValue()final{return velocityUMperSEC->getValue();};
			
		virtual int getSignalMask(){return 0;};
		
		virtual void setEnable(bool enable)final{this->enable=enable;};
		virtual bool isEnable()final{ return enable;};
	
};

#endif
