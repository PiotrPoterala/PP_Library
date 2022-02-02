#include "pp_dir_fatfs.h"

bool PDirFATFS::cd(const string &dirName){
	
		if(dirName.compare("..")==0){
			return cdUp();
		}else{
			string newDirPath=dirPath+"/"+dirName;
		
			if(exist(newDirPath)){
				dirPath=newDirPath;
				return true;
			}
		}
	
		return false;
}

bool PDirFATFS::cdUp(){
		int find=dirPath.find_last_of("/");
		string newDirPath=dirPath.substr(0, find);
	
		if(exist(newDirPath)){
			dirPath=newDirPath;
			return true;
		}
	
		return false;
	
}


unsigned int	PDirFATFS::count(){
		int fresult=FR_OK;
		FILINFO fno;
		unsigned int cnt=0;
	
		fresult=f_mount(&g_sFatFs, volume.c_str(), 1);
	
		if(fresult==FR_OK){
			fresult= f_opendir(&Dir, dirPath.c_str());                       /* Open the directory */
			if (fresult == FR_OK) {
					for (;;) {
							fresult = f_readdir(&Dir, &fno);                   /* Read a directory item */
							if (fresult != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
							cnt++;
					}
					f_closedir(&Dir);
			}
		}

		return cnt;
}


////	QFileInfoList	entryInfoList(QDir::Filters filters = NoFilter) const
vector<string> PDirFATFS::entryList(Filters filters) {
		int fresult=FR_OK;
		FILINFO fno;
		vector<string> pathList;
	
		fresult=f_mount(&g_sFatFs, volume.c_str(), 1);
	
		if(fresult==FR_OK){
			fresult= f_opendir(&Dir, dirPath.c_str());                       /* Open the directory */
			if (fresult == FR_OK) {
					for (;;) {
							fresult = f_readdir(&Dir, &fno);                   /* Read a directory item */
							if (fresult != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
							if (filters==PDir::NoFilter || 
									((filters==PDir::Dirs) && (fno.fattrib & AM_DIR)) || 		/* It is a directory */
							((filters==PDir::Files) && !(fno.fattrib & AM_DIR)) ) {                   
									pathList.push_back(dirPath+"/"+fno.fname);
								
							}
					}
					f_closedir(&Dir);
			}
		}
	
	return pathList;
}

bool PDirFATFS::exists(const string &name){
		string path=dirPath+"/"+name;
	
		return exist(path);
}



bool PDirFATFS::exists(){
	
		return exist(dirPath);
	
	
}

bool PDirFATFS::exist(string &path){
	
		int fresult=FR_OK;
		fresult=f_mount(&g_sFatFs, volume.c_str(), 1);
	
		if(fresult==FR_OK){
			fresult=f_opendir(&Dir, path.c_str());
		}
	
		if(fresult==FR_OK){
			f_closedir(&Dir);
			return true;
		}
		return false;
	
}