#include "pp_control_coordinate_decorator.h"

defOControlCoordinateDecorator::defOControlCoordinateDecorator(defOStepperMotorDriver* stepMotorDriver, defOParam* pCoord, defOParam* bCoord, int corrUM):
																															defOStepperMotorDriverDecorator(stepMotorDriver), phyCoord(pCoord), baseCoord(bCoord){
	
	if(corrUM>0){
		correctionUM=corrUM;
		typeOfCorrection=ADD_STEP;
	}else if(corrUM<0){
		correctionUM=abs(corrUM);
		typeOfCorrection=SUBTRACT_STEP;
	}else{
		correctionUM=0;
		typeOfCorrection=DO_NOTHING_WITH_STEP;
	}																									
																																
}




void defOControlCoordinateDecorator::rotateBackwards(){	

		if(typeOfCorrection==SUBTRACT_STEP && !(phyCoord->getValue()%(int32_t)(pow(10, phyCoord->getUnit()-3)*correctionUM))){
			phyCoord->decrementValue();
			baseCoord->decrementValue();
		}else{
			defOStepperMotorDriverDecorator::rotateBackwards();
	
			if(typeOfCorrection!=ADD_STEP || (phyCoord->getValue()%(int32_t)(pow(10, phyCoord->getUnit()-3)*correctionUM))){
				phyCoord->decrementValue();
				baseCoord->decrementValue();
			}
			
		}
		
}

void defOControlCoordinateDecorator::rotateForward(){	

		if(typeOfCorrection==SUBTRACT_STEP && !(phyCoord->getValue()%(int32_t)(pow(10, phyCoord->getUnit()-3)*correctionUM))){
			phyCoord->incrementValue();
			baseCoord->incrementValue();
		}else{
			
			defOStepperMotorDriverDecorator::rotateForward();
			
			if(typeOfCorrection!=ADD_STEP || (phyCoord->getValue()%(int32_t)(pow(10, phyCoord->getUnit()-3)*correctionUM))){
				phyCoord->incrementValue();
				baseCoord->incrementValue();
			}
			
		}
		
}


