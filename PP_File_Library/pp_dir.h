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


#ifndef PP_DIR_H
#define PP_DIR_H

#include <string>
#include <vector>
#include "pp_file_info.h"

using namespace std;

class PDir
{
protected:
		string volume;
		string dirPath;

public:
		PDir(const string &path);
		PDir(const char* path);	
		virtual ~PDir(){};
			
		enum	Filters {NoFilter, Dirs, Files};

		string	absoluteFilePath(const string &fileName) const;
		string	absolutePath() const;
		string	dirName() const;
		
		virtual bool	cd(const string &dirName)=0;
		virtual bool	cdUp()=0;
		virtual unsigned int	count()=0;
		virtual vector<unique_ptr<PFileInfo>>	entryInfoList(Filters filters = NoFilter)=0;
		virtual vector<string> entryList(Filters filters = NoFilter)=0;
		virtual bool exists(const string &name)=0;
		virtual bool exists() =0;
		virtual bool remove(const string &fileName)=0;
		void	setPath(const string &path);
};

using PDirShrPtr=shared_ptr<PDir>;	

#endif 
