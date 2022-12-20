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

#ifndef _RTX5_SERIAL_PORT_H
	#define _RTX5_SERIAL_PORT_H

  #include "stm32xx.h"
	#include "pp_iodevice.h"
	
	
	#include "cmsis_os2.h"
	#include "RTX_Config.h"
	

class PSerialPortRTX5 : public PIOdevice{
		
		public:
			enum	BaudRate {Baud1200=1200, Baud2400=2400, Baud4800=4800, Baud9600=9600, Baud19200=19200};
			enum	DataBits {Data8, Data9};
			enum	StopBits {Stop1, Stop0_5, Stop2, Stop1_5};
			enum	Parity {NoParity, EvenParity, OddParity};	
	
		private:
			USART_TypeDef* name;
			BaudRate baudRateMode;
			StopBits stopBitsMode;
			DataBits dataBitsMode;
			Parity parityMode;
		
			osMessageQueueId_t receiveQueue;
			osMessageQueueId_t sendQueue;
		
			bool openFlag=false;
			OpenMode openMode;
		
			bool getStringFlag=false;
			string receiveString;
		
		public:
			PSerialPortRTX5(USART_TypeDef* UARTx, BaudRate bRate=Baud9600, DataBits dBits=Data8, StopBits sBits=Stop1, Parity par=NoParity);
			PSerialPortRTX5(const PSerialPortRTX5 &serialPort);
			PSerialPortRTX5& operator=(const PSerialPortRTX5 &serialPort);
			virtual ~PSerialPortRTX5();
		
			BaudRate baudRate(){return baudRateMode;};
			StopBits stopBits(){return stopBitsMode;};
			DataBits dataBits(){return dataBitsMode;};
			Parity parity(){return parityMode;};
		
			void setBaudRate(BaudRate bRate);
			void setStopBits(StopBits sBits);
			void setDataBits(DataBits dBits);
			void setParity(Parity par);
		
			virtual bool open(OpenMode mode)override ;
			virtual bool close()override ;
			virtual void portListen() override ;
			virtual bool write(string &data) override;
			virtual bool write(const char *data) override ;

			void clear();
			int sendSignFromSendQueue();
			void receiveSignAndWriteToReceiveQueue();
		
			virtual bool waitForReadyRead(int usec) override;
		
			virtual bool canReadLine() override ;
			virtual string readLine() override ;

	};




#endif
