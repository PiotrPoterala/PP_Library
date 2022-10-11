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
			
			enum{	
				PHY_COORD_ERROR=1,	//błąd przekroczenia zakresu współrzędnych fizycznych
				BASE_COORD_ERROR,	//błąd przekroczenia zakresu współrzędnych bazowych
				SAFTY_STEP_COUNTER_ERROR	
			};
			
		virtual shared_ptr<defOStepperMotorDriver> clone()=0;
			
		virtual void rotateForward() =0;
		virtual void rotateBackwards() =0;

//		virtual void setAcronim(char pacronim)=0;
//		virtual char getAcronim()=0;
			
		virtual void setError(char pacronim)=0;
		virtual char getError()=0;
			
		virtual PParamData getAccelerationXperSEC2Clone()=0;
		virtual PParamData getVelocityXperSECClone()=0;
			
		virtual PParamData getPhyCoordClone()=0;
		virtual PParamData getBaseCoordClone()=0;
			
		virtual int getSignalMask()=0;
			
		virtual void setEnable(bool enable)=0;
		virtual bool isEnable()=0;
			
		virtual shared_ptr<defOStepperMotorDriver> undecorate()=0;
		

		virtual defOParamGeneralShdPtr getPhyCoord()=0;
		virtual defOParamGeneralShdPtr getBaseCoord()=0;
	
	
};

using defOStepperMotorDriverShdPtr= shared_ptr<defOStepperMotorDriver>;

class defOStepperMotorDriverPar : public defOStepperMotorDriver{
	
	private:
//		char acronim;
		bool enable=false;
	
		int error;

		defOParamGeneralShdPtr accelerationXperSEC2;
		defOParamGeneralShdPtr velocityXperSEC;	
	
		defOParamGeneralShdPtr phyCoord;
		defOParamGeneralShdPtr baseCoord;
	
	public:
		defOStepperMotorDriverPar()=delete;
		defOStepperMotorDriverPar(defOParamGeneralShdPtr paccelerationXperSEC2, defOParamGeneralShdPtr pvelocityXperSEC,
															defOParamGeneralShdPtr pphyCoord, defOParamGeneralShdPtr pbaseCoord):
															accelerationXperSEC2(paccelerationXperSEC2), velocityXperSEC(pvelocityXperSEC), phyCoord(pphyCoord), baseCoord(pbaseCoord){};	
			
		virtual defOStepperMotorDriverShdPtr clone()override{return make_shared<defOStepperMotorDriverPar>(*this);};													
																
		virtual void rotateForward()override{};
		virtual void rotateBackwards()override{};

//		virtual void setAcronim(char acronim) final {this->acronim=acronim;};
//		virtual char getAcronim()final{return acronim;};
		
		virtual void setError(char error) final {this->error=error;};
		virtual char getError()final{return error;};
		
		virtual PParamData getAccelerationXperSEC2Clone()final{
				PParamData value;
				if(accelerationXperSEC2!=nullptr)value.push_back(accelerationXperSEC2->clone());
				return value;
		};
		
		virtual PParamData getVelocityXperSECClone()final{
				PParamData value;
				if(velocityXperSEC!=nullptr)value.push_back(velocityXperSEC->clone());
				return value;
		};
			
		virtual PParamData getPhyCoordClone()final{
				PParamData value;
				if(phyCoord!=nullptr)value.push_back(phyCoord->clone());
				return value;
		};
		
		virtual PParamData getBaseCoordClone()final{
				PParamData value;
				if(baseCoord!=nullptr)value.push_back(baseCoord->clone());
				return value;
		};
		
		virtual int getSignalMask()override{return 0;};
		
		virtual void setEnable(bool enable)final{this->enable=enable;};
		virtual bool isEnable()final{ return enable;};
		
		virtual defOStepperMotorDriverShdPtr undecorate()override{return make_shared<defOStepperMotorDriverPar>(*this);};
	
		virtual defOParamGeneralShdPtr getPhyCoord()final{return phyCoord;};
		virtual defOParamGeneralShdPtr getBaseCoord()final{return baseCoord;};
		
};


#endif
