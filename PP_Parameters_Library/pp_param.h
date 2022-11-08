/**
 * @author  Piotr Poterała
 * @email   poterala.piotr@gmail.com
 * @website http://zappp.pl
 * @version v1.0
 * @ide     Keil uVision 5
 * @license GNU GPL v3
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Piotr Poterała, 2021
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */


#ifndef _PP_PARAM_H
#define _PP_PARAM_H
#include <string>
#include "pp_param_general.h"

#include "stm32xx.h"

using namespace std;


using PParamLimit=tuple<int,int,int,int>;
using PParamLimits=map<char, PParamLimit>;

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


    int trimDataToRange(int data) const noexcept;

public:
    defOParam(const defOParam &param);
    defOParam(string pname, int pdefaultValue, int plowerLimit, int pupperLimit, int pprecision=1, int punit=0);
		defOParam &operator=(const defOParam &param);
		virtual ~defOParam(){};
			
		virtual defOParamGeneralShdPtr clone() override;
			
    virtual string getName(void) const noexcept override;
    virtual int getValue(void) const noexcept override;
    virtual int getLowerLimit(void) const noexcept override;
    virtual int getUpperLimit(void) const noexcept override;
    virtual int getPrecision(void) const noexcept override;
    virtual int getUnit(void) const noexcept override;
    virtual int getDefaultValue(void) const noexcept override;

    virtual void setValue(int newValue) noexcept override;
		virtual void setDefaultValue(int newDefaultValue) noexcept override;
		virtual void setLowerLimit(int newLowerLimit) noexcept override;
			
    virtual void restoreDefaultValue(void) noexcept override;
		virtual int correctData(int data) const noexcept override;

		virtual bool tryDecrementValue() const noexcept override;
		virtual bool decrementValue() noexcept override;
		virtual bool decrementValue(int val) noexcept override;
		virtual bool tryIncrementValue() const noexcept override;
		virtual bool incrementValue() noexcept override;
		virtual bool incrementValue(int val) noexcept override;
		

};

using defOParamShrPtr = shared_ptr<defOParam>;

#endif // AUT_WORK_PARAM_H
