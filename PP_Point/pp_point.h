/**
 * @author  Piotr Poterała
 * @email   poterala.piotr@gmail.com
 * @website http://zappp.pl
 * @version v1.0
 * @ide     Keil uVision 5
 * @license GNU GPL v3
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Piotr Poterała, 2021
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */

#ifndef _PP_POINT_H
	#define _PP_POINT_H

	#include <map>
	#include <type_traits>
	
	#include "pstring.h"
	

template <typename Type>
	class PPpoint{
		
		public:
			static_assert	(std::is_arithmetic<Type>::value, "<Type> must be integral or a floating point type");
		
		map<char, Type> axes;	
		
		PPpoint(){};
		PPpoint(map<char, Type> point){axes=point;};
	
			
		PPpoint<Type>& operator=(const PPpoint &point){

			axes=point.axes;
			return (*this);

		};		
			
		
		PPpoint<Type>& operator=(const map<char, Type> point){

			axes=point;
			return (*this);

		};	
		
		
		bool operator==(PPpoint &point){
			if(axes.size()==point.axes.size()){
				for(auto it=axes.begin(); it!=axes.end(); it++){
					auto it_to_comp=point.axes.find((*it).first);
					if(it_to_comp!=point.axes.end()){
						if((*it_to_comp).second!=(*it).second)return false;		
					}else return false;
					
				}
			}else return false;
			return true;

	}
		
		bool operator==(map<char, Type> point){
			if(axes.size()==point.size()){
				for(auto it=axes.begin(); it!=axes.end(); it++){
					auto it_to_comp=point.find((*it).first);
					if(it_to_comp!=point.end()){
						if((*it_to_comp).second!=(*it).second)return false;		
					}else return false;
					
				}		
			}else return false;
			return true;
	};
		
	PPpoint<Type> operator+(PPpoint &point){
			PPpoint<Type> newPoint;
			for(auto it=axes.begin(); it!=axes.end(); it++){
				auto it_to_add=point.axes.find((*it).first);
				if(it_to_add!=point.axes.end()){
					newPoint.axes.insert(pair<char, Type>((*it).first, (*it_to_add).second+(*it).second));		
				}else newPoint.axes.insert(pair<char, Type>((*it).first, (*it).second));
				
			}
			return newPoint;

	}
	
		void operator+=(PPpoint &point){
			for(auto it=axes.begin(); it!=axes.end(); it++){
				auto it_to_add=point.axes.find((*it).first);
				if(it_to_add!=point.axes.end()){
					(*it).second+=(*it_to_add).second;
				}
			}

	}
		
	void setAxesBasedString(PString &data){

		for(auto it=axes.begin(); it!=axes.end(); ++it){
					(*it).second=data.findValueAfterAcronim((*it).first, (*it).second);
		}
		
	}
	
	bool setAxValue(char acronim, int val){
    auto it=axes.find(acronim);
    if(it!=axes.end()){
        (*it).second=val;
        return true;
    }
    return false;
}
	
void setAxesByZero(void){
		
		for(auto it=axes.begin(); it!=axes.end(); ++it){
				(*it).second=0;
		}
		
	}

bool exists(char acronim){
		
	auto it=axes.find(acronim);
	
	if(it!=axes.end())return true;
  return false;
		
	}
	
};

template <typename Type>
	class PPpointXY{
		
		
		public:
			static_assert	(std::is_arithmetic<Type>::value, "<Type> must be integral or a floating point type");	
		
			Type x=0;
			Type y=0;	
		
			PPpointXY(Type xpos=0, Type ypos=0):x(xpos), y(ypos){};
				
			PPpointXY(PPpoint<Type> &point){
					if(point.exists('X'))x=point.axes.find('X')->second;
					if(point.exists('Y'))y=point.axes.find('Y')->second;
			};

			
			PPpointXY<Type>& operator=(const PPpoint<Type> &point){

				if(point.exists('X'))x=point.axes.find('X')->second;
				if(point.exists('Y'))y=point.axes.find('Y')->second;
				return (*this);

			};	
				
			bool operator==(PPpointXY &point){
					if(x==point.x && y==point.y)return true;
					return false;
			}
			
			PPpointXY<Type> operator+(PPpointXY &point){
					PPpointXY<Type> newPoint;
					newPoint.x=x+point.x;
					newPoint.y=y+point.y;
					return newPoint;

			}
			
			PPpointXY<Type> operator-(PPpointXY &point){
					PPpointXY<Type> newPoint;
					newPoint.x=x-point.x;
					newPoint.y=y-point.y;
					return newPoint;

			}
			
			void operator+=(PPpointXY &point){
					x+=point.x;
					y+=point.y;
			}
			
			void operator+=(PPpoint<Type> &point){
				if(point.exists('X'))x+=point.axes.find('X')->second;
				if(point.exists('Y'))y+=point.axes.find('Y')->second;
			}
			
			void operator-=(PPpointXY &point){
					x-=point.x;
					y-=point.y;
			}
			
			bool operator!=(PPpointXY &point){
					if(x!=point.x || y!=point.y)return true;
					return false;
			}
			
			void clear(void){
				x=0;
				y=0;
			}
			
			void round(Type base){
				roundX(base);
				roundY(base);
			}
			
			
			void roundX(Type base){
				string unitS=to_string(base);
				unitS.substr(unitS.find('.')+1);
				
				auto unit=unitS.size();
				
				int roundX=x*pow(10, unit);
				base*=pow(10, unit);
				roundX-=roundX%static_cast<int>(base);
				x=static_cast<Type>(roundX)/pow(10, unit);
				
			}
			
			
			void roundY(Type base){
				string unitS=to_string(base);
				unitS.substr(unitS.find('.')+1);
				
				auto unit=unitS.size();
				
				int roundY=y*pow(10, unit);
				base*=pow(10, unit);
				roundY-=roundY%static_cast<int>(base);
				y=static_cast<Type>(roundY)/pow(10, unit);
				
			}

};


using PPpointList=vector<PPpoint<double>>;




//template <typename T1, typename T2>
//bool PPpoint<T1, T2>::operator==(PPpoint &point){
//	
//		if(this.size()==point.size()){
//			for(auto it=this.begin(); it!=this.end(); it++){
//				auto it_to_comp=point.find((*it).first);
//				if(it_to_comp!=point.end()){
//					if((*it_to_comp).second!=(*it).second)return false;		
//				}else return false;
//				
//			}
//			
//			
//		}
//		return true;

//}

#endif	
