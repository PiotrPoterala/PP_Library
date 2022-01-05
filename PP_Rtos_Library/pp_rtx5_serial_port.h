
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
	#include "pp_iodevice.h"
	
	
	#include "cmsis_os2.h"
	

class PSerialPortRTX5 : public PIOdevice{
		
		private:
			USART_TypeDef* port;
			osMessageQueueId_t receiveQueue;
			osMessageQueueId_t sendQueue;
		
			bool openFlag=false;
			int openMode;
		
			bool getStringFlag=false;
			string receiveString;
		
		public:
			PSerialPortRTX5(USART_TypeDef* UARTx);
			PSerialPortRTX5(const PSerialPortRTX5 &serialPort);
			PSerialPortRTX5& operator=(const PSerialPortRTX5 &serialPort);
			virtual ~PSerialPortRTX5();
			virtual bool open(int mode)override ;
			virtual bool isOpen()override ;
			virtual int mode() override {return openMode;};
			virtual bool close()override ;
			virtual void portListen() override ;
			virtual bool write(string &data) override;
			virtual bool write(const char *data) override ;

			int sendSignFromSendQueue();
			void receiveSignAndWriteToReceiveQueue();
		
			virtual void receiveQueueListen() override;
		
			virtual bool canReadLine() override ;
			virtual string readLine() override ;
	//		virtual void clearReceiveString() override ;

	};




#endif
