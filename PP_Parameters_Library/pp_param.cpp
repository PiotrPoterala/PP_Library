#include "pp_param.h"

defOParam::defOParam(string pname, int pvalue, int pdefaultValue, int pprecision, int punit, int plowerLimit, int pupperLimit)
{
    name=pname;
    value=pvalue;
    defaultValue=pdefaultValue;
    lowerLimit=plowerLimit;
    upperLimit=pupperLimit;
    precision=pprecision;
    unit=punit;
	
		checkCorrectnes();
}

defOParam::defOParam(defOParam &param){

    name=param.name;
    value=param.value;
    defaultValue=param.defaultValue;
    lowerLimit=param.lowerLimit;
    upperLimit=param.upperLimit;
    precision=param.precision;
    unit=param.unit;
	
		checkCorrectnes();

    copyListOfParams(param.allowedValues);

}


string defOParam::getName(void){

    return name;

}

int defOParam::getValue(void){

    return value;
}

int & defOParam::getRvalue(void){

    return value;
}


int defOParam::getLowerLimit(void){

    return lowerLimit;
}

int defOParam::getUpperLimit(void){

    return upperLimit;
}

int defOParam::getPrecision(void){

    return precision;
}

int defOParam::getUnit(void){

    return unit;
}


void defOParam::setValue(int newValue){

    value=newValue;
}

int defOParam::getDefaultValue(void){

    return defaultValue;
}

list<int>* defOParam::getAllowedValues(void){

    return &allowedValues;

}

void defOParam::resetValue(void){

    value=defaultValue;
}


void defOParam::checkRange(){

    if(value>=upperLimit)value=upperLimit;
    else if(value<=lowerLimit)value=lowerLimit;

}

int defOParam::checkRange(int val){

    if(val>=upperLimit)val=upperLimit;
    else if(val<=lowerLimit)val=lowerLimit;

    return val;
}

int defOParam::checkRange(int val, int upperLim, int lowerLim){

    if(val>=upperLim)val=upperLim;
    else if(val<=lowerLim)val=lowerLim;

    return val;
}

void defOParam::checkCorrectnes(){

    checkRange();
		value-=value%precision;
	
}

void defOParam::copyListOfParams(list<int> &allowedValuesList){

    if(allowedValues.empty()==false){
        allowedValues.clear();
    }

		for (list<int>::iterator it=allowedValuesList.begin(); it != allowedValuesList.end(); ++it){

        allowedValues.push_back(*it);
    }


}

bool defOParam::decrementValue(){
	bool changeParam=false;

	if(value-precision>=lowerLimit){
		value-=precision;
		changeParam=true;
	}

	return changeParam;
}

bool defOParam::decrementValue(int val){
	bool changeParam=false;

	if(value-val>=lowerLimit){
		value-=val;
		changeParam=true;
	}

	return changeParam;
}

bool defOParam::incrementValue(){
	bool changeParam=false;

	if(value+precision<=upperLimit){
		value+=precision;
		changeParam=true;
	}

	return changeParam;
}

bool defOParam::incrementValue(int val){
	bool changeParam=false;

	if(value+val<=upperLimit){
		value+=val;
		changeParam=true;
	}

	return changeParam;
}

