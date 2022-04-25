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


#ifndef PP_FILE_INFO_MOCK_H
#define PP_FILE_INFO_MOCK_H

#include <string>
#include "pp_file_info.h"

using namespace std;

class PFileInfoMock : public PFileInfo
{
private:
	bool exist=false;
	bool dir=false;
	
public:
		PFileInfoMock(PFile &file):PFileInfo(file){refresh();};
		PFileInfoMock(const string &path):PFileInfo(path){refresh();};
		PFileInfoMock(const char* path):PFileInfo(path){refresh();};	
				
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

					exist=true;

		};
		
		virtual bool exists() override{return exist;};
		virtual bool isFile() override{if(!dir)return true; else return false;};
		virtual bool isDir() override{return dir;};
		virtual bool isHidden() override{ return false;};
		virtual bool isWritable() override{return true;};
		
		virtual string lastModifiedTime() override{
			string time="12:10:04";
			return time;
		}
			
		virtual string lastModifiedDate() override{
			string date="2022-10-04";
			return date;
		}
		virtual int size() override{return 24;};

};
	
#endif 