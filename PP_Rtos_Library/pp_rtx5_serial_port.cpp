/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Piotr Poterała, 2021
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */


#include "pp_rtx5_serial_port.h"
#include "RTX_Config.h"

PSerialPortRTX5::PSerialPortRTX5(USART_TypeDef* UARTx, BaudRate bRate, DataBits dBits, StopBits sBits, Parity par):name(UARTx){

	sendQueue=osMessageQueueNew(128, sizeof(char), NULL);
	receiveQueue=osMessageQueueNew(128, sizeof(char), NULL);

	setBaudRate(bRate);														
	setStopBits(sBits);																	
	setDataBits(dBits);		
	setParity(par);																		
}

void PSerialPortRTX5::setBaudRate(BaudRate bRate){

		baudRateMode=bRate;

	  double divider = ((double)90000000 / (16*baudRateMode));		//PLCK1/(16*BAUD) for oversampling=16    
		name->CR1&=~USART_CR1_OVER8; //oversampling=16 
		name->BRR |= (uint16_t)divider << 4;
		name->BRR |= (uint16_t)((divider-(uint16_t)divider)*16);
	
};
void PSerialPortRTX5::setStopBits(StopBits sBits){

	stopBitsMode=sBits;

	if(sBits==Stop1){
			name->CR2=(name->CR2 & ~USART_CR2_STOP);	
	}else if(sBits==Stop0_5){
		name->CR2=(name->CR2 & ~USART_CR2_STOP) | USART_CR2_STOP_0 ;	
	}else if(sBits==Stop2){
		name->CR2=(name->CR2 & ~USART_CR2_STOP) | USART_CR2_STOP_1 ;	
	}else if(sBits==Stop1_5){
		name->CR2=(name->CR2 & ~USART_CR2_STOP) | USART_CR2_STOP_0 | USART_CR2_STOP_1 ;	
	}
	
};

void PSerialPortRTX5::setDataBits(DataBits dBits){

		dataBitsMode=dBits;

		if(dBits==Data8){
			name->CR1&=~USART_CR1_M;
		}else if(dBits==Data8){
			name->CR1|=USART_CR1_M;
		}
};


void PSerialPortRTX5::setParity(Parity par){
		parityMode=par;
	
		if(par==NoParity){
			name->CR1&=~USART_CR1_PCE;
		}else if(par==EvenParity){
			name->CR1|=USART_CR1_PCE;
			name->CR1&=~USART_CR1_PS;
		}else if(par==OddParity){
			name->CR1|=USART_CR1_PCE;
			name->CR1|=USART_CR1_PS;
		}
		
};

PSerialPortRTX5::PSerialPortRTX5(const PSerialPortRTX5 &serialPort){

	name=serialPort.name;
	baudRateMode=serialPort.baudRateMode;
	stopBitsMode=serialPort.stopBitsMode;
	dataBitsMode=serialPort.dataBitsMode;
	parityMode=serialPort.parityMode;	
	
	
	getStringFlag=serialPort.getStringFlag;
	receiveString=serialPort.receiveString;
	
	
	sendQueue=osMessageQueueNew(128, sizeof(char), NULL);
	receiveQueue=osMessageQueueNew(128, sizeof(char), NULL);

}

PSerialPortRTX5& PSerialPortRTX5::operator=(const PSerialPortRTX5 &serialPort){
	
	name=serialPort.name;
	baudRateMode=serialPort.baudRateMode;
	stopBitsMode=serialPort.stopBitsMode;
	dataBitsMode=serialPort.dataBitsMode;
	parityMode=serialPort.parityMode;	
		
	getStringFlag=serialPort.getStringFlag;
	receiveString=serialPort.receiveString;
	
	if(sendQueue==nullptr)sendQueue=osMessageQueueNew(128, sizeof(char), NULL);
	if(receiveQueue==nullptr)receiveQueue=osMessageQueueNew(128, sizeof(char), NULL);
	
	return (*this);
}


