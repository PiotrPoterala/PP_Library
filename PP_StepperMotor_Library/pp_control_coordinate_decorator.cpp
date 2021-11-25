#include "pp_control_coordinate_decorator.h"

defOControlCoordinateDecorator::defOControlCoordinateDecorator(defOStepperMotorDriver* stepMotorDriver, pair<char,defOParamGeneral*> pCoord, defOParamGeneral* bCoord, int corrUM):
																															defOStepperMotorDriverDecorator(stepMotorDriver), baseCoord(bCoord){
																						
		defOStepperMotorDriverDecorator::setAcronim(pCoord.first);																							
																																
		phyCoord=pCoord.second;																																
																																
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

		if(typeOfCorrection==SUBTRACT_STEP && !(phyCoord->getValue()%static_cast<int>(pow(10, phyCoord->getUnit()-3)*correctionUM))){
			phyCoord->decrementValue();
			baseCoord->decrementValue();
		}else{
			defOStepperMotorDriverDecorator::rotateBackwards();
	
			if(typeOfCorrection!=ADD_STEP || (phyCoord->getValue()%static_cast<int>(pow(10, phyCoord->getUnit()-3)*correctionUM))){
				phyCoord->decrementValue();
				baseCoord->decrementValue();
			}
			
		}
		
}

void defOControlCoordinateDecorator::rotateForward(){	

		if(typeOfCorrection==SUBTRACT_STEP && !(phyCoord->getValue()%static_cast<int>(pow(10, phyCoord->getUnit()-3)*correctionUM))){
			phyCoord->incrementValue();
			baseCoord->incrementValue();
		}else{
			
			defOStepperMotorDriverDecorator::rotateForward();
			
			if(typeOfCorrection!=ADD_STEP || (phyCoord->getValue()%static_cast<int>(pow(10, phyCoord->getUnit()-3)*correctionUM))){
				phyCoord->incrementValue();
				baseCoord->incrementValue();
			}
			
		}
		
}


