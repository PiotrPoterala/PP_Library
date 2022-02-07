/**
 * @author  Piotr Poterała
 * @email   poterala.piotr@gmail.com
 * @website http://zappp.pl
 * @version v1.0
 * @ide     Keil uVision 5
 * @license GNU GPL v3
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Piotr Poterała, 2021
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */


#ifndef PP_FILE_INFO_FATFS_H
#define PP_FILE_INFO_FATFS_H

#include <string>
#include "ff.h"
#include "pp_file_info.h"

using namespace std;

class PFileInfoFATFS : public PFileInfo
{
private:
	FATFS g_sFatFs;
	bool exist=false;
	int fattrib;
	int fsize;
	
public:
		PFileInfoFATFS(PFile &file):PFileInfo(file){refresh();};
		PFileInfoFATFS(const string &path):PFileInfo(path){refresh();};
		PFileInfoFATFS(const char* path):PFileInfo(path){refresh();};	
				
		virtual void setFile(PFile &file) override{
			PFileInfo::setFile(file);
			refresh();
		}
				
		virtual void setFile(const string &path) override{
			PFileInfo::setFile(path);
			refresh();
		}
		
		virtual void setFile(const char* path) override{
			PFileInfo::setFile(path);
			refresh();
		}
		
		
		virtual void refresh() override{
			FILINFO fno;
			int fresult=FR_OK;
			
			exist=false;
		
			fresult=f_mount(&g_sFatFs, volume.c_str(), 1);
		
			if(fresult==FR_OK){
				fresult=f_stat(filePath.c_str(), &fno);
		
				if(fresult==FR_OK){
					fattrib=fno.fattrib;
					fsize=fno.fsize;
					exist=true;
				}
				f_mount(0, volume.c_str(), 1);
			}
			
		};
		
		virtual bool	exists() override{return exist;};
		virtual bool isFile() override{if(!(fattrib & AM_DIR))return true; else return false;};
		virtual bool isDir() override{if(fattrib & AM_DIR)return true; else return false;};
		virtual bool isHidden() override{if(fattrib & AM_HID)return true; else return false;};
		virtual bool isWritable() override{if(!(fattrib & AM_RDO))return true; else return false;};
		virtual PDateTime lastModified() override;
		virtual int size() override{return fsize;};
};

#endif 