/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Piotr Poterała, 2021
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */

#include "pp_param.h"

defOParam::defOParam(string pname, int pvalue, int pdefaultValue, int pprecision, int punit, int plowerLimit, int pupperLimit)
{
    name=pname;
    lowerLimit=plowerLimit;
    upperLimit=pupperLimit;
    precision=pprecision;
    unit=punit;
	
		setValue(pvalue);
		setDefaultValue(pdefaultValue);
}

defOParam::defOParam(const defOParam &param){

    name=param.name;
    lowerLimit=param.lowerLimit;
    upperLimit=param.upperLimit;
    precision=param.precision;
    unit=param.unit;
	
		setValue(param.value);
		setDefaultValue(param.defaultValue);

}

defOParam& defOParam::operator=(const defOParam &param){

    name=param.name;
    setValue(param.value);
    defaultValue=param.defaultValue;
    lowerLimit=param.lowerLimit;
    upperLimit=param.upperLimit;
    precision=param.precision;
    unit=param.unit;

		setValue(param.value);
		setDefaultValue(param.defaultValue);
	
		return (*this);

}

defOParamGeneralShdPtr defOParam::clone(){
	
		return make_shared<defOParam>(*this);
	
}



string defOParam::getName(void) const{

    return name;

}

int defOParam::getValue(void) const{

    return value;
}



int defOParam::getLowerLimit(void) const{

    return lowerLimit;
}

int defOParam::getUpperLimit(void) const{

    return upperLimit;
}

int defOParam::getPrecision(void) const{

    return precision;
}

int defOParam::getUnit(void) const{

    return unit;
}

int defOParam::getDefaultValue(void) const{

    return defaultValue;
}


void defOParam::setValue(int newValue){

    value=correctData(newValue);
}

void defOParam::setDefaultValue(int newDefaultValue){

    defaultValue=correctData(newDefaultValue);
}


void defOParam::restoreDefaultValue(void){

    value=defaultValue;
}

void defOParam::setLowerLimit(int newLowerLimit){
	
		lowerLimit=newLowerLimit;
}


int defOParam::trimDataToRange(int data) const{

    if(data>=upperLimit)data=upperLimit;
    else if(data<=lowerLimit)data=lowerLimit;

    return data;
}


int defOParam::correctData(int data) const{
		int trimVal;
    trimVal=trimDataToRange(data);
		trimVal-=trimVal%precision;
		return trimVal;
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

