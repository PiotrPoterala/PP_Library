#ifndef _PP_PARAM_COMMAND_H
	#define _PP_PARAM_COMMAND_H
	
	#include "pp_command.h"
	#include "pp_paramlist.h"
	
	#include <string>
	#include <map>

class PSetParamCommand : public PCommand{
		
		private:
			defOParamListShdPtr param;
	
		public:
			PSetParamCommand(defOParamListShdPtr par):param(par){};
	
			virtual bool execute(string &data) override{
					PString str(data);
					param->setParamsBasedString(str);	
					return true;
			};

	};


class PGetParamCommand : public PAskCommand{
		
		private:
			defOParamListShdPtr param;
	
		public:
			PGetParamCommand(defOParamListShdPtr par):param(par){};
	
			virtual string execute() override{
						
					return param->getStringWithParams();
				
			};

	};
	
#endif