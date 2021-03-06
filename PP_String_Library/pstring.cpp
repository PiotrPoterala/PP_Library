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
                if((at(i)>='0' && at(i)<='9') || at(i)=='-' || at(i)=='+' || at(i)=='.'){
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
	
	if(base==16){
    for (int i=0; i<size(); i++) {
        if (at(i)>=48 && at(i)<=57){
            result =result*16+(at(i)-48);
        }else if(at(i)>=65 && at(i)<=70) {
            result =result*16+(at(i)-55);
        }else if(at(i)>=97 && at(i)<=102) {
            result =result*16+(at(i)-87);
        }
    }
	}else if(base==10){
		
		result=atoi(c_str());
	}
	
	return result;
}

double PString::findValueAfterAcronim(char acronim, double defValue){
        string line=findDataAfterAcronim(acronim);
        if(line.empty())return defValue;
				
				return atof( line.c_str());
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

vector<string> PString::splitWithClamps(char sep, char clamps){
				vector<string> stringList;
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