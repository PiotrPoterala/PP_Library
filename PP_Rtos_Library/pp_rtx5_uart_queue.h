#ifndef _RTX5_UART_QUEUE_H
	#define _RTX5_UART_QUEUE_H

  #include "stm32xx.h"
	#include "pp_rtos_uart_queue.h"
	
	#include "cmsis_os2.h"
	
	using namespace std;


class defOUartRTX5queues : public defOUartQueues{
		
		private:
			osMessageQueueId_t receiveQueue;
			osMessageQueueId_t sendQueue;
		
		public:
			defOUartRTX5queues(USART_TypeDef* UARTx, osMessageQueueId_t qSend, osMessageQueueId_t qReceive);
	
			virtual void putStringToSendQueueAndStartSend(string &data);
			virtual int sendSignFromSendQueue();
			virtual void receiveSignAndWriteToReceiveQueue();
			virtual void getStringFromReceiveQueue();

	};




#endif
