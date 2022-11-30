#include "pp_file_info.h"


PFileInfo::PFileInfo(PFile &file){
	
	setPath(file.absolutePath());
}


PFileInfo::PFileInfo(const string &path){
	
	setPath(path);
}

PFileInfo::PFileInfo(const char* path){
	
	setPath(path);
}

void PFileInfo::setFile(PFile &file){
	setPath(file.absolutePath());
}

void PFileInfo::setFile(const string &path){
	setPath(path);
}

void PFileInfo::setFile(const char* path){
	setPath(path);
}	



void PFileInfo::setPath(const string &path){

	int find=path.find("/");
	
	if(find!=string::npos){
		volume=path.substr(0, find+1);
		filePath=path.substr(find+1);
	}else{
		volume=path;
		filePath.clear();
	}

}
	
string PFileInfo::absoluteFilePath() const{
	
	return (volume+filePath);
	
}

string PFileInfo::absolutePath() const{
	string path=absoluteFilePath() ;
	
	return (path.substr(0, path.find_last_of("/")));
	
}

string PFileInfo::fileName() const{
	string path=absoluteFilePath() ;
	
	return path.substr(path.find_last_of("/")+1);
}