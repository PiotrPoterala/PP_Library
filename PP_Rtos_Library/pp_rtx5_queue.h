#ifndef _RTX5_QUEUE_H
	#define _RTX5_QUEUE_H

  #include "stm32xx.h"
	#include "pp_rtos_queue.h"
	#include <vector>
	
	#include "cmsis_os2.h"
	
	using namespace std;


class defORTX5TaskQueues : public defOTaskQueues{
		
		private:
			osMessageQueueId_t queue;
			osMutexId_t	mutex;
		
		public:
			defORTX5TaskQueues(osMessageQueueId_t pqueue, osMutexId_t	pmutex);
	
			virtual void xQueueSendToBackWithSemaphore(unsigned int data);
			virtual void xQueueSendConteinerToBackWithSemaphore(vector<int> &data);

	};




#endif
