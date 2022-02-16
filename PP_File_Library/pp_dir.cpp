#include "pp_dir.h"

PDir::PDir(const string &path){
			
		setPath(path);
}

PDir::PDir(const char* path){
	
	setPath(path);
		
}

		
string PDir::absoluteFilePath(const string &fileName) const{
	
	return (volume+dirPath+"/"+fileName);
	
}
	
	
string PDir::absolutePath() const{
	
	return (volume+dirPath);
	
}


string	PDir::dirName() const{
		string path=absolutePath();
	
		return path.substr(path.find_last_of("/")+1);
	
}

void PDir::setPath(const string &path){


	int find=path.find("/");
	volume=path.substr(0, find+1);
	dirPath=path.substr(find+1);


};