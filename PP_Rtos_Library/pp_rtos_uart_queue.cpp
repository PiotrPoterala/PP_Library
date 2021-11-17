#include "pp_rtos_uart_queue.h"



bool defOUartQueues::isReceiveString(){
	
	return getStringFlag;
	
	
}

string defOUartQueues::getReceiveString(){
	
	return receiveString;
	
	
}

void defOUartQueues::clearReceiveString(){
	
	receiveString.clear();
	getStringFlag=false;
	
}
