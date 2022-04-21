#ifndef _PP_COMMAND_H
	#define _PP_COMMAND_H
	
	#include <string>
	#include <map>
	
	constexpr int qMARK_TAG=(1<<28);
	constexpr int qMARK_KEY=(2<<28);
	constexpr int qMARK_ATC=(3<<28);

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
	
	using PComandShrPtr = shared_ptr<PCommand>;
	using PAskComandShrPtr = shared_ptr<PAskCommand>;
	
#endif
