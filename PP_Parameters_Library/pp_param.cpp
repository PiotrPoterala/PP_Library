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
    value=pvalue;
    defaultValue=pdefaultValue;
    lowerLimit=plowerLimit;
    upperLimit=pupperLimit;
    precision=pprecision;
    unit=punit;
	
		checkCorrectnes();
}

defOParam::defOParam(const defOParam &param){

    name=param.name;
    value=param.value;
    defaultValue=param.defaultValue;
    lowerLimit=param.lowerLimit;
    upperLimit=param.upperLimit;
    precision=param.precision;
    unit=param.unit;
	
		checkCorrectnes();


}

defOParam& defOParam::operator=(const defOParam &param){

    name=param.name;
    value=param.value;
    defaultValue=param.defaultValue;
    lowerLimit=param.lowerLimit;
    upperLimit=param.upperLimit;
    precision=param.precision;
    unit=param.unit;
	
		checkCorrectnes();

		return (*this);

}


string defOParam::getName(void){

    return name;

}

int defOParam::getValue(void){

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


void defOParam::checkCorrectnes(){

    checkRange();
		value-=value%precision;
	
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

