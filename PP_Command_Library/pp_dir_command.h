#ifndef _PP_DIR_COMMAND_H
	#define _PP_DIR_COMMAND_H
	
	#include "pp_command.h"
	#include "pp_dir.h"
	#include "pp_file_info.h"
	

class PDirCdCommand : public PCommand{
		
		private:
			PDirShrPtr dir;
	
		public:
			PDirCdCommand(PDirShrPtr directory):dir(directory){};
	
			virtual bool execute(string &data) override{
				
				return dir->cd(data);		
				
			};

	};


class PGetDirEntryListCommand : public PAskCommand{
		
		private:
			PDirShrPtr dir;
	
		public:
			PGetDirEntryListCommand(PDirShrPtr directory):dir(directory){};
	
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

	class PGetDirEntryInfoListCommand : public PAskCommand{
		
		private:
			PDirShrPtr dir;
	
		public:
			PGetDirEntryInfoListCommand(PDirShrPtr directory):dir(directory){};
	
			virtual string execute() override{
					string data;
					vector<unique_ptr<PFileInfo>> entrInfoList=dir->entryInfoList();	
					for(auto it=entrInfoList.begin(); it!=entrInfoList.end(); it++){
						data+=(*it)->fileName();
						data+=" ";
						data+=to_string((*it)->size());
						data+=" ";
						data+=(*it)->lastModifiedDate();
						data+=",";
					}
				
					return data;
				
			};

	};
	
#endif