#ifndef PP_MOTOR_LIST_H
#define PP_MOTOR_LIST_H

#include "stm32xx.h"
#include <vector>
#include "pp_stepper_motor_driver.h"

using namespace std;

class defOMotorsList
{

private:
    vector<defOStepperMotorDriver*> motors;

public:
    defOMotorsList();

		vector<defOStepperMotorDriver*>* getMotors(void);
    defOStepperMotorDriver* getMotor(char acronim);
		vector<defOStepperMotorDriver*>::iterator getIterator(char acronim);

};

#endif 