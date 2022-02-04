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

string PFile::absolutePath(){
	string filePath;
	
	filePath+=volume;
	filePath+=path;
	return filePath;
}

bool PFile::open(OpenMode mode){
		int fresult;
		int fmode=FA_OPEN_ALWAYS;

		if(mode==ReadOnly){
			fmode=FA_READ;
		}else if(mode==WriteOnly){
			fmode=FA_WRITE | FA_CREATE_ALWAYS;
		}else if(mode==ReadWrite){	
			fmode=FA_WRITE | FA_READ;
		}

			fresult=f_mount(&g_sFatFs, volume.c_str(), 1);
			if(fresult==FR_OK){
				fresult=f_open(&file, absolutePath().c_str(), fmode);
			}
		
			if(fresult==FR_OK){
				openFlag=true;
				openMode=mode;
				position=0;
				return true;
			}
			return false;

}

bool PFile::close(){
		int fresult;

			fresult=f_close(&file);
			if(fresult==FR_OK)fresult=f_mount(0, volume.c_str(), 1);


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

bool PFile::write(string &data){
		int writeChars=0;

		writeChars=f_puts(data.c_str(), &file);
		if(writeChars>0){
			position+=writeChars;
			return true;
		}
		return false;

}

bool PFile::write(const char *data){
		int writeChars=0;

		writeChars=f_puts(data, &file);

		if(writeChars>0){
			position+=writeChars;
			return true;
		}
		return false;

}

bool PFile::writeAtTheEnd(string &data){
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

//PFile& PFile::operator<<(const char *data){
//	
//		if(open(FA_WRITE)){
//			writeAtTheEnd(data);
//			close();
//		}
//		return (*this);
//}


string PFile::read(int maxSize){
		constexpr int buforSize=64;
	
		unsigned int readBytes=buforSize;
		unsigned int bytesToGet=maxSize;
		unsigned int sizeToRead=0;
		char bufor[buforSize];
		string result;


		if(position<file.obj.objsize){

			while(bytesToGet>0){
				f_lseek(&file, position);
				if(bytesToGet<buforSize){
					sizeToRead=bytesToGet;		
				}else{
					sizeToRead=buforSize;	 	
				}
				f_read(&file, bufor, sizeToRead, &readBytes);	//pobranie n bajtów (wartość wskazywana przez ) z danego fileu i zapisanie ich do bufora  
				bytesToGet-=readBytes;
				position+=readBytes;
				result+=bufor;		
				if(sizeToRead!=readBytes)break;
			}
		}

		
		return result;


};

int PFile::read(char *data, int maxSize){
		unsigned int readBytes=0;
	
		if(position<file.obj.objsize){
			f_lseek(&file, position);
			f_read(&file, data, maxSize, &readBytes);	//pobranie n bajtów (wartość wskazywana przez ) z danego fileu i zapisanie ich do bufora  		
			position+=readBytes;			
		}

		return readBytes;

};

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
						position+=(i+1);
					}
				}

				result+=bufor;		
			}
		}

		
		return result;
}

bool PFile::exists(){
		FILINFO fno;
		int fresult=FR_OK;
		bool objectExist=false;
	
		fresult=f_mount(&g_sFatFs, volume.c_str(), 1);
	
		if(fresult==FR_OK){
			fresult=f_stat(path.c_str(), &fno);
	
			if(fresult==FR_OK && !(fno.fattrib & AM_DIR)){
					objectExist=true;
			}
			f_mount(0, volume.c_str(), 1);
		}
		
		return objectExist;
	
}

bool PFile::clear(){
		int fresult;

	
		fresult=f_mount(&g_sFatFs, volume.c_str(), 1);
		if(fresult==FR_OK){
			fresult=f_open(&file, absolutePath().c_str(), FA_CREATE_ALWAYS);
		}
	
		if(fresult==FR_OK){
			close();
			return true;
		}
		return false;
	
}
