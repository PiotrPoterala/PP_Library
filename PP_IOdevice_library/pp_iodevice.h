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

#ifndef _PP_IODEVICE_H
	#define _PP_IODEVICE_H
		
		#include <string>

		using namespace std;

		class PIOdevice{		
			
			public:
				enum OpenMode{ReadOnly=1, WriteOnly, ReadWrite};
			
				PIOdevice(){};	
				virtual ~PIOdevice(){};
					
				virtual bool isOpen()=0;
				virtual OpenMode mode()=0;
			
				virtual bool open(OpenMode mode=ReadWrite)=0;
				virtual bool close()=0;
				virtual bool write(string &data)=0;
				virtual bool write(const char *data)=0;
				virtual string readLine()=0;
				virtual bool canReadLine(){return true;};
			
				//file
				virtual bool seek(int pos){return true;};
				virtual int size(){return 0;};
				virtual int pos(){return 0;};
				virtual bool atEnd(){return false;};
				virtual bool exists(){return true;};
				
				//uart
				virtual void portListen(){};
				virtual bool waitForReadyRead(int usec){return true;};
				


		};
#endif