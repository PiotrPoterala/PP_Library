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

#ifndef _PP_PARAM_MUTEX_DECORATOR_H
#define _PP_PARAM_MUTEX_DECORATOR_H
#include <string>
#include "pp_param_general.h"

#include "stm32xx.h"

using namespace std;

class defORTX5ParamMutexDecorator : public defOParamGeneral
{

	private:
		defOParamGeneralShdPtr paramGeneral;
		osMutexId_t	mutex;
	
	public:
		defORTX5ParamMutexDecorator(defOParamGeneralShdPtr param):paramGeneral(param){
				mutex=osMutexNew(NULL);
		};
		
		virtual ~defORTX5ParamMutexDecorator(){
			osMutexDelete(mutex);
		};
		
		
		virtual defOParamGeneralShdPtr clone() override{
	
			return make_shared<defORTX5ParamMutexDecorator>(paramGeneral->clone());
	
		}
		
    virtual string getName(void) const override{return paramGeneral->getName();};
    virtual int getValue(void) const override{return paramGeneral->getValue();};
    virtual int getLowerLimit(void) const override{return paramGeneral->getLowerLimit();};
    virtual int getUpperLimit(void) const override{return paramGeneral->getUpperLimit();};
    virtual int getPrecision(void) const override{return paramGeneral->getPrecision();};
    virtual int getUnit(void) const override{return paramGeneral->getUnit();};
    virtual int getDefaultValue(void) const override{return paramGeneral->getDefaultValue();};


    virtual void setValue(int newValue) override{		
			if(osKernelGetState() != osKernelRunning){
				paramGeneral->setValue(newValue);
			}else{
				if (osMutexAcquire(mutex, osWaitForever) == osOK) paramGeneral->setValue(newValue);
				osMutexRelease (mutex); 
			}
		};
		
		virtual void setDefaultValue(int newDefaultValue) override{	
			if(osKernelGetState() != osKernelRunning){
				paramGeneral->setDefaultValue(newDefaultValue);
			}else{
				if (osMutexAcquire(mutex, osWaitForever) == osOK) paramGeneral->setDefaultValue(newDefaultValue);
				osMutexRelease (mutex); 
			}
		};
		
		
		virtual void setLowerLimit(int newLowerLimit) override{
			if(osKernelGetState() != osKernelRunning){
				paramGeneral->setLowerLimit(newLowerLimit);
			}else{
				if (osMutexAcquire(mutex, osWaitForever) == osOK) paramGeneral->setLowerLimit(newLowerLimit);
				osMutexRelease (mutex); 
			}
		}
		
		
    virtual void restoreDefaultValue(void) override{		
			if(osKernelGetState() != osKernelRunning){
				paramGeneral->restoreDefaultValue();
			}else{
				if (osMutexAcquire(mutex, osWaitForever) == osOK) paramGeneral->restoreDefaultValue();
				osMutexRelease (mutex); 
			}
		};
		
		virtual int correctData(int data) const override{	
			return paramGeneral->correctData(data);
		}

		virtual bool decrementValue(void) override{		
			bool answer=false;
			
			if(osKernelGetState() != osKernelRunning){
				answer=paramGeneral->decrementValue();
			}else{
				if (osMutexAcquire(mutex, osWaitForever) == osOK) answer=paramGeneral->decrementValue();
				osMutexRelease (mutex); 
			}
			return answer;
		};
		
		virtual bool decrementValue(int val) override{		
			bool answer=false;
			if(osKernelGetState() != osKernelRunning){
				answer=paramGeneral->decrementValue(val);
			}else{
				if (osMutexAcquire(mutex, osWaitForever) == osOK) answer=paramGeneral->decrementValue(val);
				osMutexRelease (mutex); 
			}
			return answer;
		};
		
		virtual bool incrementValue(void) override{		
			bool answer=false;
			if(osKernelGetState() != osKernelRunning){
				answer=paramGeneral->incrementValue();
			}else{
				if (osMutexAcquire(mutex, osWaitForever) == osOK) answer=paramGeneral->incrementValue();
				osMutexRelease (mutex); 
			}
			return answer;
		};
		
		virtual bool incrementValue(int val) override{	
			bool answer=false;
			if(osKernelGetState() != osKernelRunning){
				answer=paramGeneral->incrementValue(val);
			}else{
				if (osMutexAcquire(mutex, osWaitForever) == osOK) answer=paramGeneral->incrementValue(val);
				osMutexRelease (mutex); 
			}
			return answer;
		};

};


#endif 