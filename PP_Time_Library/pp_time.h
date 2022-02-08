#ifndef _PP_TIME_H
	#define _PP_TIME_H

		#include <string>


		using namespace std;


		class PTime{
			private:
				int sec=0; 
				int min=0; 
				int hr=0;
			
			public:
				PTime(int h, int m, int s);
				void reset();
				void	addSec(int s=1);
				int	hour() const;
				int	minute() const;
				int	second() const;
				bool setHMS(int s);
				bool setHMS(int h, int m, int s);
				int toSec() const;
				string	toString() const;
				bool	operator!=(const PTime &t) const;
				bool	operator<(const PTime &t) const;
				bool	operator<=(const PTime &t) const;
				bool	operator==(const PTime &t) const;
				bool	operator>(const PTime &t) const;
				bool	operator>=(const PTime &t) const;
				void	operator+(const PTime &t);

		};
#endif