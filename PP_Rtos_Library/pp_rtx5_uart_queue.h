#ifndef _RTX5_UART_QUEUE_H
	#define _RTX5_UART_QUEUE_H

  #include "stm32xx.h"
	#include "pp_rtos_uart_queue.h"
	
	#include "cmsis_os2.h"
	
	using namespace std;


class defOUartRTX5queues : public defOUartQueues{
		
		private:
			USART_TypeDef* port;
			osMessageQueueId_t receiveQueue;
			osMessageQueueId_t sendQueue;
		
			bool getStringFlag=false;
			string receiveString;
		
		public:
			defOUartRTX5queues(USART_TypeDef* UARTx);
			virtual ~defOUartRTX5queues();
			virtual void portListen() override ;
			virtual void putStringToSendQueueAndStartSend(string &data) override ;
			virtual defOUartQueues& operator<<(string &data) override;	
			virtual defOUartQueues& operator<<(const char *data) override;
		
			virtual defOUartQueues& operator<<(map<char, int> &values)override;
		
			virtual int sendSignFromSendQueue() override ;
			virtual void receiveSignAndWriteToReceiveQueue() override ;
			virtual void getStringFromReceiveQueue() override ;
		
			virtual bool isReceiveString() override ;
			virtual string getReceiveString() override ;
			virtual void clearReceiveString() override ;

	};




#endif
