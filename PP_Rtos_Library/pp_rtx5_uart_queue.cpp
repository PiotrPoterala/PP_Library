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


#include "pp_rtx5_uart_queue.h"


defOUartRTX5queues::defOUartRTX5queues(USART_TypeDef* UARTx):port(UARTx){

	sendQueue=osMessageQueueNew(128, sizeof(char), NULL);
	receiveQueue=osMessageQueueNew(128, sizeof(char), NULL);

}


defOUartRTX5queues::defOUartRTX5queues(const defOUartRTX5queues &uartQueues){

	port=uartQueues.port;
		
	getStringFlag=uartQueues.getStringFlag;
	receiveString=uartQueues.receiveString;
	
	
	sendQueue=osMessageQueueNew(128, sizeof(char), NULL);
	receiveQueue=osMessageQueueNew(128, sizeof(char), NULL);

}

defOUartRTX5queues& defOUartRTX5queues::operator=(const defOUartRTX5queues &uartQueues){
	
	port=uartQueues.port;
		
	getStringFlag=uartQueues.getStringFlag;
	receiveString=uartQueues.receiveString;
	
	if(sendQueue==nullptr)sendQueue=osMessageQueueNew(128, sizeof(char), NULL);
	if(receiveQueue==nullptr)receiveQueue=osMessageQueueNew(128, sizeof(char), NULL);
	
	return (*this);
}


defOUartRTX5queues::~defOUartRTX5queues(){
	
	osMessageQueueDelete(sendQueue);
	osMessageQueueDelete(receiveQueue);
	
}

bool defOUartRTX5queues::isReceiveString(){
	
	return getStringFlag;
	
	
}

string defOUartRTX5queues::getReceiveString(){
	
	return receiveString;
	
	
}

void defOUartRTX5queues::clearReceiveString(){
	
	receiveString.clear();
	getStringFlag=false;
	
}

void defOUartRTX5queues::portListen(){
	
	if(port->SR & USART_SR_RXNE){  
		receiveSignAndWriteToReceiveQueue();
  }else if(port->SR & USART_SR_TXE){  
		sendSignFromSendQueue();
  }
}


void defOUartRTX5queues::putStringToSendQueueAndStartSend(string &data){
	
		for(auto it: data){
			if(osMessageQueuePut(sendQueue, &it, 0, osWaitForever)==osOK){
				port->CR1&=~USART_CR1_RE;	
				port->CR1|=USART_CR1_TXEIE;
			}	
			
		}


}

defOUartQueues& defOUartRTX5queues::operator<<(string &data){
	
	putStringToSendQueueAndStartSend(data);
	
	return (*this);
}

defOUartQueues& defOUartRTX5queues::operator<<(const char *data){
	
	string str(data);
	
	putStringToSendQueueAndStartSend(str);
	return (*this);
}

defOUartQueues& defOUartRTX5queues::operator<<(map<char, int> &values){
	
	string str;
	
	for(auto it=values.begin(); it!=values.end(); it++){
		str+=(*it).first;
		str+=to_string((*it).second);
		str+=" ";
	}
	
	
	putStringToSendQueueAndStartSend(str);
	return (*this);
}


int defOUartRTX5queues::sendSignFromSendQueue(){
		char sign;	
		osStatus_t status;

		status=osMessageQueueGet(sendQueue, &sign, NULL, 0);
		if(status==osOK){
			port->DR=sign;
		}else{
			port->CR1&=~USART_CR1_TXEIE;	
			port->CR1|=USART_CR1_RE;			
		}

		return status;
 }

void defOUartRTX5queues::receiveSignAndWriteToReceiveQueue(){
	char receiveChar;
	
	receiveChar=(uint8_t)(port->DR); 
	osMessageQueuePut (receiveQueue, &receiveChar, 0, 0); 
	
}


void defOUartRTX5queues::getStringFromReceiveQueue(){
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

