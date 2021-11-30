#include "pp_stepper_motor_2clock_driver.h"

defOStepperMotor2clockDriver::defOStepperMotor2clockDriver(defOParam* paccelerationMMperSEC2, defOParam* pvelocityUMperSEC, int tOfStep):defOStepperMotorDriverPar(paccelerationMMperSEC2, pvelocityUMperSEC){
	
	
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

		if(maskIter==maskStep->begin())maskIter=maskStep->end()-1;
		else maskIter--;
				
}

void defOStepperMotor2clockDriver::rotateForward(){	

			maskIter++;
			if(maskIter==maskStep->end())maskIter=maskStep->begin();
}

