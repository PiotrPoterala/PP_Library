#include "motor_parallel_driver.h"

defOParallelMotorDriver::defOParallelMotorDriver(pair<char, defOParam*> pCoord, pair<char, defOParam*> bCoord, int tOfStep, int corrUM):defOMotorDriver(pCoord, bCoord, tOfStep, corrUM){
	
	posOfSequence=0;
	previousPosOfSequence=0;
	
	setTypeOfStep(tOfStep);
	
}

void defOParallelMotorDriver::setTypeOfStep(int tOfStep){
	
	defOMotorDriver::setTypeOfStep(tOfStep);
	
	switch(typeOfStep){
		case FULL_STEP:
			maskStep=&maskFullStep;
			break;
		case HALF_STEP:
			maskStep=&maskHalfStep;
			break;
		case MICRO_STEP:
			maskStep=&maskMicroStep;
			break;
	}
	
}


//ustawienie maski powodującej obrót silnika o jeden krok do tylu
void defOParallelMotorDriver::rotateBackwards(){	

		if(typeOfCorrection==SUBTRACT_STEP && !(phyCoord.second->getValue()%(int32_t)(pow(10, phyCoord.second->getUnit()-3)*correctionUM)) && relizeSubstractStepInTravelBack==false){
			relizeSubstractStepInTravelBack=true;
		}else{
			
			posOfSequence--;
			if(posOfSequence<0)posOfSequence=maskStep->size()-1;

			mask=maskStep->at(posOfSequence) & PHASAES_MASK;
			inputsMask=(maskStep->at(posOfSequence)>>2) & INPUTS_MASK;
			
		}
		
}

void defOParallelMotorDriver::rotateForward(){	

		if(typeOfCorrection==SUBTRACT_STEP && !(phyCoord.second->getValue()%(int32_t)(pow(10, phyCoord.second->getUnit()-3)*correctionUM)) && relizeSubstractStepInTravelForward==false){
			relizeSubstractStepInTravelForward=true;
		}else{
			
			posOfSequence++;
			
			if(posOfSequence>=maskStep->size())posOfSequence=0;
			
			mask=maskStep->at(posOfSequence) & PHASAES_MASK;
			inputsMask=(maskStep->at(posOfSequence)>>2) & INPUTS_MASK;
			
		}
		
}


bool defOParallelMotorDriver::confirmRotateBackwards(){
	int prevPosOfSequence=0x0;

	if(typeOfCorrection==SUBTRACT_STEP && relizeSubstractStepInTravelBack==true){
		phyCoord.second->decrementValue();
		baseCoord.second->decrementValue();
		relizeSubstractStepInTravelBack=false;
		return true;
	}else{

		prevPosOfSequence=previousPosOfSequence-1;
		if(prevPosOfSequence<0)prevPosOfSequence=maskStep->size()-1;
		
		if(posOfSequence==prevPosOfSequence){
			previousPosOfSequence=prevPosOfSequence; 
			if(typeOfCorrection==ADD_STEP && relizeLeapStep==false && !(phyCoord.second->getValue()%(int32_t)(pow(10, phyCoord.second->getUnit()-3)*correctionUM))){
				relizeLeapStep=true;
			}else{
				phyCoord.second->decrementValue();
				baseCoord.second->decrementValue();
				relizeLeapStep=false;
			}
			return true;
		}
	}
	return false;

}

bool defOParallelMotorDriver::confirmRotateForward(){
	int prevPosOfSequence=0x0;

	if(typeOfCorrection==SUBTRACT_STEP && relizeSubstractStepInTravelForward==true){
		phyCoord.second->incrementValue();
		baseCoord.second->incrementValue();
		relizeSubstractStepInTravelForward=false;
		return true;
	}else{

		prevPosOfSequence=previousPosOfSequence-1;
		if(prevPosOfSequence>=maskStep->size())prevPosOfSequence=0;
		
		if(posOfSequence==prevPosOfSequence){
			previousPosOfSequence=prevPosOfSequence; 
			if(typeOfCorrection==ADD_STEP && relizeLeapStep==false && !(phyCoord.second->getValue()%(int32_t)(pow(10, phyCoord.second->getUnit()-3)*correctionUM))){
				relizeLeapStep=true;
			}else{
				phyCoord.second->incrementValue();
				baseCoord.second->incrementValue();
				relizeLeapStep=false;
			}
			return true;
		}
	}
	return false;

}
