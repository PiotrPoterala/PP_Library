#include "pp_stepper_motor_2clock_driver.h"

defOStepperMotor2clockDriver::defOStepperMotor2clockDriver(int paccelerationMMperSEC2, defOParam* pvelocityUMperSEC, int tOfStep){
	
	
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
	maskIter=maskStep->begin();
}



//ustawienie maski powodującej obrót silnika o jeden krok do tylu
void defOStepperMotor2clockDriver::rotateBackwards(){	


			if(maskIter==maskStep->begin())maskIter=maskStep->end();
			else maskIter--;
			
		
}

void defOStepperMotor2clockDriver::rotateForward(){	

			if(maskIter==maskStep->end())maskIter=maskStep->begin();
			else maskIter++;
				
}

