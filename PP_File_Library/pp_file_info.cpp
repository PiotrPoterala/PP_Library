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
	volume=path.substr(0, find+1);
	filePath=path.substr(find+1);

};
	
string PFileInfo::absoluteFilePath() const{
	
	return (volume+filePath);
	
}

string PFileInfo::absolutePath() const{
	
	return (volume+filePath.substr(0, filePath.find_last_of("/")));
	
}

string PFileInfo::fileName() const{
	
	return filePath.substr(filePath.find_last_of("/")+1);
}