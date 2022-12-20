#ifndef _PP_STM32_FLASH_H
	#define _PP_STM32_FLASH_H

		#include "stm32xx.h"
		#include "pp_flash.h"
		
		#include <string>
		#include <vector>
		#include <initializer_list>


		using namespace std;
		

		class PSTM32Flash : public PFlash{

			public:
				PSTM32Flash()=delete;	
				PSTM32Flash(FlashAreaDescList &page):PFlash(page){};
				PSTM32Flash(initializer_list<FlashPage> page):PFlash(page){};
			
				virtual bool writeAtTheEnd(int data) override;	
				virtual bool clear()override;

		};
		
		using PSTM32FlashShrPtr =shared_ptr<PSTM32Flash>;
#endif
