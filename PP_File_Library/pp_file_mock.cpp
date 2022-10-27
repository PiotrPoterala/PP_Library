#include "pp_file_mock.h"

int PFileMock::size(){

		file.seekg( 0, file.end);
    auto fsize = file.tellg();
		seek(position);
	
	return fsize;
	
}

bool PFileMock::atEnd(){
	
	if(position>=size())return true;
	
	return false;
	
}


bool PFileMock::open(OpenMode mode){
		int fresult;
		auto fmode=fstream::out | fstream::trunc ;

		if(mode==ReadOnly){
			fmode=fstream::in;
		}else if(mode==WriteOnly){
			fmode=fstream::out | fstream::trunc;
		}else if(mode==ReadWrite){	
			fmode=fstream::out | fstream::in;
		}

		file.open(absolutePath().c_str(), fmode);

		if(file.is_open()){
			openFlag=true;
			openMode=mode;
			seek(0);
			return true;
		}
		return false;

}

bool PFileMock::close(){
			file.close();
			if(file.fail()==false){
				openFlag=false;
				return true;
			}
			return false;
}

bool PFileMock::seek(int pos){
	
	position=pos;
	file.seekg(position);
	
	if(file.fail()==false) return true;
	return false;
	
}

bool PFileMock::write(string &data){

		file.write(data.c_str(), data.size());
		if(file.fail()==false){
			position+=data.size();
			return true;
		}
		return false;

}

bool PFileMock::write(const char *data){
		int writeChars=0;

		while(*data){
			file.put(*(data++));
			writeChars++;
		}

		if(writeChars>0){
			position+=writeChars;
			return true;
		}
		return false;

}

bool PFileMock::writeAtTheEnd(string &data){
		bool result=false;
	
		if(seek(size())){
			result=write(data);
		}

		return result;

}

bool PFileMock::writeAtTheEnd(const char *data){
		bool result=false;
	
		if(seek(size())){
			result=write(data);
		}

		return result;

}


string PFileMock::read(int maxSize){
		constexpr int buforSize=64;
	
		unsigned int readBytes=0;
		unsigned int bytesToGet=maxSize;
		unsigned int sizeToRead=0;
		char bufor[buforSize];
		string result;


		if(position<size()){

			while(bytesToGet>0){
				seek(position);
				if(bytesToGet<buforSize){
					sizeToRead=bytesToGet;		
				}else{
					sizeToRead=buforSize;	 	
				}
				file.read(bufor, sizeToRead);	//pobranie n bajtów (wartość wskazywana przez ) z danego fileu i zapisanie ich do bufora  
				readBytes=strlen(bufor);
				bytesToGet-=readBytes;
				position+=readBytes;
				result+=bufor;		
				if(sizeToRead!=readBytes)break;
			}
		}

		
		return result;


};

int PFileMock::read(char *data, int maxSize){
		unsigned int readBytes=0;
	
		if(position<size()){
			seek(position);
			file.read(data, maxSize);	
			position+=strlen(data);			
		}

		return readBytes;

};

string PFileMock::readLine(){
		constexpr int buforSize=64;
	
		unsigned int readBytes=buforSize;
		char bufor[buforSize];
		string result;
		bool isEndSign=false;


		if(position<size()){

			while(isEndSign==false && readBytes==buforSize){
				seek(position);
				file.read(bufor, buforSize);	//pobranie n bajtów (wartość wskazywana przez ) z danego fileu i zapisanie ich do bufora  		
		
				
				for(int i=0; i<readBytes; i++){
					if(bufor[i]=='\n'){
						if(i+1<buforSize)bufor[i+1]='\0';
						isEndSign=true;
						break;
					}
				}
				result+=bufor;
				position+=strlen(bufor);
						
			}
		}

		
		return result;
}


bool PFileMock::clear(){
	
		if(open(WriteOnly)){
			close();
			return true;
		}
		return false;
	
}
