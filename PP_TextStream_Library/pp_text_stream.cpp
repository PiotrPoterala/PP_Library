#include "pp_text_stream.h"


PTextStream& PTextStream::operator<<(int data){
	
	if(IOdevice->mode()==PIOdevice::WriteOnly || IOdevice->mode()==PIOdevice::ReadWrite){
		string str;
		IOdevice->seek(IOdevice->size());
		
		str=to_string(data);
		IOdevice->write(str);
	}
	return (*this);
	
}

PTextStream& PTextStream::operator<<(string &data){
	
	if(IOdevice->mode()==PIOdevice::WriteOnly || IOdevice->mode()==PIOdevice::ReadWrite){
		IOdevice->seek(IOdevice->size());
		IOdevice->write(data);
	}
	return (*this);
	
}

PTextStream& PTextStream::operator<<(const char *data){
	
	if(IOdevice->mode()==PIOdevice::WriteOnly || IOdevice->mode()==PIOdevice::ReadWrite){
		IOdevice->seek(IOdevice->size());
		IOdevice->write(data);
	}
	return (*this);
	
}

PTextStream& PTextStream::operator<<(map<char, int> &values){
	
	if(IOdevice->mode()==PIOdevice::WriteOnly || IOdevice->mode()==PIOdevice::ReadWrite){
		string str;
		
		IOdevice->seek(IOdevice->size());
		
		for(auto it=values.begin(); it!=values.end(); it++){
			str+=(*it).first;
			str+=to_string((*it).second);
			str+=" ";
		}
		
		
		IOdevice->write(str);
	}
	return (*this);
	
}
