#include "pp_file.h"


PFile::PFile(const string &path){
			
	int find=path.find("/");
	
	if(find!=string::npos){
		volume=path.substr(0, find+1);
		this->path=path.substr(find+1);
	}else{
		volume=path;
		this->path.clear();
	}
}

PFile::PFile(const char* path){
	string newPath=path;	
	
	int find=newPath.find("/");
	
	if(find!=string::npos){
		volume=newPath.substr(0, find+1);
		this->path=newPath.substr(find+1);
	}else{
		volume=path;
		this->path.clear();
	}
		
}



bool PFile::isOpen(){
	
	return openFlag;
	
}

int PFile::pos(){
	
	return position;
}


string PFile::absolutePath(){
	string filePath;
	
	filePath=volume+path;
	return filePath;
}
