#ifndef _PP_SELECT_PROG_TYPE_COMMAND_H
	#define _PP_SELECT_PROG_TYPE_COMMAND_H
	
	#include "pp_command.h"
	#include "pp_select_list.h"
	
class PSetProgTypeCommand : public PCommand{
		
		private:
			PSelectListShrPtr typeOfProgSelList;
			PProgramResolverSwitchContextShrPtr resolveProgram;
	
		public:
			PSetProgTypeCommand()=delete;
			PSetProgTypeCommand(PSelectListShrPtr type, PProgramResolverSwitchContextShrPtr resProg):typeOfProgSelList(type), resolveProgram(resProg){};
	
			virtual bool execute(string &data) override{
				PString str(data);
				int index=str.findValueAfterAcronim('t');
				typeOfProgSelList->setCurrentIndex(index);
				resolveProgram->setResolver(index);
				return true;
			};

	};

	
	class PGetProgTypeCommand : public PAskCommand{
		
		private:
			PSelectListShrPtr typeOfProgSelList;
	
		public:
			PGetProgTypeCommand()=delete;
			PGetProgTypeCommand(PSelectListShrPtr type):typeOfProgSelList(type){};
	
			virtual string execute() override{
					string response="t";
					response+=to_string(typeOfProgSelList->currentIndex());
					return response;
				
			};

	};
	
#endif