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


#ifndef PP_FILE_INFO_H
#define PP_FILE_INFO_H

#include <string>
#include "pp_file.h"
#include "pp_dir.h"

using namespace std;

class PFileInfo
{
protected:
		string volume;
		string filePath;

		void setPath(const string &path);

public:
		PFileInfo(PFile &file);
		PFileInfo(PDir &dir);
		PFileInfo(const string &path);
		PFileInfo(const char* path);	
				
		string	absoluteFilePath() const;
		string	absolutePath() const;
		string	fileName() const;
		
		virtual void refresh()=0;
		virtual bool	exists() =0;
		virtual bool isFile() =0;
		virtual bool isDir() =0;
		virtual bool isHidden() =0;
		virtual bool isWritable() =0; 
//		PDateTime lastModified();
		virtual int size() =0;
};

#endif 

