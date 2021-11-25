#ifndef _PP_PARAM_H
#define _PP_PARAM_H
#include <string>
#include "pp_param_general.h"

#include "stm32xx.h"

using namespace std;

class defOParam : public defOParamGeneral
{

private:
    string name;
    int value;
    int defaultValue;
    int lowerLimit;
    int upperLimit;
    int precision;
    int unit;

public:
    defOParam(defOParam &param);
    defOParam(string pname, int pvalue=0, int pdefaultValue=0, int pprecision=1, int punit=0, int plowerLimit=0, int pupperLimit=0);
		virtual ~defOParam(){};
    virtual string getName(void) override;
    virtual int getValue(void) override;
    virtual int getLowerLimit(void) override;
    virtual int getUpperLimit(void) override;
    virtual int getPrecision(void) override;
    virtual int getUnit(void) override;
    virtual int getDefaultValue(void) override;

    virtual int checkRange(int val) override;

    virtual void setValue(int newValue) override;
    virtual void resetValue(void) override;

		virtual void checkCorrectnes() override;
		virtual void checkRange() override;

		virtual bool decrementValue() override;
		virtual bool decrementValue(int val) override;
		virtual bool incrementValue() override;
		virtual bool incrementValue(int val) override;
		

};


#endif // AUT_WORK_PARAM_H
