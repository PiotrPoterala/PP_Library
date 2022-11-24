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

#include "pstring.h"
#include "pp_math.h"
#include <iostream>

PString::PString():string ()
{

}

PString::PString(const string &s):string (s)
{

}

PString::PString(const char* s):string (s)
{

}



PString::PString(string &str):string (str)
{

}


string PString::findDataAfterAcronim(char acronim){
        int i=0;
        string line;

				i=find(acronim);

				if(i!=string::npos){
            for(i=i+1; i<size(); i++){
                if(isdigit(at(i)) || at(i)=='-' || at(i)=='+' || at(i)=='.'){
                    line+=at(i);
                }else break;

            }
        }


        return line;
}

PString PString::mid(int position, int n){
	
	return substr(position, n);
}

int PString::toInt(int base){
	int result=0;
	
	if(base!=16 && base!=10 && base!=2)base=10;
	
	if(base==16){
		if(isalnum(at(0)))result=stoi(data(), nullptr, base);
	}else{
		if(isdigit(at(0)))result=stoi(data(), nullptr, base);
	}
	
	return result;
		
}

double PString::toDouble(){
		int result=0;
		if(isdigit(at(0)))result=stod(data());
	
		return result;

}

double PString::findValueAfterAcronim(char acronim, double defValue){
        string line=findDataAfterAcronim(acronim);
        if(line.empty())return defValue;
				
				return stod(line);
}

map<char, double> PString::findValuesAfterAcronims(){
				string data;
				map<char, double> valuesMap;
	
				for(int i='a'; i<'z'; i++){
					data=findDataAfterAcronim(i);
					if(!data.empty())valuesMap.insert(pair<char, double>(i, atof(data.c_str())));
				}

				for(int i='A'; i<'Z'; i++){
					data=findDataAfterAcronim(i);
					if(!data.empty())valuesMap.insert(pair<char, double>(i, atof(data.c_str())));
				}
				
        return valuesMap;
}


PString& PString::trimmed(){
	
	int i=0;
	
	for(i=0; i<size(); i++){
		if(!isspace(at(i)))break;
	}
	erase(0, i);

	return trimmedRight();
}

PString& PString::trimmedRight(){
	
	int i=0;
	
	for(i=size()-1; i>=0; i--){
		if(!isspace(at(i)))break;
	}
	
	if(i<size()-1)erase(i+1);

	return (*this);
}


vector<PString> PString::split(char sep, SplitBehavior behavior){
		vector<PString> stringList;
		PString data;
  
    for(int i=0; i<size(); i++){
        if(at(i)==sep){
					if(behavior==KeepEmptyParts || (!data.empty()))stringList.push_back(data);
          data.clear();
        }else {
            data+=at(i);
        }
      
    }
    
		if(!data.empty())stringList.push_back(data);
		
    return stringList;
}

StringList PString::splitWithClamps(char sep, char clamps){
				StringList stringList;
				string data;
        bool getData=false;
        int num_char=0;

        for(int i=0; i<size(); i++){

                if(at(i)==sep){
                    num_char=0;
                }else if(at(i)==clamps){
                    num_char++;
                    if(num_char==1)getData=true;
                    else if(num_char==2){
                        getData=false;
                        stringList.push_back(data);
                        data.clear();
                    }
                }else if(getData){
                    data+=at(i);
                }


        }


        return stringList;
}

string PString::doubleToString(double doubleToStr, int unit){
		string str;
		
		if(unit<0){
			str=to_string(doubleToStr);
		}else if(unit>0){
			char format[20];
			char str_c[50];
			int data=doubleToStr*pow_pp(10, unit);
			int unitToDisplay;
			
			for(unitToDisplay=unit; unitToDisplay>0; unitToDisplay--){
				if(data%10)break;
				data/=10;
			}
			if(data<0)sprintf(format, "-%%i.%%0%ii", unitToDisplay);
			else sprintf(format, "%%i.%%0%ii", unitToDisplay);
			
			sprintf(str_c, format, abs(data)/pow_pp(10, unitToDisplay), abs(data)%pow_pp(10, unitToDisplay));
			str=str_c;
		}else{
			str=to_string(static_cast<int>(doubleToStr));
		}

		return str;
}