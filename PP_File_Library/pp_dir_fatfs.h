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

#include "ff.h"

using namespace std;

class PDirFATFS : public PDir
{

	private:
		DIR Dir;
		PVolume *volume;
	
	public:
			PDirFATFS(PVolume *vol, const string &path):volume(vol), dirPath(path);

			virtual string	absoluteFilePath(const string &fileName) const override;
			virtual string	absolutePath() const override;
			virtual bool	cd(const string &dirName) override;
			virtual bool	cdUp() override;
			virtual unsigned int	count() const override;
			virtual string	dirName() const override;
		//	QFileInfoList	entryInfoList(QDir::Filters filters = NoFilter) const
			virtual vector<string>	entryList(Filters filters = NoFilter) const override;
			virtual bool	exists(const string &name) const override;
			virtual bool	exists() override;
	
			bool exist(string &path);
				
};

#endif 
