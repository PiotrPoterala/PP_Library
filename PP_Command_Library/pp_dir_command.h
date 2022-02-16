#ifndef _PP_DIR_COMMAND_H
	#define _PP_DIR_COMMAND_H
	
	#include "pp_command.h"
	#include "pp_dir.h"
	

class PDirCdCommand : public PCommand{
		
		private:
			PDir *dir;
	
		public:
			PDirCdCommand(PDir *directory):dir(directory){};
	
			virtual bool execute(string &data) override{
				
				return dir->cd(data);		
				
			};

	};


class PGetDirEntryListCommand : public PAskCommand{
		
		private:
			PDir *dir;
	
		public:
			PGetDirEntryListCommand(PDir *directory):dir(directory){};
	
			virtual string execute() override{
					string data;
					vector<string> entryList=dir->entryList();	
					for(auto it=entryList.begin(); it!=entryList.end(); it++){
						data+=(*it);
						data+=",";
					}
				
					return data;
				
			};

	};
	
#endif