#ifndef _PP_DIR_FATFS_COMMAND_H
	#define _PP_DIR_FATFS_COMMAND_H
	
	#include "pp_command.h"
	#include "pp_dir.h"
	#include "pp_file_info_fatfs.h"
	#include "pp_file_fatfs.h"
	
class PSetFileFATFSCommand : public PCommand{
		
		private:
			PDir *dir;
			PIOdeviceShrPtr dev;
	
		public:
			PSetFileFATFSCommand(PDir *directory, PIOdeviceShrPtr device ):dir(directory), dev(device){};
	
			virtual bool execute(string &data) override{
					PFileInfoFATFS fInfo(dir->absoluteFilePath(data));
				
					if(fInfo.exists()){
						dev=make_shared<PFileFATFS>(dir->absoluteFilePath(data));
						return true;
					}						
					return false;
			};

	};
	
#endif