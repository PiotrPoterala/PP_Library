#include "pp_file_string_mock.h"

int PFileStringMock::size(){

	return file.size();
	
}

bool PFileStringMock::atEnd(){
	
	if(position>=size())return true;
	
	return false;
	
}


bool PFileStringMock::open(OpenMode mode){
		int fresult;

		if(mode==WriteOnly){
			file.clear();
		}

		openFlag=true;
		openMode=mode;
		seek(0);
		return true;

}

bool PFileStringMock::close(){

		return true;

}

bool PFileStringMock::seek(int pos){
	
	position=pos;
	return true;

	
}

bool PFileStringMock::write(const char *data){

		file.insert(position, data);
		position+=strlen(data);
		return true;


}

bool PFileStringMock::write(string &data){

		return write(data.c_str());

}

bool PFileStringMock::write(int data){
		int writeChars=0;
		string str=to_string(data);
	
		return write(str.c_str());

}

bool PFileStringMock::writeAtTheEnd(const char *data){
		bool result=false;
	
		if(seek(size())){
			result=write(data);
		}

		return result;

}

bool PFileStringMock::writeAtTheEnd(string &data){

		return writeAtTheEnd(data.c_str());

}

bool PFileStringMock::writeAtTheEnd(int data){
		string str=to_string(data);

		return writeAtTheEnd(str.c_str());
	
}



string PFileStringMock::read(int maxSize){

	
		return file.substr(position);


};

int PFileStringMock::read(char *data, int maxSize){
		unsigned int readBytes=0;
	
		if(position<size()){
			strncpy(data, file.substr(position).c_str(), maxSize);	
			readBytes=strlen(data);
			position+=readBytes;			
		}

		return readBytes;

};

string PFileStringMock::readLine(){
		constexpr int buforSize=64;
	
		unsigned int readBytes=buforSize;
		string bufor;
		string result;
		bool isEndSign=false;


		if(position<size()){

			while(isEndSign==false && readBytes==buforSize){
				bufor=file.substr(position, buforSize);	//pobranie n bajtów (wartość wskazywana przez ) z danego fileu i zapisanie ich do bufora  		
				readBytes=bufor.size();
				
				for(int i=0; i<readBytes; i++){
					if(bufor.at(i)=='\n'){
						bufor.erase(i+1);
						isEndSign=true;
						break;
					}
				}
				result+=bufor;
				position+=bufor.size();
						
			}
		}

		
		return result;
}


bool PFileStringMock::clear(){
	
		file.clear();
		return true;
	
}
