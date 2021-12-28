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

#ifndef _RTX5_QUEUE_H
	#define _RTX5_QUEUE_H

	#include "pp_rtos_queue.h"
	#include <vector>
	
	#include "cmsis_os2.h"

template <typename Type>
class defORTX5TaskQueues : public defOTaskQueues<Type>{
		
		private:
			osMessageQueueId_t queue;
			osMutexId_t	mutex;
		
		public:
		defORTX5TaskQueues();
		defORTX5TaskQueues(const defORTX5TaskQueues &taskQueues);
		defORTX5TaskQueues& operator=(const defORTX5TaskQueues &taskQueues);
		virtual ~defORTX5TaskQueues();
	
		virtual void xQueueSendToBackWithSemaphore(Type data);
		virtual void xQueueSendConteinerToBackWithSemaphore(vector<Type> &data);
		virtual int xQueueReceive(Type* data, unsigned int timeoutValue);
		virtual void xQueueReceiveMap(map<char, Type> &data, int lines, unsigned int timeoutValue);

	};

template <typename Type>
defORTX5TaskQueues<Type>::defORTX5TaskQueues(){
			queue=osMessageQueueNew(64, sizeof(Type), NULL);
			mutex=osMutexNew(NULL);
};

template <typename Type>
defORTX5TaskQueues<Type>::defORTX5TaskQueues(const defORTX5TaskQueues<Type> &taskQueues){
			queue=osMessageQueueNew(64, sizeof(Type), NULL);
			mutex=osMutexNew(NULL);
};

template <typename Type>
defORTX5TaskQueues<Type>& defORTX5TaskQueues<Type>::operator=(const defORTX5TaskQueues<Type> &taskQueues){
			if(queue==nullptr)queue=osMessageQueueNew(64, sizeof(Type), NULL);
			if(mutex==nullptr)mutex=osMutexNew(NULL);
	
			return (*this);
};

template <typename Type>
defORTX5TaskQueues<Type>::~defORTX5TaskQueues(){
	
	osMessageQueueDelete(queue);
	osMutexDelete(mutex);
	
}

template <typename Type>
void defORTX5TaskQueues<Type>::xQueueSendToBackWithSemaphore(Type data){
	

		if (osMutexAcquire(mutex, osWaitForever) == osOK) osMessageQueuePut (queue, &data, 0, osWaitForever);
		osMutexRelease (mutex); 
}

template <typename Type>
void defORTX5TaskQueues<Type>::xQueueSendConteinerToBackWithSemaphore(vector<Type> &data){
	
	if (osMutexAcquire(mutex, osWaitForever) == osOK){
		if(osMessageQueueGetSpace(queue)>data.size()){
			for(int i=0; i<data.size(); i++){
				osMessageQueuePut (queue, &data.at(i), 0, osWaitForever);
			}
		}
		osMutexRelease (mutex); 
	}

}

template <typename Type>
int defORTX5TaskQueues<Type>::xQueueReceive(Type* data, unsigned int timeoutValue){
	
	return osMessageQueueGet(queue, data, NULL, timeoutValue);
}

template <typename Type>
void defORTX5TaskQueues<Type>::xQueueReceiveMap(map<char, Type> &data, int lines, unsigned int timeoutValue){
	
		char acronim='\0';
		int receiveData, rData=0;
		for(int i=0; i<lines; i++){
			acronim='\0';
			rData=0;
			if(xQueueReceive(&receiveData, osWaitForever) == osOK)acronim=receiveData;
			if(xQueueReceive(&receiveData, osWaitForever) == osOK)rData=receiveData;
			data.insert(pair<char, int>(acronim, rData));	
		}
	
}


#endif
