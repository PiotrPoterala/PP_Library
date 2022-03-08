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


#ifndef PP_PARAM_LIST_H
#define PP_PARAM_LIST_H

#include "stm32xx.h"
#include <string>
#include <map>
#include "pp_param_general.h"
#include "pstring.h"

using namespace std;

using PParamMap = map<char, defOParamGeneral*>;

class defOParamList
{

private:
    PParamMap param;

		void copyListOfParams(const PParamMap &copyParams);

public:
    defOParamList();
		defOParamList(const defOParamList& other);
    defOParamList(const PParamMap &copyParams);
		defOParamList& operator=(const defOParamList& other);
		~defOParamList();

		void clear(void);
		defOParamList* clone() const;
		bool exists(char acronim);

		defOParamGeneral* getParam(char acronim);
    PParamMap* getParams(void);

    int getParamValue(char acronim);
		int getParamUpperLimit(char acronim);
		int getParamUnit(char acronim);
		int getParamPrecision(char acronim);

		pair<char, defOParamGeneral*> getParamPair(char acronim);
		map<char, int> getParamsValues();
		string getStringWithParams();

		void insert(pair<char, defOParamGeneral*>);

    void setParamsByZero(void);
		bool setParamValue(char acronim, int val);
    void setParamsByValue(int value);
    void setParamsByDefaultValue();
    void setParamsValue(PParamMap &copyParams);
		void setParamsValue(map<char, double> &copyParams);

    bool comparingParamsValue(PParamMap &paramsToComp);
		bool comparingParamsValue(map<char, int> &paramToComp);

    void setParamsBasedString(PString &data);
};

#endif 
