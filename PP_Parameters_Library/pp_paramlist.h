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

#include <string>
#include "pp_param_general.h"
#include "pp_param.h"
#include "pstring.h"

using namespace std;

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
		shared_ptr<defOParamList> clone() const;
		PParamData getParamClone(char acronim);
		bool exists(char acronim);

		PParamData getParam(char acronim) noexcept;
 //   PParamMap getParams(void) noexcept;


    int getParamValue(char acronim) noexcept;
		int getParamUpperLimit(char acronim) noexcept;
		int getParamUnit(char acronim) noexcept;
		int getParamPrecision(char acronim) noexcept;

		PParamPair getParamPair(char acronim) noexcept;
		map<char, int> getParamsValues();
		map<char, double> getParamsRealValues();
		PParamsLimits getParamsLimits();
		
		string getStringWithParam(char acronim);
		string getStringWithParams();

		void insert(PParamPair pair);

		bool setParamValue(char acronim, int val);
		
		void setParamsValueByDefaultValue();
    void setParamsValue(int value);
    void setParamsValue(PParamMap &copyParams);
		void setParamsValue(map<char, double> &copyParams);

		void setParamsDefaultValue(int value);
		void setParamsRealLowerLimit(double value);

    bool comparingParamsValue(PParamMap &paramsToComp);
		bool comparingParamsValue(map<char, int> &paramToComp);

    void setParamsBasedString(PString &data);
		void setParamsBasedString(string &data);
		void setParamsBasedString(const char *data);
		
		static PParamsLimits getParamsLimits(PParamMap &param);
		static void setParamsBasedString(PParamMap &param, PString &data);
};

using defOParamListShdPtr=shared_ptr<defOParamList>;

#endif 
