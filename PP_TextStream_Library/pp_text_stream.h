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

#ifndef _PP_TEXT_STREAM_H
	#define _PP_TEXT_STREAM_H

  #include "stm32xx.h"

	#include "pp_iodevice.h"
	#include <string>
	#include <map>
	using namespace std;

class PTextStream{
		
		private:
			PIOdeviceShrPtr IOdevice;	
		
		public:
			PTextStream(PIOdeviceShrPtr device){IOdevice=device;}
			PTextStream& operator<<(int data);
			PTextStream& operator<<(string &data);
			PTextStream& operator<<(const char *data);
			PTextStream& operator<<(map<char, int> &values);
			
	};

	

#endif
