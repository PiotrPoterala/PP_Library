#include "pp_rtx5_uart_queue.h"


defOUartRTX5queues::defOUartRTX5queues(USART_TypeDef* UARTx, osMessageQueueId_t qSend, osMessageQueueId_t qReceive):port(UARTx), sendQueue(qSend), receiveQueue(qReceive){


}


void defOUartRTX5queues::putStringToSendQueueAndStartSend(string &data){
	
		for(string::iterator it=data.begin(); it!=data.end();  ++it){
			if(osMessageQueuePut(sendQueue, &(*it), 0, osWaitForever)==osOK){
				port->CR1&=~USART_CR1_RE;	
				port->CR1|=USART_CR1_TXEIE;
			}	
			
		}


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

				}else{
					if(receiveString.size()>64)receiveString.clear();
				}

			}  
		}
	
}

