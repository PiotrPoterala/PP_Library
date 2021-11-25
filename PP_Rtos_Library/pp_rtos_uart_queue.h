#ifndef _UART_QUEUE_H
	#define _UART_QUEUE_H

  #include "stm32xx.h"

	#include <string>
	#include <map>
	
	using namespace std;

	class defOUartQueues{
		
		public:
			defOUartQueues(){};
			virtual ~defOUartQueues(){};
			virtual void portListen()=0;
			virtual void putStringToSendQueueAndStartSend(string &data) =0;
			virtual defOUartQueues& operator<<(string &data)=0;	
			virtual defOUartQueues& operator<<(const char *data)=0;
			virtual defOUartQueues& operator<<(map<char, int> &values)=0;
			virtual int sendSignFromSendQueue() =0;
			virtual void receiveSignAndWriteToReceiveQueue() =0;
			virtual void getStringFromReceiveQueue()=0;
		
		
			virtual bool isReceiveString() =0;
			virtual string getReceiveString() =0;
			virtual void clearReceiveString() =0;
	};


#endif
