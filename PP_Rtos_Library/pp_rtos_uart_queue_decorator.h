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

	#include "pp_iodevice.h"
	#include <string>
	
	using namespace std;

class PIOdeviceDecorator: public PIOdevice{
		
		private:
			PIOdevice* IOdevice;	
		
		public:
			PIOdeviceDecorator(PIOdevice* device){IOdevice=device;}
			virtual ~PIOdeviceDecorator(){};
			virtual bool open(int mode)override {return IOdevice->open(mode);};
			virtual bool isOpen()override {return IOdevice->isOpen();};
			virtual bool close()override {return IOdevice->close();};
			virtual void portListen() override {IOdevice->portListen();};
			virtual bool write(string &data) override {return IOdevice->write(data);};
			virtual bool write(const char *data) override {return IOdevice->write(data);};
//			virtual defOUartQueues& operator<<(string &data) override{ return uartQueues->operator<<(data);};
//			virtual defOUartQueues& operator<<(const char *data) override{return uartQueues->operator<<(data);};
//			virtual defOUartQueues& operator<<(map<char, int> &values)override {return uartQueues->operator<<(values);};
			virtual void receiveQueueListen() override {IOdevice->receiveQueueListen();};
			
			virtual bool canReadLine() override {return IOdevice->canReadLine();};
			virtual string readLine() override {return IOdevice->readLine();};
	};

	

#endif
