#include "pp_file.h"


PFile::PFile(PVolume *volume, const char* path){

		this->volume=volume;
		this->path=path;

}	



bool PFile::isOpen(){
	
	return openFlag;
	
}

int PFile::size(){
	
	return file.obj.objsize;
	
}

int PFile::pos(){
	
	return position;
}

bool PFile::atEnd(){
	
	if(position>=file.obj.objsize)return true;
	
	return false;
	
}

bool PFile::open(int mode){
		int fresult;
		string filePath;

			fresult=f_mount(&volume->g_sFatFs, &volume->volume, 1);
			if(fresult==FR_OK){
				filePath+=volume->volume;
				filePath+=":";
				filePath+=path;
				fresult=f_open(&file, filePath.c_str(), mode);
			}
		
			if(fresult==FR_OK){
				openFlag=true;
				position=0;
				return true;
			}
			return false;

}

bool PFile::close(){
		int fresult;

			fresult=f_close(&file);
			if(fresult==FR_OK)fresult=f_mount(0, &volume->volume, 1);


			if(fresult==FR_OK){
				openFlag=false;
				return true;
			}
			return false;
}

bool PFile::seek(int pos){
	int fresult;
	position=pos;
	fresult=f_lseek(&file, position);
	
	if(fresult==FR_OK) return true;
	return false;
	
}

bool PFile::write(string *data){
		int fresult;

		fresult=f_puts(data->c_str(), &file);

		if(fresult==FR_OK) return true;
		return false;

}

bool PFile::write(const char *data){
		int fresult;

		fresult=f_puts(data, &file);

		if(fresult==FR_OK) return true;
		return false;

}

bool PFile::writeAtTheEnd(string *data){
		bool result=false;
	
		if(seek(file.obj.objsize)){
			result=write(data);
		}

		return result;

}

bool PFile::writeAtTheEnd(const char *data){
		bool result=false;
	
		if(seek(file.obj.objsize)){
			result=write(data);
		}

		return result;

}

PFile& PFile::operator<<(const char *data){
	
		if(open(FA_WRITE)){
			writeAtTheEnd(data);
			close();
		}
		return (*this);
}


string PFile::readLine(){
		constexpr int buforSize=64;
	
		int fresult, i;
		unsigned int readBytes=buforSize;
		char bufor[buforSize];
		string result;
		bool isEndSign=false;


		if(position<file.obj.objsize){

			while(isEndSign==false && readBytes==buforSize){
				f_lseek(&file, position);
				f_read(&file, bufor, buforSize, &readBytes);	//pobranie n bajtów (wartość wskazywana przez ) z danego fileu i zapisanie ich do bufora  		

				
				for(i=0; bufor[i]!='\0' && i<buforSize; i++){
					if(isEndSign)bufor[i]='\0'; 
					if(bufor[i]=='\n'){
						isEndSign=true;
						position+=i;
					}
				}

				result+=bufor;		
			}
		}

		
		return result;
}

bool PFile::clear(){
		bool result=false;
	
		if(open(FA_CREATE_ALWAYS)){
			result=close();
		}
		
		return result;
}
