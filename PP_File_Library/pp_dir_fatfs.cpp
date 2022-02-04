#include "pp_dir_fatfs.h"

bool PDirFATFS::cd(const string &dirName){
	
		if(dirName.compare("..")==0){
			return cdUp();
		}else{
			string newDirPath=dirPath+"/"+dirName;
		
			if(exists(newDirPath)){
				dirPath=newDirPath;
				return true;
			}
		}
	
		return false;
}

bool PDirFATFS::cdUp(){
		int find=dirPath.find_last_of("/");
		string newDirPath=dirPath.substr(0, find);
	
		if(exists(newDirPath)){
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
	
		return exist(path, PDir::Files);
}



bool PDirFATFS::exists(){
	
		return exist(dirPath, PDir::Dirs);

}

bool PDirFATFS::exist(string &path, Filters filters){
		FILINFO fno;
		int fresult=FR_OK;
		bool objectExist=false;
	
		fresult=f_mount(&g_sFatFs, volume.c_str(), 1);
	
		if(fresult==FR_OK){
			fresult=f_stat(path.c_str(), &fno);
	
			if(fresult==FR_OK){
				if (filters==PDir::NoFilter || 
						((filters==PDir::Dirs) && (fno.fattrib & AM_DIR)) || 		/* It is a directory */
						((filters==PDir::Files) && !(fno.fattrib & AM_DIR)) ){
					objectExist=true;
				}
			}
			f_mount(0, volume.c_str(), 1);
		}
		
		return objectExist;
	
}