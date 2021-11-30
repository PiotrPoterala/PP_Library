#ifndef _PP_STEPPER_MOTOR_DRIVER_H
	#define _PP_STEPPER_MOTOR_DRIVER_H

#include "pp_param.h"

using namespace std;

class defOStepperMotorDriver{
	
	
	public:
	
		defOStepperMotorDriver(){};	
			
		virtual void rotateForward() =0;
		virtual void rotateBackwards() =0;

		virtual void setAcronim(char pacronim)=0;
		virtual char getAcronim()=0;
			
		virtual int getAccelerationMMperSEC2Value()=0;
		virtual int getVelocityUMperSECValue()=0;
			
		virtual int getSignalMask()=0;
	
};

class defOStepperMotorDriverPar : public defOStepperMotorDriver{
	
	private:
		char acronim;	

		defOParam* accelerationMMperSEC2;
		defOParam* velocityUMperSEC;	
	
	public:
		defOStepperMotorDriverPar(defOParam* paccelerationMMperSEC2, defOParam* pvelocityUMperSEC):accelerationMMperSEC2(paccelerationMMperSEC2), velocityUMperSEC(pvelocityUMperSEC){};	
			
		virtual void rotateForward(){};
		virtual void rotateBackwards(){};

		virtual void setAcronim(char pacronim) final {acronim=pacronim;};
		virtual char getAcronim()final{return acronim;};
		
		virtual int getAccelerationMMperSEC2Value()final{return accelerationMMperSEC2->getValue();};
		virtual int getVelocityUMperSECValue()final{return velocityUMperSEC->getValue();};
			
		virtual int getSignalMask(){return 0;};
	
};

#endif
