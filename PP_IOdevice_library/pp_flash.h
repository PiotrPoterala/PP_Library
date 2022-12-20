#ifndef _PP_FLASH_H
	#define _PP_FLASH_H

		#include "pp_iodevice.h"
		
		#include <string>
		#include <vector>
		#include <initializer_list>


		using namespace std;
		

		typedef struct{
			unsigned int number;
			unsigned int firstAdress;
			unsigned int areaSize;
		}FlashPage;

		
		using FlashAreaDescList = vector<FlashPage>;
		
		class PFlash : public PIOdevice{
			protected:
				FlashAreaDescList pages;
			
				unsigned int *focusReadAdress;
				unsigned int *focusWriteAdress;
			
			public:
				PFlash()=delete;	
				PFlash(FlashAreaDescList &page);
				PFlash(initializer_list<FlashPage> page);
			
				virtual bool open(OpenMode mode) override ;
				virtual bool close() override ;
				
				virtual int pos() override ;
				virtual bool atEnd() override ;
				virtual bool seek(int pos) override ;
				virtual int read() override;
			
				virtual int size() override ;
				virtual bool writeAtTheEnd(int data) override;
			
				virtual bool clear();

		};
		
		using PFlashShrPtr =shared_ptr<PFlash>;
#endif
