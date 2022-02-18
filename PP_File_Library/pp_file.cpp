#include "pp_file.h"


PFile::PFile(const string &path){
			
	int find=path.find("/");
	volume=path.substr(0, find+1);
	this->path=path.substr(find+1);
		
}

PFile::PFile(const char* path){
	string newPath=path;	
	
	int find=newPath.find("/");
	volume=newPath.substr(0, find+1);
	this->path=newPath.substr(find+1);
		
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
