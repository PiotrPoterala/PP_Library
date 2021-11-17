#include "pp_control_2clock_signals_decorator.h"

defOControl2ClockSignalsDecorator::defOControl2ClockSignalsDecorator(defOStepperMotorDriver* stepMotorDriver, GPIO_TypeDef* pPort, array<int, 2> *pPins, GPIO_TypeDef* iPort, array<int, 8> *iPins):
																																		defOStepperMotorDriverDecorator(stepMotorDriver), phasesPort(pPort), phasesPins(pPins), inputsPort(iPort), inputsPins(iPins){
	
}

void defOControl2ClockSignalsDecorator::setStateOfPins(){	
		int phasesMask=0, stateOfPhases=0, microStepMask=0, stateOfMicroStep=0;

		for(int i=0; i<phasesPins->size(); i++){
			if(phasesPins->at(i)>=0 && phasesPins->at(i)<16){
				phasesMask|=(1<<phasesPins->at(i));
				stateOfPhases|=((((defOStepperMotorDriverDecorator::getSignalMask() & PHASAES_MASK)>>i) & 0x1)<<phasesPins->at(i));
			}
		}

		phasesPort->ODR=(phasesPort->ODR & ~phasesMask) | stateOfPhases;
		
		
		for(int i=0; i<inputsPins->size(); i++){
			if(inputsPins->at(i)>=0 && inputsPins->at(i)<16){
				microStepMask|=(1<<inputsPins->at(i));
				stateOfMicroStep|=((((defOStepperMotorDriverDecorator::getSignalMask() & MICROSTEPPING_MASK)>>i) & 0x1)<<inputsPins->at(i));
			}
		}

		inputsPort->ODR=(inputsPort->ODR & ~microStepMask) | stateOfPhases;
		
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


