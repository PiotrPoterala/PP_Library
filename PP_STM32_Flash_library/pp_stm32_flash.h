#ifndef _PP_STM32_FLASH_H
	#define _PP_STM32_FLASH_H

		#include "stm32xx.h"
		#include "pp_iodevice.h"
		
		#include <string>
		#include <vector>
		#include <initializer_list>

		#include "ff.h"

		using namespace std;
		

		typedef struct{
			unsigned int number;
			unsigned int firstAdress;
			unsigned int areaSize;
		}STM32FlashPage;

		
		using FlashAreaDescList = vector<STM32FlashPage>;
		
		class PSTM32Flash : public PIOdevice{
			private:
				FlashAreaDescList pages;
			
				bool openFlag=false;
				OpenMode openMode;
			
				unsigned int position;
				unsigned int* focusAdress;
			public:
				PSTM32Flash()=delete;	
				PSTM32Flash(const PSTM32Flash &other);
				PSTM32Flash(FlashAreaDescList &page);
				PSTM32Flash(initializer_list<STM32FlashPage> page);
				PSTM32Flash& operator=(const PSTM32Flash &other);
			
				virtual int size() override ;
				virtual bool isOpen() override ;
				virtual int pos() override ;
				virtual bool atEnd() override ;
				virtual OpenMode mode() override {return openMode;};
			
				virtual bool open(OpenMode mode) override ;
				virtual bool close() override ;
				virtual bool seek(int pos) override ;
				virtual bool write(int data) override ;
				virtual int read() override;
			
				bool clear();

		};
		
		using PSTM32FlashShrPtr =shared_ptr<PSTM32Flash>;
#endif
