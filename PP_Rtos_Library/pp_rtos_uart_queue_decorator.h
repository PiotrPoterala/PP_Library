#ifndef _UART_QUEUE_DECORATOR_H
	#define _UART_QUEUE_DECORATOR_H

  #include "stm32xx.h"

	#include "pp_rtos_uart_queue.h"
	#include <string>
	
	using namespace std;

class defOUartQueuesDecorator: public defOUartQueues{
		
		protected:
			defOUartQueues* uartQueues;	
		
		public:
			defOUartQueuesDecorator(defOUartQueues* uQueues):uartQueues(uQueues){};
		
			virtual void putStringToSendQueueAndStartSend(string &data){uartQueues->putStringToSendQueueAndStartSend(data);};
			virtual int sendSignFromSendQueue(){return uartQueues->sendSignFromSendQueue();};
			virtual void receiveSignAndWriteToReceiveQueue(){uartQueues->receiveSignAndWriteToReceiveQueue();};
			virtual void getStringFromReceiveQueue(){uartQueues->getStringFromReceiveQueue();};
	};


#endif
