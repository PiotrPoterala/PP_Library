#ifndef _PP_COMMAND_H
	#define _PP_COMMAND_H
	
	#include <string>
	#include <map>

	class PCommand{
		
		protected:
			PCommand(){};
		
		public:
			virtual bool execute(string &data)=0;

	};

	class PAskCommand{
		
		protected:
			PAskCommand(){};
		
		public:
			virtual string execute()=0;

	};
	
	
#endif
