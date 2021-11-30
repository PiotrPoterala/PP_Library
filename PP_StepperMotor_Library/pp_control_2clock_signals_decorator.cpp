#include "pp_control_2clock_signals_decorator.h"

defOControl2ClockSignalsDecorator::defOControl2ClockSignalsDecorator(defOStepperMotorDriver* stepMotorDriver, vector<uPin> *iPins):
																																		defOStepperMotorDriverDecorator(stepMotorDriver),  inputsPins(iPins){
	
		for(auto it: *iPins){		
			auto it_portMask=portMask.find(it.port);
			if(it_portMask==portMask.end())portMask.insert(pair<GPIO_TypeDef*, uPortMask*>{it.port, new uPortMask{1<<it.pin,0}});
			else (*it_portMask).second->clrMask|=(1<<it.pin);
			
		}			
																																																																			
}

void defOControl2ClockSignalsDecorator::setStateOfPins(){	
	
		for(int i=0; i<inputsPins->size(); i++){
			auto it=portMask.find(inputsPins->at(i).port);
			(*it).second->mask|= (((defOStepperMotorDriverDecorator::getSignalMask()>>i) & 0x1)<<inputsPins->at(i).pin);
		}
		
		for(auto it:portMask){	
			it.first->ODR=(it.first->ODR & ~(it.second->clrMask)) | it.second->mask;
			it.second->mask=0;
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


