#include <stdio.h>
#include "input_signals_analysis.h"


defOCheckSignals::defOCheckSignals(){
	
	currCheckingSetSignals=0;
	checkedSetSignals=0;
	currCheckingResetSignals=0;
	checkedResetSignals=0;
	madeSignals=0;
	
}

void defOCheckSignals::checkSignal(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t mask){
	
		checkSetSignal(GPIOx, GPIO_Pin, mask);
		checkResetSignal(GPIOx, GPIO_Pin, mask);
	
}


void defOCheckSignals::checkSetSignal(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t mask){
			
			
		if(!(currCheckingSetSignals & mask)){
			if(KEY_SELECT(GPIOx->IDR, GPIO_Pin)==B_HIGH)currCheckingSetSignals|=mask; 
		}else{
			if(KEY_SELECT(GPIOx->IDR, GPIO_Pin)==B_HIGH)checkedSetSignals|=mask;
			else{
				currCheckingSetSignals&=~mask;
				checkedSetSignals&=~mask;
			}
		}

}

void defOCheckSignals::checkResetSignal(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t mask){
			
			
		if(!(currCheckingResetSignals & mask)){
			if(KEY_SELECT(GPIOx->IDR, GPIO_Pin)==B_LOW)currCheckingResetSignals|=mask; 
		}else{
			if(KEY_SELECT(GPIOx->IDR, GPIO_Pin)==B_LOW)checkedResetSignals|=mask;
			else{
				currCheckingResetSignals&=~mask;
				checkedResetSignals&=~mask;
			}
		}

}



//void defOCheckSignals::checkGroupOfSignals(GPIO_TypeDef* GPIOx, uint32_t mask){
//			
//			
//		if((currCheckingSetSignals & mask)  == (GPIOx->IDR & mask)){
//			checkedSetSignals=currCheckingSetSignals;
//		}else{
//			currCheckingSetSignals = (currCheckingSetSignals & ~mask) | (GPIOx->IDR & mask);
//		}

//}


