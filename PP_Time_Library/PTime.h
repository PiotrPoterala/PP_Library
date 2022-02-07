#ifndef _PP_TIME_H
	#define _PP_TIME_H

		#include <string>


		using namespace std;


		class PTime{
			private:
				int sec; 
				int min; 
				int hr;
			
				int time2sec();
			public:
				PTime(int h, int m, int s);
				void	addSecs(int s) const;
				int	hour() const;
				int	minute() const;
				int	second() const;
				bool	setHMS(int h, int m, int s);
				string	toString() const;
				bool	operator!=(const PTime &t) const;
				bool	operator<(const PTime &t) const;
				bool	operator<=(const PTime &t) const;
				bool	operator==(const PTime &t) const;
				bool	operator>(const PTime &t) const;
				bool	operator>=(const PTime &t) const;

		};
#endif