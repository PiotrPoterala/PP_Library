#include "pp_rtx5_uart_queue.h"


defOUartRTX5queues::defOUartRTX5queues(USART_TypeDef* UARTx):port(UARTx){

	sendQueue=osMessageQueueNew(128, sizeof(char), NULL);
	receiveQueue=osMessageQueueNew(128, sizeof(char), NULL);

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

