
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
			defOUartRTX5queues(const defOUartRTX5queues &uartQueues);
			defOUartRTX5queues& operator=(const defOUartRTX5queues &uartQueues);
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
