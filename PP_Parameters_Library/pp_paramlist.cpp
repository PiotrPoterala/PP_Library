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

#include "pp_paramlist.h"


defOParamList::defOParamList(void){

}

defOParamList::defOParamList(const defOParamList &other){
	
	param.insert(other.param.begin(), other.param.end());
	
}

defOParamList::defOParamList(const PParamMap &copyParams){

    copyListOfParams(copyParams);

}

defOParamList& defOParamList::operator=(const defOParamList& other){
		
	copyListOfParams(other.param);
	return (*this);
}

defOParamList::~defOParamList(){
	
	clear();
	
}

void defOParamList::clear(){
	
		 if(param.empty()==false){
			for (auto it=param.begin(); it != param.end(); ++it){
				delete (*it).second;
			}
       param.clear();
    }	
}




defOParamList* defOParamList::clone() const{
	
	return new defOParamList(*this);
}

PParamMap* defOParamList::getParams(void){

    return &param;

}

bool defOParamList::exists(char acronim){
	
	auto it=param.find(acronim);
	
	if(it!=param.end())return true;
	
  return false;
	
}


void defOParamList::insert(pair<char, defOParamGeneral*> data){
	
	param.insert(data);
	
}

defOParamGeneral* defOParamList::getParam(char acronim){


	auto it=param.find(acronim);
	
	if(it!=param.end())return it->second;
	
  return nullptr;
}

pair<char, defOParamGeneral*> defOParamList::getParamPair(char acronim){

	auto it=param.find(acronim);
	
	if(it!=param.end())return pair<char, defOParamGeneral*>(it->first, it->second);
	
  return pair<char, defOParamGeneral*>('\0', nullptr);
}

int defOParamList::getParamValue(char acronim){
    defOParamGeneral* par;
    par=getParam(acronim);
    if(par!=nullptr){
        return par->getValue();
    }
    return 0;
}

map<char, int> defOParamList::getParamsValues(){
	map<char, int> values;
	
	for(auto it=param.begin(); it != param.end(); ++it){
		values.insert(pair<char,int>((*it).first, (*it).second->getValue()));
		
	}
	
	return values;
}

bool defOParamList::setParamValue(char acronim, int val){
    defOParamGeneral* par;
    par=getParam(acronim);
    if(par!=nullptr){
        par->setValue(val);
        return true;
    }
    return false;
}

int defOParamList::getParamUnit(char acronim){
    defOParamGeneral* par;
    par=getParam(acronim);
    if(par!=nullptr){
        return par->getUnit();
    }
    return 0;
}


int defOParamList::getParamUpperLimit(char acronim){
    defOParamGeneral* par;
    par=getParam(acronim);
    if(par!=nullptr){
        return par->getUpperLimit();
    }
    return 0;
}

int defOParamList::getParamPrecision(char acronim){
    defOParamGeneral* par;
    par=getParam(acronim);
    if(par!=nullptr){
        return par->getPrecision();
    }
    return 0;
}

//int defOParamList::checkRange(char acronim, int val){
//	
//	  defOParamGeneral* par;
//    par=getParam(acronim);
//    if(par!=nullptr){
//        return par->checkRange(val);
//    }
//    return 0;
//	
//}


void defOParamList::copyListOfParams(const PParamMap &copyParams){

//	map<char,defOParam*>::iterator it
//	for_each(param.begin(), param.end(), it){
//		x+=1;
//	}
	
    clear();
		param.insert(copyParams.begin(), copyParams.end());
		
//		for (map<char,defOParam*>::iterator it=copyParams.begin(); it != copyParams.end(); ++it){
//			param.push_back(new defOParam(**it));
//		}
		
}

void defOParamList::setParamsByZero(void){

	for(auto it=param.begin(); it!=param.end(); ++it){
		(*it).second->setValue(0);
	}
	
}

void defOParamList::setParamsByValue(int value){

	
	for(auto it=param.begin(); it!=param.end(); ++it){
		(*it).second->setValue(value);
	}
	
}

void defOParamList::setParamsByDefaultValue(){
	
	for(auto it=param.begin(); it!=param.end(); ++it){
		(*it).second->setValue((*it).second->getDefaultValue());
	}
	
}


void defOParamList::setParamsValue(PParamMap &copyParams){

	auto it=param.begin();
	
	for(auto it=param.begin(); it!=param.end();  ++it){
		auto it_copy=copyParams.find((*it).first);
		if(it_copy!=copyParams.end()){
			(*it).second->setValue((*it_copy).second->getValue());
		}
		
	}

}

void defOParamList::setParamsValue(map<char, double> &copyParams){

	auto it=param.begin();
	
	for(auto it=param.begin(); it!=param.end();  ++it){
		auto it_copy=copyParams.find((*it).first);
		if(it_copy!=copyParams.end()){
			(*it).second->setValue((*it_copy).second*pow(10.0, (*it).second->getUnit()));
		}
		
	}

}



bool defOParamList::comparingParamsValue(PParamMap &paramToComp){
    bool same=true;


	for(auto it=param.begin(); it!=param.end();  ++it){
		auto it_to_comp=paramToComp.find((*it).first);
		if(it_to_comp!=paramToComp.end()){
			if((*it).second->getValue()!=(*it_to_comp).second->getValue()){
					same=false;
					break;
			}
		}else{
			same=false;
			break;
		}
	}
    return same;

}

bool defOParamList::comparingParamsValue(map<char, int> &paramToComp){
    bool same=true;
	
	for(auto it=param.begin(); it!=param.end();  ++it){
		auto it_to_comp=paramToComp.find((*it).first);
		if(it_to_comp!=paramToComp.end()){
			if((*it).second->getValue()!=(*it_to_comp).second){
					same=false;
					break;
			}
		}else{
			same=false;
			break;
		}
	}
    return same;

}


void defOParamList::setParamsBasedString(PString &data){

	for(auto it=param.begin(); it!=param.end(); ++it){
		    (*it).second->setValue(data.findValueAfterAcronim((*it).first, static_cast<double>((*it).second->getValue())/pow(10.0, (*it).second->getUnit()))*pow(10.0, (*it).second->getUnit()));
	}
	
	
}

//void defOParamList::checksParamsValue(){
//	 int val=0;

//	for(auto it=param.begin(); it!=param.end(); ++it){
//		    val=(*it).second->checkRange((*it).second->getValue());
//        val-=val%(*it).second->getPrecision();
//        (*it).second->setValue(val);
//	}
//	
//}

string defOParamList::getStringWithParams(){
	
	string answer;
	auto it_last_elem=param.end();
	
	it_last_elem--;
	
		for (auto i=param.begin(); i!=param.end(); i++) {
				answer+=(*i).first;  
				answer+=to_string(static_cast<double>((*i).second->getValue())/pow(10.0, (*i).second->getUnit())); 
				if(i!=it_last_elem)answer+=" ";
		}
	
	return answer;
}

