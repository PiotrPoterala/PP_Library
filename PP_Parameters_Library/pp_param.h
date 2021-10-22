#ifndef _PP_PARAM_H
#define _PP_PARAM_H
#include <string>
#include <list>

#include "stm32xx.h"

using namespace std;

class defOParam
{

private:
    string name;
//    char acronim;
    int value;
    int defaultValue;
    list<int> allowedValues;
    int lowerLimit;
    int upperLimit;
    int precision;
    int unit;
public:
    defOParam(defOParam &param);
    defOParam(string pname, int pvalue=0, int pdefaultValue=0, int pprecision=1, int punit=0, int plowerLimit=0, int pupperLimit=0);
    string getName(void);
 //   char getAcronim(void);
    int getValue(void);
    int & getRvalue(void);
    int getLowerLimit(void);
    int getUpperLimit(void);
    int getPrecision(void);
    int getUnit(void);
    int getDefaultValue(void);
    list<int>* getAllowedValues(void);
    void setValue(int newValue);
    void resetValue(void);

		void checkCorrectnes();
		void checkRange();
    int checkRange(int val);
    static int checkRange(int val, int upperLim, int lowerLim);
    void copyListOfParams(list<int> &allowedValuesList);

		bool decrementValue();
		bool decrementValue(int val);
		bool incrementValue();
		bool incrementValue(int val);

};


#endif // AUT_WORK_PARAM_H
