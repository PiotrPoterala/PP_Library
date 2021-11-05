#include "pp_stepper_motor_2clock_driver.h"

defOStepperMotor2clockDriver::defOStepperMotor2clockDriver(int paccelerationMMperSEC2, defOParam* pvelocityUMperSEC, int tOfStep){
	
	posOfSequence=0;
	
	accelerationMMperSEC2=paccelerationMMperSEC2;
	velocityUMperSEC=pvelocityUMperSEC;
	
	setTypeOfStep(tOfStep);
	
}

void defOStepperMotor2clockDriver::setTypeOfStep(int tOfStep){
	
	typeOfStep=tOfStep;
	
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
void defOStepperMotor2clockDriver::rotateBackwards(){	


			posOfSequence--;
			if(posOfSequence<0)posOfSequence=maskStep->size()-1;

			signalsMask=maskStep->at(posOfSequence);// & PHASAES_MASK;
//			microsteppingMask=(maskStep->at(posOfSequence)>>2) & INPUTS_MASK;
			
		
}

void defOStepperMotor2clockDriver::rotateForward(){	

			posOfSequence++;
			
			if(posOfSequence>=maskStep->size())posOfSequence=0;
			
			signalsMask=maskStep->at(posOfSequence);// & PHASAES_MASK;
	//		microsteppingMask=(maskStep->at(posOfSequence)>>2) & INPUTS_MASK;
				
}

