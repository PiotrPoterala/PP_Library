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


bool PDir::cd(const string &dirName){
	
		if(dirName.compare("..")==0){
			return cdUp();
		}else{
			
			if(exists(dirName)){
				
				dirPath+="/";
				dirPath+=dirName;
				return true;
			}
		}
	
		return false;
}

bool PDir::cdUp(){
		string path=absolutePath();
		string newDirName;
	
		path.substr(0, path.find_last_of("/"));
		newDirName=path.substr(path.find_last_of("/")+1);
	
		if(exists(newDirName)){
			setPath(path);
			return true;
		}
	
		return false;
	
}


void PDir::setPath(const string &path){


	int find=path.find("/");
	volume=path.substr(0, find+1);
	dirPath=path.substr(find+1);


};