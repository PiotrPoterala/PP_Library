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


#ifndef PP_DIR_MOCK_H
#define PP_DIR_MOCK_H

#include <string>
#include <vector>
#include "pp_dir.h"
#include "pp_file_info_mock.h"

using namespace std;

class PDirMock : public PDir
{
	private:
		vector<string> pathList;
	
	public:
			PDirMock(const string &path):PDir(path){
					pathList.push_back("folder");
					pathList.push_back("test1.txt");
					pathList.push_back("test2.txt");
					pathList.push_back("test3.txt");
			};
			PDirMock(const char* path):PDir(path){
					pathList.push_back("folder");
					pathList.push_back("test1.txt");
					pathList.push_back("test2.txt");
					pathList.push_back("test3.txt");
			};	

			virtual unsigned int	count()override{
				return pathList.size();
			};
			
			virtual vector<unique_ptr<PFileInfo>>	entryInfoList(PDir::Filters filters = NoFilter) override{
				vector<unique_ptr<PFileInfo>> fileInfoList;
				vector<string> pathList=entryList();

					for(auto it=pathList.begin(); it!=pathList.end(); it++){
						fileInfoList.push_back(make_unique<PFileInfoMock>(absoluteFilePath(*it)));
					}
				
				return fileInfoList;
			};
			
			
			
			virtual vector<string> entryList(PDir::Filters filters = NoFilter)override{
					vector<string> elemList;
					
					for(auto it=pathList.begin(); it!=pathList.end(); it++){
						if(it->find('.')!=string::npos){
							if(filters == NoFilter || filters == Files)elemList.push_back(*it);
						}else{
							if(filters == NoFilter || filters == Dirs)elemList.push_back(*it);
						}
					}
					return elemList;	
				
			};
				

			virtual bool	exists(const string &name) override{
					for(auto it=pathList.begin(); it!=pathList.end(); it++){
						if(it->compare(name)==0){
							return true;
						}
					}
					return false;
				
			}

			virtual bool	exists() override{
					string name=dirName();
					for(auto it=pathList.begin(); it!=pathList.end(); it++){
						if(it->compare(name)==0){
							return true;
						}
					}
					return false;
				
			}
	
				
			virtual bool remove(const string &fileName) override{
				
				for(auto it=pathList.begin(); it!=pathList.end(); it++){
						if(it->compare(fileName)==0){
							pathList.erase(it);
							return true;
						}
					}
					return false;
				
			};
				
};

#endif 
