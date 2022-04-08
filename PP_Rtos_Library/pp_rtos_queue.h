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

#ifndef _RTOS_QUEUE_H
	#define _RTOS_QUEUE_H

  #include "stm32xx.h"

	#include <vector>
	#include <map>
	
	using namespace std;

	template <typename Type>
	class defOTaskQueues{
		
		
		public:
			static_assert	(std::is_arithmetic<Type>::value, "<Type> must be integral or a floating point type");
		
			defOTaskQueues(){};
			virtual ~defOTaskQueues(){};
			virtual void xQueueSendToBackWithSemaphore(Type data)=0;
			virtual void xQueueSendConteinerToBackWithSemaphore(vector<Type> &data)=0;
			virtual int xQueueReceive(Type* data, unsigned int timeoutValue)=0;
			virtual void xQueueReceiveMap(map<char, Type> &data, int lines, unsigned int timeoutValue)=0;
		
	};

	using defOTaskQueuesIntShrPtr = shared_ptr<defOTaskQueues<int>>;

#endif