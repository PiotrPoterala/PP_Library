#include "pp_flash.h"


PFlash::PFlash(FlashAreaDescList &page){

		pages=page;
	
		focusReadAdress=reinterpret_cast<unsigned int*>(pages.begin()->firstAdress);
		focusWriteAdress=focusReadAdress;

}

PFlash::PFlash(initializer_list<FlashPage> page){
	
	pages=page;
	
	focusReadAdress=reinterpret_cast<unsigned int*>(pages.begin()->firstAdress);
	focusWriteAdress=focusReadAdress;
}


int PFlash::size(){
	
	int area=0;
	
	for(auto&& page: pages){
		area+=page.areaSize;
		
	}
	
	return area;
}

int PFlash::pos(){
	
	if(pages.empty()==false){
		auto firstPage=pages.begin();
		
		return (reinterpret_cast<unsigned int>(focusReadAdress)-firstPage->firstAdress)/sizeof(unsigned int);
	}
	
	return 0;
}

bool PFlash::atEnd(){
	
	if(pages.empty()==false){
		auto p=pages.end()-1;
		
		if(size()<=pos())return true;
		
		return false;	
	}
	return true;
}



bool PFlash::open(OpenMode mode){

		seek(0);
	
		if(mode==WriteOnly || mode==ReadWrite){
			clear();
		}
	
		openFlag=true;
		openMode=mode;
	
		return true;
}

bool PFlash::close(){

		openFlag=false;
		return true;
}

bool PFlash::seek(int pos){
	
	if(pos<size()){
		auto p=pages.begin();
		
		focusReadAdress=reinterpret_cast<unsigned int*>(p->firstAdress);
		focusReadAdress+=pos;
		
		return true;
	}
	
	return false;
}

int PFlash::read(){
	return *(focusReadAdress++);
}


bool PFlash::writeAtTheEnd(int data){

	focusReadAdress=focusWriteAdress;
		if(!atEnd()){
			*(focusWriteAdress++)=data;
			focusReadAdress=focusWriteAdress;
			return true;
		}
		return false;
}

bool PFlash::clear(){		

	seek(0);
	focusWriteAdress=focusReadAdress;
	
	if(pages.empty()==false){
		auto firstPage=pages.begin();
		memset(reinterpret_cast<unsigned int*>(firstPage->firstAdress), 0, sizeof(unsigned int)*size());
	}

	return true;

}