PSerialPortRTX5::~PSerialPortRTX5(){
	
	osMessageQueueDelete(sendQueue);
	osMessageQueueDelete(receiveQueue);
	
}

bool PSerialPortRTX5::open(OpenMode mode){
	
	openMode=mode;
	
	if(mode==ReadOnly || mode==ReadWrite){
		name->CR1&=~USART_CR1_TXEIE;
		name->CR1|=USART_CR1_RE;
	}else if(mode==PIOdevice::WriteOnly){	
		name->CR1&=~USART_CR1_RE;	
		name->CR1|=USART_CR1_TXEIE;
	}
	
	name->CR1|=USART_CR1_TE;
	name->CR1|=USART_CR1_RXNEIE;
	name->CR1|=USART_CR1_UE;	
	openFlag=true;
	return true;
}

bool PSerialPortRTX5::isOpen(){
	return openFlag;
}

bool PSerialPortRTX5::close(){
	
	name->CR1&=~USART_CR1_UE;
	openFlag=false;
	return true;
}


bool PSerialPortRTX5::canReadLine(){
	
	return getStringFlag;
	
	
}

string PSerialPortRTX5::readLine(){
	string returnStr;
	
	if(canReadLine()){
		returnStr=receiveString;
		clear();
	}
	return returnStr;
	
}

void PSerialPortRTX5::clear(){
	
	receiveString.clear();
	getStringFlag=false;
	
}

void PSerialPortRTX5::portListen(){
	
	if(name->SR & USART_SR_RXNE){  
		receiveSignAndWriteToReceiveQueue();
  }else if(name->SR & USART_SR_TXE){  
		sendSignFromSendQueue();
  }
}


bool PSerialPortRTX5::write(string &data){
	bool answer=true;
	
	if(openMode==WriteOnly || openMode==ReadWrite){
		for(auto it: data){
			if(osMessageQueuePut(sendQueue, &it, 0, osWaitForever)==osOK){
				name->CR1&=~USART_CR1_RE;	
				name->CR1|=USART_CR1_TXEIE;
			}else{
				answer=false;
				break;
			}				
		}
	}else{
		answer=false;
	}

	return answer;
}

bool PSerialPortRTX5::write(const char *data){
	bool answer=true;
	
	if(openMode==WriteOnly || openMode==ReadWrite){
		while(*data){
			if(osMessageQueuePut(sendQueue, (data++), 0, osWaitForever)==osOK){
				name->CR1&=~USART_CR1_RE;	
				name->CR1|=USART_CR1_TXEIE;
			}else{
				answer=false;
				break;
			}				
		}
	}else{
		answer=false;
	}
	
	return answer;
}

int PSerialPortRTX5::sendSignFromSendQueue(){
		char sign;	
		osStatus_t status;

		status=osMessageQueueGet(sendQueue, &sign, NULL, 0);
		if(status==osOK){
			name->DR=sign;
		}else{
			if(openMode==ReadOnly || openMode==ReadWrite){
				name->CR1&=~USART_CR1_TXEIE;	
				name->CR1|=USART_CR1_RE;			
			}
		}

		return status;
 }

void PSerialPortRTX5::receiveSignAndWriteToReceiveQueue(){
	char receiveChar;
	
	receiveChar=(uint8_t)(name->DR); 
	osMessageQueuePut (receiveQueue, &receiveChar, 0, 0); 
	
}

bool PSerialPortRTX5::waitForReadyRead(int usec){
		char receiveChar;
		int tick;
	
		if(usec==osWaitForever){
			tick=osWaitForever;
		}else{
			tick=(OS_TICK_FREQ/1000000)*usec;
		}
	
		if(getStringFlag==false){
			if(osMessageQueueGet(receiveQueue, &receiveChar, NULL, tick) == osOK){

				receiveString+=receiveChar; 

				if(receiveChar=='\n'){

					getStringFlag=true;

				}else if(receiveString.size()>64){
						receiveString.clear();
					
				}
				return true;
			}  
		}
		
		return false;
	
}

