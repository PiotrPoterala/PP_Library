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


#ifndef PP_DIR_FATFS_H
#define PP_DIR_FATFS_H

#include "pp_dir.h"

using namespace std;

class PDirFATFS : public PDir
{


public:
	PDir(const string &path):dirPath(path);

		enum	Filters {NoFilter, Dirs, Files, AllObjects};

		virtual string	absoluteFilePath(const string &fileName) const=0;
		virtual string	absolutePath() const=0;
		virtual bool	cd(const string &dirName)=0;
		virtual bool	cdUp()=0;
		virtual unsigned int	count() const=0;
		virtual string	dirName() const=0;
	//	QFileInfoList	entryInfoList(QDir::Filters filters = NoFilter) const
		virtual list<string>	entryList(Filters filters = NoFilter) const=0;
		virtual bool	exists(const string &name) const=0;
		virtual bool	exists() const=0;
			
		void	setPath(const string &path){dirPath=path;};
};

#endif 
