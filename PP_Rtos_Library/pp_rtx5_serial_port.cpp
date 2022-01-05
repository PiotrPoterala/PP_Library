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


PSerialPortRTX5::PSerialPortRTX5(USART_TypeDef* UARTx):port(UARTx){

	sendQueue=osMessageQueueNew(128, sizeof(char), NULL);
	receiveQueue=osMessageQueueNew(128, sizeof(char), NULL);

}


PSerialPortRTX5::PSerialPortRTX5(const PSerialPortRTX5 &serialPort){

	port=serialPort.port;
		
	getStringFlag=serialPort.getStringFlag;
	receiveString=serialPort.receiveString;
	
	
	sendQueue=osMessageQueueNew(128, sizeof(char), NULL);
	receiveQueue=osMessageQueueNew(128, sizeof(char), NULL);

}

PSerialPortRTX5& PSerialPortRTX5::operator=(const PSerialPortRTX5 &serialPort){
	
	port=serialPort.port;
		
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

bool PSerialPortRTX5::open(int mode){
	
	openMode=mode;
	
	if(mode==ReadOnly || mode==ReadWrite){
		port->CR1&=~USART_CR1_TXEIE;
		port->CR1|=USART_CR1_RE;
	}else if(mode==PIOdevice::WriteOnly){	
		port->CR1&=~USART_CR1_RE;	
		port->CR1|=USART_CR1_TXEIE;
	}
	
	port->CR1|=USART_CR1_TE;
	port->CR1|=USART_CR1_RXNEIE;
	port->CR1|=USART_CR1_UE;	
	openFlag=true;
	return true;
}

bool PSerialPortRTX5::isOpen(){
	return openFlag;
}

bool PSerialPortRTX5::close(){
	
	port->CR1&=~USART_CR1_UE;
	openFlag=false;
	return true;
}


bool PSerialPortRTX5::canReadLine(){
	
	return getStringFlag;
	
	
}

string PSerialPortRTX5::readLine(){
	
	string returnStr=receiveString;
	receiveString.clear();
	getStringFlag=false;
	return returnStr;
	
	
}

//void PSerialPortRTX5::clearReceiveString(){
//	
//	receiveString.clear();
//	getStringFlag=false;
//	
//}

void PSerialPortRTX5::portListen(){
	
	if(port->SR & USART_SR_RXNE){  
		receiveSignAndWriteToReceiveQueue();
  }else if(port->SR & USART_SR_TXE){  
		sendSignFromSendQueue();
  }
}


bool PSerialPortRTX5::write(string &data){
	bool answer=true;
	
	if(openMode==WriteOnly || openMode==ReadWrite){
		for(auto it: data){
			if(osMessageQueuePut(sendQueue, &it, 0, osWaitForever)==osOK){
				port->CR1&=~USART_CR1_RE;	
				port->CR1|=USART_CR1_TXEIE;
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
		while(*(data++)){
			if(osMessageQueuePut(sendQueue, data, 0, osWaitForever)==osOK){
				port->CR1&=~USART_CR1_RE;	
				port->CR1|=USART_CR1_TXEIE;
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
			port->DR=sign;
		}else{
			if(openMode==ReadOnly || openMode==ReadWrite){
				port->CR1&=~USART_CR1_TXEIE;	
				port->CR1|=USART_CR1_RE;			
			}
		}

		return status;
 }

void PSerialPortRTX5::receiveSignAndWriteToReceiveQueue(){
	char receiveChar;
	
	receiveChar=(uint8_t)(port->DR); 
	osMessageQueuePut (receiveQueue, &receiveChar, 0, 0); 
	
}


void PSerialPortRTX5::receiveQueueListen(){
	char receiveChar;
	
		if(getStringFlag==false){
			if(osMessageQueueGet(receiveQueue, &receiveChar, NULL, osWaitForever) == osOK){

				receiveString+=receiveChar; 

				if(receiveChar=='\n'){

					getStringFlag=true;

				}else if(receiveString.size()>64){
						receiveString.clear();
					
				}

			}  
		}
	
}

