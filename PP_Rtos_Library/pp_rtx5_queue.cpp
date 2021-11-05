#include "pp_rtx5_queue.h"


defORTX5TaskQueues::defORTX5TaskQueues(osMessageQueueId_t pqueue, osMutexId_t	pmutex):queue(pqueue), mutex(pmutex){


}


void defORTX5TaskQueues::xQueueSendToBackWithSemaphore(unsigned int data){
	

		if (osMutexAcquire(mutex, osWaitForever) == osOK) osMessageQueuePut (queue, &data, 0, osWaitForever);
		osMutexRelease (mutex); 


}


void defORTX5TaskQueues::xQueueSendConteinerToBackWithSemaphore(vector<int> &data){
	
	if (osMutexAcquire(mutex, osWaitForever) == osOK){
		if(osMessageQueueGetSpace(queue)>2*data.size()){
			for(vector<int>::iterator it=data.begin(); it!=data.end(); ++it){
				osMessageQueuePut (queue, &(*it), 0, osWaitForever);
			}
		}
		osMutexRelease (mutex); 
	}

}
