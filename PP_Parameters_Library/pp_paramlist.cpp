#include "pp_paramlist.h"


defOParamList::defOParamList(void){

}

defOParamList::defOParamList(const defOParamList &other){
	
	param.insert(other.param.begin(), other.param.end());
	
}

defOParamList::defOParamList(map<char, defOParam*> &copyParams){

    copyListOfParams(copyParams);

}


map<char, defOParam*>* defOParamList::getParams(void){

    return &param;

}

defOParamList* defOParamList::clone() const{
	
	return new defOParamList(*this);
}

defOParam* defOParamList::getParam(char acronim){

  map<char,defOParam*>::iterator it;

	it=param.find(acronim);
	
	if(it!=param.end())return it->second;
	
  return nullptr;
}

pair<char, defOParam*> defOParamList::getParamPair(char acronim){

  map<char,defOParam*>::iterator it;

	it=param.find(acronim);
	
	if(it!=param.end())return pair<char, defOParam*>(it->first, it->second);
	
  return pair<char, defOParam*>('\0', nullptr);
}

int defOParamList::getParamValue(char acronim){
    defOParam* par;
    par=getParam(acronim);
    if(par!=nullptr){
        return par->getValue();
    }
    return 0;
}

map<char, int> defOParamList::getParamsValues(){
	map<char, int> values;
	
	for(map<char,defOParam*>::iterator it=param.begin(); it != param.end(); ++it){
		values.insert(pair<char,int>((*it).first, (*it).second->getValue()));
		
	}
	
	return values;
}

bool defOParamList::setParamValue(char acronim, int val){
    defOParam* par;
    par=getParam(acronim);
    if(par!=nullptr){
        par->setValue(val);
        return true;
    }
    return false;
}

//vector<int>* defOParamList::getParamAllowedValues(char acronim){
//    defOParam* par;
//    par=getParam(acronim);
//    if(par!=NULL){
//        return par->getAllowedValues();
//    }
//    return NULL;
//}

int defOParamList::getParamUpperLimit(char acronim){
    defOParam* par;
    par=getParam(acronim);
    if(par!=nullptr){
        return par->getUpperLimit();
    }
    return 0;
}

void defOParamList::copyListOfParams(map<char, defOParam*> &copyParams){

//	map<char,defOParam*>::iterator it
//	for_each(param.begin(), param.end(), it){
//		x+=1;
//	}
	
    if(param.empty()==false){
			for (map<char,defOParam*>::iterator it=param.begin(); it != param.end(); ++it){
				delete (*it).second;
			}
       param.clear();
    }
		
		param.insert(copyParams.begin(), copyParams.end());
		
//		for (map<char,defOParam*>::iterator it=copyParams.begin(); it != copyParams.end(); ++it){
//			param.push_back(new defOParam(**it));
//		}
		
}

void defOParamList::clearParams(void){

	for(map<char,defOParam*>::iterator it=param.begin(); it!=param.end(); ++it){
		(*it).second->setValue(0);
	}
	
}

void defOParamList::setParamsByValue(int value){

	
	for(map<char,defOParam*>::iterator it=param.begin(); it!=param.end(); ++it){
		(*it).second->setValue(value);
	}
	
}

void defOParamList::setParamsByDefaultValue(){
	
	for(map<char,defOParam*>::iterator it=param.begin(); it!=param.end(); ++it){
		(*it).second->setValue((*it).second->getDefaultValue());
	}
	
}


void defOParamList::setParamsValue(map<char, defOParam*> &copyParams){

	map<char,defOParam*>::iterator it=param.begin();
	map<char,defOParam*>::iterator it_copy=copyParams.begin();
	
	for(; it!=param.end() && it_copy!=copyParams.end(); ++it, ++it_copy){
		(*it).second->setValue((*it_copy).second->getValue());
	}

}



bool defOParamList::comparingParamsValue(map<char, defOParam*> &paramToComp){
    bool same=true;

	map<char,defOParam*>::iterator it_to_comp;
	
	for(map<char,defOParam*>::iterator it=param.begin(); it!=param.end();  ++it){
		it_to_comp=paramToComp.find((*it).first);
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

	map<char,int>::iterator it_to_comp;
	
	for(map<char,defOParam*>::iterator it=param.begin(); it!=param.end();  ++it){
		it_to_comp=paramToComp.find((*it).first);
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


void defOParamList::getParamsFromString(PString *data){
   int val=0;

	for(map<char,defOParam*>::iterator it=param.begin(); it!=param.end(); ++it){
		    val=(*it).second->checkRange(data->findValueAfterAcronim((*it).first, (*it).second->getValue(), (*it).second->getUnit()));
        val-=val%(*it).second->getPrecision();
        (*it).second->setValue(val);
	}
	
	
}

void defOParamList::checksParamsValue(){
	 int val=0;

	for(map<char,defOParam*>::iterator it=param.begin(); it!=param.end(); ++it){
		    val=(*it).second->checkRange((*it).second->getValue());
        val-=val%(*it).second->getPrecision();
        (*it).second->setValue(val);
	}
	
}

