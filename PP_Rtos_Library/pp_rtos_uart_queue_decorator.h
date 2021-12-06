/**
 * @author  Piotr Poterała
 * @email   poterala.piotr@gmail.com
 * @website http://zappp.pl
 * @version v1.0
 * @ide     Keil uVision 5
 * @license GNU GPL v3
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Piotr Poterała, 2021
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */

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
