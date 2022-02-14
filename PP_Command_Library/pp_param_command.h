#ifndef _PP_PARAM_COMMAND_H
	#define _PP_PARAM_COMMAND_H
	
	#include "pp_command.h"
	#include "pp_paramlist.h"
	
	#include <string>
	#include <map>

class PSetParamCommand : public PCommand{
		
		private:
			defOParamList *param;
	
		public:
			PSetParamCommand(defOParamList *par):param(par){};
	
			virtual void execute(map<char, double> &values) override{
				
				param->setParamsValue(values);		
				
			};

	};


class PGetParamCommand : public PAskCommand{
		
		private:
			defOParamList *param;
	
		public:
			PGetParamCommand(defOParamList *par):param(par){};
	
			virtual string execute() override{
						
					return param->getStringWithParams();
				
			};

	};
	
#endif