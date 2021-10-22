#ifndef _INPUT_SIGNALS_ANALYSIS_H
	#define _INPUT_SIGNALS_ANALYSIS_H

	#include "stm32l4xx.h"

	#define KEY_SELECT(PORT, PIN) (((PORT & PIN)>0)?1:0)	

	enum { 
		B_LOW=0,
		B_HIGH=1
	};

	class defOCheckSignals{
		public:
			defOCheckSignals();
		
	

			uint32_t currCheckingSetSignals;
			uint32_t checkedSetSignals;
			uint32_t currCheckingResetSignals;
			uint32_t checkedResetSignals;
			uint32_t madeSignals;
			
			void checkSignal(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t mask);
			void checkSetSignal(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t mask);
			void checkResetSignal(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint32_t mask);
	};


#endif
