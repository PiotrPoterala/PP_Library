#include "pp_file.h"


PFile::PFile(const string &path){
			
		setPath(path);
}

PFile::PFile(const char* path){
	
		setPath(path);
		
}

void PFile::setPath(const string &path){


	int find=path.find("/");
	
	if(find!=string::npos){
		volume=path.substr(0, find+1);
		this->path=path.substr(find+1);
	}else{
		volume=path;
		this->path.clear();
	}

};


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

void PFile::setFileName(const string &path){
	
		if(isOpen()){
			close();
		}
	
		setPath(path);
}

void PFile::setFileName(const char* path){
	
		if(isOpen()){
			close();
		}
	
		setPath(path);
}