#include "pstring.h"
#include "math.h"


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


double PString::toDouble(bool *ok){
		uint32_t character=0;
		bool comma=false;
		int decimal_place=0;
		int32_t znak=1;
		double result=0;

		for(uint32_t i=0; i<size(); i++){
			character=charToInt(at(i));
			if(character==ZNAK_MINUS && i==0)znak=(-1);
			else if(character==ZNAK_PLUS && i==0)znak=1;
			else if(character<=9 || character==KROPKA){
				if(character==KROPKA){
					if(comma==true){
						if(ok!=NULL)*ok=false;
						return 0;
					}else{
						comma=true;
					}
				}else{
					if(comma==false){
						result=result*10+character;	
					}else{
							decimal_place++;
							result+=(static_cast<double>(character)/(pow(10.0, decimal_place)));	
					}
						
				}
			}else{
				if(ok!=NULL)*ok=false;
				return 0;
			}
		}
		result*=znak;
		if(ok!=NULL)*ok=true;
		return result;
}

uint32_t PString::toInt(bool *ok){
		bool success=false;
		double result=toDouble(&success);
	
		if(success==true){
			if(ok!=NULL)*ok=true;
			return static_cast<uint32_t>(result);
		}else{
			if(ok!=NULL)*ok=false;
			return 0;
		}
}

uint32_t PString::charToInt(char sign){
		
		switch(sign){
					case '-':	return ZNAK_MINUS;
					case '+':	return ZNAK_PLUS;	
					case '0':	return 0;					
					case '1':	return 1;
					case '2':	return 2;
					case '3':	return 3;
					case '4':	return 4;
					case '5':	return 5;
					case '6':	return 6;
					case '7':	return 7;
					case '8':	return 8;
					case '9':	return 9;
					case 'A':	return 10;
					case 'B':	return 11;
					case 'C':	return 12;
					case 'D':	return 13;
					case 'E':	return 14;
					case 'F':	return 15;
					case '.':	return KROPKA;
					case ',':	return KROPKA;
					default: return SIGN_NULL;
				}
}

double PString::findValueAfterAcronim(char acronim, int defValue, int precision){
        uint32_t i=0;
        PString line=PString();
        double value=0;

				i=find(acronim);

				if(i!=string::npos){
            i++;
            for(uint32_t j=0; j<size(); j++){
                if((at(i)>='0' && at(i)<='9') || at(i)=='-' || at(i)=='+' || at(i)=='.'){
                    line+=at(i);
                    i++;
                }else break;

            }
        }
        if(line.empty())return defValue;

        if(precision>0){
            double val=0;
            val=line.toDouble();

            value=static_cast<int>(val*pow(10.0, precision));
        }else{
            value=line.toInt();
        }

        return value;
}

vector<string> PString::split(char sep){
    int j=0;
		vector<string> stringList;
		string data;
  
    for(uint32_t i=0; i<size(); i++){

        if(at(i)==sep){
          j++;
					stringList.push_back(data);
          data.clear();
        }else {
            data+=at(i);
        }
      
    }
    
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
                        num_char=0;
                        stringList.push_back(data);
                        data.clear();
                    }
                }else if(getData){
                    data+=at(i);
                }


        }


        return stringList;
}
