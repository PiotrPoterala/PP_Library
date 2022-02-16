#include "pp_dir_fatfs.h"

bool PDirFATFS::cd(const string &dirName){
	
		if(dirName.compare("..")==0){
			return cdUp();
		}else{
			
			if(exists(dirName)){
				
				dirPath+="/";
				dirPath+=dirName;
				return true;
			}
		}
	
		return false;
}

bool PDirFATFS::cdUp(){
		string path=absolutePath();
		string newDirName;
	
		path.substr(0, path.find_last_of("/"));
		newDirName=path.substr(path.find_last_of("/")+1);
	
		if(exists(newDirName)){
			setPath(path);
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
			fresult= f_opendir(&Dir, absolutePath().c_str());                       /* Open the directory */
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


vector<PFileInfo*>	PDirFATFS::entryInfoList(PDir::Filters filters){
		int fresult=FR_OK;
		FILINFO fno;
		vector<PFileInfo*> fileInfoList;
	
		fresult=f_mount(&g_sFatFs, volume.c_str(), 1);
	
		if(fresult==FR_OK){
			fresult= f_opendir(&Dir, absolutePath().c_str());                       /* Open the directory */
			if (fresult == FR_OK) {
					for (;;) {
							fresult = f_readdir(&Dir, &fno);                   /* Read a directory item */
							if (fresult != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
							if (filters==PDir::NoFilter || 
									((filters==PDir::Dirs) && (fno.fattrib & AM_DIR)) || 		/* It is a directory */
							((filters==PDir::Files) && !(fno.fattrib & AM_DIR)) ) {     							
									fileInfoList.push_back(new PFileInfoFATFS(volume+dirPath+"/"+fno.fname));
								
							}
					}
					f_closedir(&Dir);
			}
		}
	
	return fileInfoList;
	
	
}




vector<string> PDirFATFS::entryList(PDir::Filters filters) {
		int fresult=FR_OK;
		FILINFO fno;
		vector<string> pathList;
	
		fresult=f_mount(&g_sFatFs, volume.c_str(), 1);
		if(fresult==FR_OK){
			fresult= f_opendir(&Dir, absolutePath().c_str());                       /* Open the directory */
			if (fresult == FR_OK) {
					for (;;) {
							fresult = f_readdir(&Dir, &fno);                   /* Read a directory item */
							if (fresult != FR_OK || fno.fname[0] == 0  || fno.fsize>0x0FFFFFFF) break;  /* Break on error or end of dir */
							if (filters==PDir::NoFilter || 
									((filters==PDir::Dirs) && (fno.fattrib & AM_DIR)) || 		/* It is a directory */
							((filters==PDir::Files) && !(fno.fattrib & AM_DIR)) ) {                   
									pathList.push_back(fno.fname);
								
							}
					}
					f_closedir(&Dir);
			}
		}
	
	return pathList;
}

bool PDirFATFS::exists(const string &name){
		string path=absolutePath()+"/"+name;
	
		return exist(path, PDir::Files);
}



bool PDirFATFS::exists(){
		string path=absolutePath();
	
		return exist(path, PDir::Dirs);

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