#include "pp_time.h"


PTime::PTime(int h, int m, int s){
	
	if(h>=0)hr=h; else hr=0;
	if(m>=0 && m<60)min=m; else min=0;
	if(s>=0 && s<60)sec=s; else sec=0;
	
}

void PTime::reset(){
	hr=0;
	min=0;
	sec=0;
}

void PTime::addSec(int s){
	
	setHMS(toSec()+s);
	
}
	
int	PTime::hour() const{
	return hr;
}

int	PTime::minute() const{
	return min;
}

int	PTime::second() const{
	return sec;
}


bool PTime::setHMS(int s){

	if(s>=0){
    sec=s%60;
    min=(s/60)%60;
    hr=(s/3600)%24;
		return true;
	}
	return false;
}

bool PTime::setHMS(int h, int m, int s){

	if(h>=0 && m>=0 && m<60 && s>=0 && s<60){
		hr=h; 
		min=m; 
		sec=s;
		return true;
	}
	return false;
}



int PTime::toSec() const{
	
		return (sec+(min*60)+(hr*3600));
}

string	PTime::toString() const{
		char buffer [50];
		sprintf (buffer, "%04u:%02u:%02u", hr, min, sec);
	
		return buffer;
}

bool	PTime::operator!=(const PTime &t) const{
	
		if(toSec()!=t.toSec())return true;
	
		return false;	
}

bool	PTime::operator<(const PTime &t) const{
	
	if(toSec()<t.toSec())return true;
	
	return false;
}

bool PTime::operator<=(const PTime &t) const{
	
	if(toSec()<=t.toSec())return true;
	
	return false;
}

bool PTime::operator==(const PTime &t) const{
	
	if(toSec()==t.toSec())return true;
	
	return false;
}

bool PTime::operator>(const PTime &t) const{
	
	if(toSec()>t.toSec())return true;
	
	return false;
}

bool PTime::operator>=(const PTime &t) const{
	
	if(toSec()>=t.toSec())return true;
	
	return false;
}

void PTime::operator+(const PTime &t){
	
	setHMS(toSec()+t.toSec());
	
}
