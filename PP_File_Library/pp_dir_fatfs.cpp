#include "pp_dir_fatfs.h"



//virtual string	absoluteFilePath(const string &fileName) const override;
string	PDirFATFS::absolutePath() const{
	
	return dirPath;
}

bool	PDirFATFS::cd(const string &dirName){
	
	
	
}



//virtual bool	cdUp() override;
unsigned int	PDirFATFS::count() const{
		int fresult=FR_OK;
		FILINFO fno;
		unsigned int cnt=0;
	
		fresult=f_mount(&volume->g_sFatFs, volume->volume.c_str(), 1);
	
		if(fresult==FR_OK){
			fresult= f_opendir(&Dir, dirPath);                       /* Open the directory */
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




string PDirFATFS::dirName() const{
	
}
////	QFileInfoList	entryInfoList(QDir::Filters filters = NoFilter) const
vector<string> PDirFATFS::entryList(Filters filters) const{
		int fresult=FR_OK;
		FILINFO fno;
		vector<string> pathList;
	
		fresult=f_mount(&volume->g_sFatFs, volume->volume.c_str(), 1);
	
		if(fresult==FR_OK){
			fresult= f_opendir(&Dir, dirPath);                       /* Open the directory */
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

bool PDirFATFS::exists(const string &name) const{
	
		return exist(dirPath+"/"+name);
}



bool PDirFATFS::exists(){
	
		return exist(dirPath);
	
	
}

bool PDirFATFS::exist(string &path){
	
		int fresult=FR_OK;
		fresult=f_mount(&volume->g_sFatFs, volume->volume.c_str(), 1);
	
		if(fresult==FR_OK){
			fresult=f_opendir(&Dir, path.c_str());
		}
	
		if(fresult==FR_OK){
			f_closedir(&Dir);
			return true;
		}
		return false;
	
}