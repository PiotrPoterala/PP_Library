#ifndef _PP_SET_FILE_NAME_COMMAND_H
	#define _PP_SET_FILE_NAME_COMMAND_H
	
	#include "pp_command.h"
	#include "pp_dir.h"
	#include "pp_program_resolver_strategy.h"
	#include "pp_file.h"
	
class PSetFileNameCommand : public PCommand{
		
		private:
			PDirShrPtr dir;
			PFileShrPtr file;
			PProgramResolverSwitchContextShrPtr resolveProgram;
//			PProgramResolverContextShrPtr resolveProgram;
	
		public:
			PSetFileNameCommand()=delete;
			PSetFileNameCommand(PDirShrPtr directory, PFileShrPtr device,PProgramResolverSwitchContextShrPtr resProg):dir(directory), file(device), resolveProgram(resProg){};
	
			virtual bool execute(string &data) override{
			//		PFileInfoFATFS fInfo(dir->absoluteFilePath(data));
				
					file->setFileName(dir->absoluteFilePath(data));
					if(resolveProgram->interpretProg()==InterpretProgErr::idNO_ERRORS){
						return true;
					}				
					return false;
			};

	};
	
#endif