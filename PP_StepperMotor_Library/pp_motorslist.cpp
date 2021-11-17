#include "pp_motorslist.h"


defOMotorsList::defOMotorsList(){
	
	
}

vector<defOStepperMotorDriver*>* defOMotorsList::getMotors(void){
	
	return &motors;
	
}

defOStepperMotorDriver* defOMotorsList::getMotor(char acronim){

	vector<defOStepperMotorDriver*>::iterator it=getIterator(acronim);
	
	if(it!=motors.end()) return (*it);
	
	return nullptr;
}

vector<defOStepperMotorDriver*>::iterator defOMotorsList::getIterator(){

	return motors.begin();
	
}


vector<defOStepperMotorDriver*>::iterator defOMotorsList::getIterator(char acronim){

	vector<defOStepperMotorDriver*>::iterator it;
	
	for(it=motors.begin(); it!=motors.end(); ++it){
	//	if((*it)->acronim==acronim) break;
		
	}
	
	return it;
}

void defOMotorsList::clearCounters(){

	vector<defOStepperMotorDriver*>::iterator it;
	
	for(it=motors.begin(); it!=motors.end(); ++it){
	//	(*it)->counter=0;
	}
	
}