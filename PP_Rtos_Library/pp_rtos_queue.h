#ifndef _RTOS_QUEUE_H
	#define _RTOS_QUEUE_H

  #include "stm32xx.h"

	#include <vector>
	#include <map>
	
	using namespace std;

	template <typename Type>
	class defOTaskQueues{
		
		
		public:
			defOTaskQueues(){};

			virtual void xQueueSendToBackWithSemaphore(Type data)=0;
			virtual void xQueueSendConteinerToBackWithSemaphore(vector<Type> &data)=0;
			virtual int xQueueReceive(Type* data, unsigned int timeoutValue)=0;
			virtual void xQueueReceiveMap(map<char, Type> &data, int lines, unsigned int timeoutValue)=0;
		
	};


#endif