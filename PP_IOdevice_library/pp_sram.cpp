#include "pp_sram.h"

PSRam::PSRam(unsigned int firstAdress, unsigned int areaSize){

		this->firstAdress=firstAdress;
		this->areaSize=areaSize;
		this->focusAdress=reinterpret_cast<unsigned int*>(firstAdress);
	
}

bool PSRam::open(OpenMode mode){
		seek(0);
	
		if(mode==WriteOnly){
			clear();
		}
	
		openFlag=true;
		openMode=mode;
	
		return true;
}

bool PSRam::close(){

		openFlag=false;
		return true;
}



int PSRam::size(){
	

	return areaSize;
	
}

int PSRam::pos(){
	
	return (reinterpret_cast<unsigned int>(focusAdress)-firstAdress)/sizeof(unsigned int);
	
}


bool PSRam::atEnd(){
	
		if(areaSize<=pos())return true;
		
		return false;	
}



bool PSRam::seek(int pos){
	
	if(pos<areaSize){
		focusAdress=reinterpret_cast<unsigned int*>(firstAdress);

		focusAdress+=pos;
		
		return true;
	}
	
	return false;
	
}

int PSRam::read(){

	return *(focusAdress++);
}


bool PSRam::write(int value){

	if(!atEnd()){
		*(focusAdress++)=value;
		return true;
	}
	return false;
}



bool PSRam::clear(){		

	seek(0);
	memset(reinterpret_cast<unsigned int*>(firstAdress), 0, sizeof(unsigned int)*areaSize);
	return true;
}








