#include "platform_motor_parallel_driver.h"

defOPlatformParallelMotorDriver::defOPlatformParallelMotorDriver(pair<char, defOParam*> pCoord, pair<char, defOParam*> bCoord, GPIO_TypeDef* pPort, array<int, 2> *pPins, GPIO_TypeDef* iPort, array<int, 8> *iPins, int tOfStep, int corrUM):
	defOParallelMotorDriver(pCoord, bCoord, tOfStep, corrUM), phasesPort(pPort), phasesPins(pPins), inputsPort(iPort), inputsPins(iPins){
	
	
}

void defOPlatformParallelMotorDriver::setStateOfPins(){	
		int phasesMask=0, stateOfPhases=0, microStepMask=0, stateOfMicroStep=0;

		for(int i=0; i<phasesPins->size(); i++){
			if(phasesPins->at(i)>=0 && phasesPins->at(i)<16){
				phasesMask|=(1<<phasesPins->at(i));
				stateOfPhases|=(((mask>>i) & 0x1)<<phasesPins->at(i));
			}
		}

		phasesPort->ODR=(phasesPort->ODR & ~phasesMask) | stateOfPhases;
		
		
		for(int i=0; i<inputsPins->size(); i++){
			if(inputsPins->at(i)>=0 && inputsPins->at(i)<16){
				microStepMask|=(1<<inputsPins->at(i));
				stateOfMicroStep|=(((inputsMask>>i) & 0x1)<<inputsPins->at(i));
			}
		}

		inputsPort->ODR=(inputsPort->ODR & ~inputsMask) | stateOfPhases;
		
}


//ustawienie maski powodującej obrót silnika o jeden krok do tylu
void defOPlatformParallelMotorDriver::rotateBackwards(){	
	
		defOParallelMotorDriver::rotateBackwards();
		setStateOfPins();
		
}

void defOPlatformParallelMotorDriver::rotateForward(){	

		defOParallelMotorDriver::rotateForward();
		setStateOfPins();	
}



bool defOPlatformParallelMotorDriver::confirmRotateBackwards(){

	return defOParallelMotorDriver::confirmRotateBackwards();

}

bool defOPlatformParallelMotorDriver::confirmRotateForward(){


	return defOParallelMotorDriver::confirmRotateForward();

}
