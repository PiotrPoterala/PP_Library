#ifndef _UART_QUEUE_DECORATOR_H
	#define _UART_QUEUE_DECORATOR_H

  #include "stm32xx.h"

	#include "pp_rtos_uart_queue.h"
	#include <string>
	
	using namespace std;

class defOUartQueuesDecorator: public defOUartQueues{
		
		private:
			defOUartQueues* uartQueues;	
		
		public:
			defOUartQueuesDecorator(defOUartQueues* uQueues){uartQueues=uQueues;}
			virtual ~defOUartQueuesDecorator(){};
			virtual void portListen() override {uartQueues->portListen();};
			virtual void putStringToSendQueueAndStartSend(string &data) override {uartQueues->putStringToSendQueueAndStartSend(data);};
			virtual defOUartQueues& operator<<(string &data) override{ return uartQueues->operator<<(data);};
			virtual defOUartQueues& operator<<(const char *data) override{return uartQueues->operator<<(data);};
			virtual defOUartQueues& operator<<(map<char, int> &values)override {return uartQueues->operator<<(values);};
			virtual int sendSignFromSendQueue() override {return uartQueues->sendSignFromSendQueue();};
			virtual void receiveSignAndWriteToReceiveQueue() override {uartQueues->receiveSignAndWriteToReceiveQueue();};
			virtual void getStringFromReceiveQueue() override {uartQueues->getStringFromReceiveQueue();};
			
			virtual bool isReceiveString() override {return uartQueues->isReceiveString();};
			virtual string getReceiveString() override {return uartQueues->getReceiveString();};
			virtual void clearReceiveString() override {uartQueues->clearReceiveString();};
	};


#endif
