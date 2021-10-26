#ifndef _UART_QUEUE_H
	#define _UART_QUEUE_H

  #include "stm32xx.h"

	#include <string>
	
	using namespace std;

	class defOUartQueues{
		
		protected:
			USART_TypeDef* port;	
		
			bool getStringFlag;
			string receiveString;
		
		public:
			defOUartQueues(USART_TypeDef* UARTx);
		
			virtual void putStringToSendQueueAndStartSend(string &data)=0;
			virtual int sendSignFromSendQueue()=0;
			virtual void receiveSignAndWriteToReceiveQueue()=0;
			virtual void getStringFromReceiveQueue()=0;
			bool isReceiveString();
			string getReceiveString();
			void clearReceiveString();
	};


#endif
