#ifndef _COMMAND_H
	#define _COMMAND_H
	
	using namespace std;

	class defOCommand{
		
		protected:
			defOCommand();
		
		public:
			virtual void execute()=0;

	};


#endif
