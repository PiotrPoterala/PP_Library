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
	
	#include "pstring.h"
	#include "pp_math.h"
	#include "pp_math_ext.h"
	
using PPointIntPair = pair<char, int>;

template <typename Type>
	class PPpoint{
		
	using TLimits=tuple<Type,Type,Type,int>;
		
	private:
		map<char, TLimits> limits;
		map<char, Type> axes;	
		
	public:
		static_assert	(std::is_arithmetic<Type>::value, "<Type> must be integral or a floating point type");	
		
//		map<char, Type> axes;	
		
		PPpoint(){};
		PPpoint(map<char, Type> point){axes=point;}
//		PPpoint(const PPpoint<Type> &point){
//			axes=point.getAxes();
//			limits=point.getLimits();
//		}
		PPpoint(const map<char, Type> &point, const map<char, TLimits> &lim){
			limits=lim;
			for(auto it:point){
				addAx(it);
			}
		}
		
		shared_ptr<PPpoint<Type>> clone() const{
	
			return make_shared<PPpoint<Type>>(*this);
		}
		
			
		PPpoint<Type>& operator=(const PPpoint<Type> &point){

			axes=point.getAxes();
			limits=point.getLimits();
			return (*this);

		}		
			
		
		template <typename From>
		PPpoint<Type>& operator=(const PPpoint<From> &pointToConvert){

		//		PPpoint<Type> point;
				axes.clear();
				limits.clear();
	
				for(auto pkt:pointToConvert.getAxes()){
					addAx(pair<char, Type>(pkt.first, static_cast<Type>(pkt.second)));					
				}
				
				for(auto lim:pointToConvert.getLimits()){
					addLimit(lim.first, TLimits(static_cast<Type>(std::get<0>(lim.second)), static_cast<Type>(std::get<1>(lim.second)), static_cast<Type>(std::get<2>(lim.second)), std::get<3>(lim.second)));		
				}
				
				
			
				return (*this);
		}	
		
		
		PPpoint<Type>& operator=(const map<char, Type> point){

			axes=point;
			limits.clear();

			return (*this);

		}	
		
		void clear(){
			axes.clear();
			limits.clear();
		}
		
		void swap(PPpoint<Type> &point){
			axes.swap(point.rGetAxes());
			limits.swap(point.rGetLimits());
		}
		
		
		void addAx(char acronim, Type value){
			axes.insert(pair<char, Type>(acronim, 0));
			setAxValue(acronim, value);
			
		}
		
		void addAx(pair<char, Type> ax){
			axes.insert(ax);
			setAxValue(ax.first, ax.second);
			
		}
		
		void eraseAx(char acronim, Type value){
			axes.erase(acronim);
			limits.erase(acronim);
		}
		
		map<char, Type>& rGetAxes(){
			return axes;

		}			
		
		map<char, Type> getAxes() const{
			return axes;

		}		
		
		bool operator==(PPpoint &point){
			if(axes.size()==point.axes.size()){
				return compare(point);
			}
			
			return false;
		}
		
		bool compare(PPpoint &point){
			for(auto it:axes){
				auto it_to_comp=point.axes.find(it.first);
				if(it_to_comp!=point.axes.end()){
					if(it_to_comp->second!=it.second)return false;		
				}else return false;
				
			}
			return true;
		}
		
		bool operator==(map<char, Type> &point){
			if(axes.size()==point.size()){
				return compare(point);		
			}
			
			return false;
		}
		
	bool compare(map<char, Type> &point){
		for(auto it:axes){
				auto it_to_comp=point.find(it.first);
				if(it_to_comp!=point.end()){
					if(it_to_comp->second!=it.second)return false;		
				}else return false;
			}		
			return true;
	}
		
	PPpoint<Type> operator+(PPpoint &point){
			PPpoint<Type> newPoint;
			for(auto it:axes){
				auto it_to_add=point.axes.find(it.first);
				if(it_to_add!=point.axes.end()){

					auto limit=limits.find(it.first);
					if(limit!=limits.end()){
							newPoint.axes.insert(pair<char, Type>(it.first, trimAcc_pp(it_to_add->second+it.second, std::get<0>(limit->second), std::get<1>(limit->second), std::get<2>(limit->second))));		
							newPoint.addLimit(it.first, limit->second);
					}else newPoint.axes.insert(pair<char, Type>(it.first, it_to_add->second+it.second));
					
				}else newPoint.axes.insert(pair<char, Type>(it.first, it.second));
				
			}
			return newPoint;

	}
	
		void operator+=(PPpoint &point){
			for(auto&& it:axes){
				auto it_to_add=point.axes.find(it.first);
				if(it_to_add!=point.axes.end()){
					setAxValue(it.first, it.second+it_to_add->second);	
				}
			}
		}
		
		void operator-=(PPpoint &point){
			for(auto&& it:axes){
				auto it_to_add=point.axes.find(it.first);
				if(it_to_add!=point.axes.end()){
					setAxValue(it.first, it.second-it_to_add->second);	
				}
			}
		}
		
		void operator-=(const map<char, Type> point){
			for(auto&& it:axes){
				auto it_to_add=point.find(it.first);
				if(it_to_add!=point.end()){
					setAxValue(it.first, it.second-it_to_add->second);				
				}
			}
		}
		
	void setAxesBasedString(PString &data){

		for(auto&& it:axes){
			auto limit=limits.find(it.first);
			if(limit!=limits.end()){
				setAxValue(it.first, data.findValueAfterAcronim(it.first, static_cast<double>(it.second)/pow_pp(10, std::get<3>(limit->second)))*pow_pp(10, std::get<3>(limit->second)));
			}else{
				setAxValue(it.first, data.findValueAfterAcronim(it.first, it.second));
			}
			
//					it.second=data.findValueAfterAcronim(it.first, it.second);
		}
		
	}
	
	
	string getStringWithAx(char acronim){
		string answer;
	
		auto ax=axes.find(acronim);
		if(ax!=axes.end()){
			answer+=acronim;  
			auto limit=limits.find(acronim);
			if(limit!=limits.end()){
				answer+=PString::doubleToString(static_cast<double>(ax->second)/pow_pp(10, std::get<3>(limit->second)), std::get<3>(limit->second));
			}else{
				answer+=PString::doubleToString(ax->second, 0);
			}
		}
		
		return answer;
	}

	string getStringWithAxes(){
		
		string answer;
		auto it_last_elem=axes.end();
		
		it_last_elem--;
		
			for(auto it=axes.begin(); it!=axes.end(); it++){
					answer+=getStringWithAx(it->first);  
					if(it!=it_last_elem)answer+=" ";
			}
		
		return answer;
	}
	
	
	vector<Type> getAx(char acronim){
		vector<Type> value;

		auto it=axes.find(acronim);
		
		if(it!=axes.end())value.push_back(it->second);
		
		return value;
	}
	
	
	Type getAxValue(char acronim){
		auto it=axes.find(acronim);
		if(it!=axes.end())return it->second;
		
		return 0;
	}
	
	double getRealAxValue(char acronim){
		double val=static_cast<double>(getAxValue(acronim));
		auto limit=limits.find(acronim);
    if(limit!=limits.end())val/=pow_pp(10, std::get<3>(limit->second));
		
		return val;
	}
	
	bool setAxValue(char acronim, Type val){
    auto it=axes.find(acronim);
    if(it!=axes.end()){
				auto limit=limits.find(acronim);
				if(limit!=limits.end()){
					it->second=trimAcc_pp(val, std::get<0>(limit->second), std::get<1>(limit->second), std::get<2>(limit->second));
        }else it->second=val;
        return true;
    }
    return false;	
}
	
	void setRealAxValue(char acronim, double val){
		auto limit=limits.find(acronim);
		if(limit!=limits.end())val*=pow_pp(10, std::get<3>(limit->second));
		setAxValue(acronim, static_cast<Type>(val));
	}
	
	void setAxesByZero(void){
			
		for(auto&& it:axes){
					setAxValue(it.first, 0);
		//			(*it).second=0;
			}
			
		}

	bool exists(char acronim){
			
		auto it=axes.find(acronim);
		
		if(it!=axes.end())return true;
		return false;
			
		}

	
	void setLimits(map<char, TLimits> newLimits){
		
		limits=newLimits;
		
	}
	
	map<char, TLimits> getLimits() const{
		return limits;
		
	}
	
	map<char, TLimits>& rGetLimits() const{
		return limits;
		
	}
	
	vector<TLimits> getLimit(char acronim) const{
		vector<TLimits> lim;
		
		auto it=limits.find(acronim);
	
		if(it!=limits.end())lim.push_back(it->second);
		
		return lim;
	}

	
	void addLimit(char acronim, TLimits data){
		
		limits.insert(pair<char, TLimits>(acronim, data));
		
	}


	void ereseLimit(char acronim){
		limits.erase(acronim);
		
	}

	void ereseLimits(){
		limits.clear();
	}
	
	bool existLimit(char acronim) const{
		auto it=limits.find(acronim);
	
		if(it!=limits.end())return true;
		return false;
	}
	
	
};
	

