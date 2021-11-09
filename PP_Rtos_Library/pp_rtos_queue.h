#ifndef _RTOS_QUEUE_H
	#define _RTOS_QUEUE_H

  #include "stm32xx.h"

	#include <vector>
	
	using namespace std;

	class defOTaskQueues{
		
		
		public:
			defOTaskQueues(){};

			virtual void xQueueSendToBackWithSemaphore(unsigned int data)=0;
			virtual void xQueueSendConteinerToBackWithSemaphore(vector<int> &data)=0;
		
	};


#endif