template<typename To, typename From>
PPpoint<To> convertPPpointType(const PPpoint<From>& pointToConvert){
	PPpoint<To> point{};
	
		for(auto pkt:pointToConvert.axes){
			point.axes.insert(pair<char, To>(pkt.first, static_cast<To>(pkt.second)));
			
		}
	
	return point;
};



template <typename Type>
	class PPpointXY{
		
		using TLimits=tuple<Type,Type,Type,int>;
		
		private:
			map<char, TLimits> limits;
			Type x=0;
			Type y=0;	
		
		public:	
		
			PPpointXY(Type xpos=0, Type ypos=0):x(xpos), y(ypos){}
				
			PPpointXY(PPpoint<Type> &point){
				if(point.existLimit('X'))addXLimit(point.getLimit('X').front());
				if(point.existLimit('Y'))addYLimit(point.getLimit('Y').front());
				if(point.exists('X'))setX(point.getAxValue('X'));
				if(point.exists('Y'))setY(point.getAxValue('Y'));
			}
			
			Type getX(){return x;}
			Type getY(){return y;}
			
			void setX(Type val){
				auto limit=limits.find('X');
				if(limit!=limits.end()){
					x=trimAcc_pp(val, std::get<0>(limit->second), std::get<1>(limit->second), std::get<2>(limit->second));
				}else x=val;		
			}
			
			void setRealX(double val){
				auto limit=limits.find('X');
				if(limit!=limits.end())val*=pow_pp(10, std::get<3>(limit->second));
				setX(val);
			}
			
			void setY(Type val){
				auto limit=limits.find('Y');
				if(limit!=limits.end()){
					y=trimAcc_pp(val, std::get<0>(limit->second), std::get<1>(limit->second), std::get<2>(limit->second));
				}else y=val;		
			}

			void setRealY(double val){
				auto limit=limits.find('Y');
				if(limit!=limits.end())val*=pow_pp(10, std::get<3>(limit->second));
				setY(val);
			}
			
			PPpointXY<Type>& operator=(const PPpoint<Type> &point){
				if(point.existLimit('X'))addXLimit(point.getLimit('X').front());
				if(point.existLimit('Y'))addYLimit(point.getLimit('Y').front());
				if(point.exists('X'))setX(point.axes.find('X')->second);
				if(point.exists('Y'))setY(point.axes.find('Y')->second);
				return (*this);

			}	
				
			bool operator==(PPpointXY &point){
					if(x==point.x && y==point.y)return true;
					return false;
			}
			
			PPpointXY<Type> operator+(PPpointXY &point){
					PPpointXY<Type> newPoint;
					newPoint.setLimits(point.getLimits());
					newPoint.setX(x+point.x);
					newPoint.setY(y+point.y);
					return newPoint;

			}
			
			PPpointXY<Type> operator-(PPpointXY &point){
					PPpointXY<Type> newPoint;
					newPoint.setLimits(point.getLimits());
					newPoint.setX(x-point.x);
					newPoint.setY(y-point.y);
					return newPoint;

			}
			
			void operator+=(PPpointXY &point){
				setX(x+point.x);
				setY(y+point.y);
			}
			
			void operator+=(PPpoint<Type> &point){
				if(point.exists('X'))setX(x+point.getAxValue('X'));
				if(point.exists('Y'))setY(y+point.getAxValue('Y'));
			}
			
			void operator-=(PPpointXY &point){
					setX(x-point.x);
					setY(y-point.y);
			}
			
			bool operator!=(PPpointXY &point){
					if(x!=point.x || y!=point.y)return true;
					return false;
			}
			
			void clear(void){
				setX(0);
				setY(0);
			}
			
			void round(Type precision){
				roundX(precision);
				roundY(precision);
			}
			
			
			void roundX(Type precision){
				round_pp(x, precision);
//				string unitS=to_string(base);
//				unitS.substr(unitS.find('.')+1);
//				
//				auto unit=unitS.size();
//				
//				int roundX=x*pow(10, unit);
//				base*=pow(10, unit);
//				roundX-=roundX%static_cast<int>(base);
//				x=static_cast<Type>(roundX)/pow(10, unit);
				
			}
			
			
			void roundY(Type precision){
				round_pp(y, precision);
			}
			
			
			void setLimits(map<char, TLimits> newLimits){
				
				auto lim=newLimits.find('X');
				if(lim!=newLimits.end()){
					limits.insert(pair<char, TLimits>(lim->first, lim->second));
					setX(x);
				}
				lim=newLimits.find('Y');
				if(lim!=newLimits.end()){
					limits.insert(pair<char, TLimits>(lim->first, lim->second));
					setY(y);
				}
			}
			
				map<char, TLimits> getLimits() const{
					return limits;
					
				}

				
				void addXLimit(TLimits data){
					
					limits.insert(pair<char, TLimits>('X', data));
					setX(x);
					
				}
				
				void addYLimit(TLimits data){
					
					limits.insert(pair<char, TLimits>('Y', data));
					setY(y);
					
				}
				
				vector<TLimits> getXLimit(){		
					vector<TLimits> limit;					
					auto lim=limits.find('X');
					if(lim!=limits.end())limit.push_back(lim->second);
					return limit;
				}
				
				vector<TLimits> getYLimit(){		
					vector<TLimits> limit;					
					auto lim=limits.find('Y');
					if(lim!=limits.end())limit.push_back(lim->second);
					return limit;
				}

				void ereseLimits(){
					limits.clear();
				}
				
			

};

using PPpointIntShdPtr=shared_ptr<PPpoint<int>>;

using PPpointIntList=vector<PPpoint<int>>;
using PPpointIntListShdPtr=shared_ptr<PPpointIntList>;



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
