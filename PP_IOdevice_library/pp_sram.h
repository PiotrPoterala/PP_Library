#ifndef _PP_SRAM_H
	#define _PP_SRAM_H


	#include "pp_iodevice.h"
	#include <stdbool.h>

		using namespace std;
	
	class PSRam : public PIOdevice{
		
		protected:
			unsigned int firstAdress;
			unsigned int areaSize;
			unsigned int *focusAdress;
			
		public:
			PSRam()=delete;
			PSRam(unsigned int firstAdress, unsigned int areaSize);
	
			virtual bool open(OpenMode mode=ReadWrite) override;
			virtual bool close() override;
				
			virtual bool write(int data) override;
			virtual int read() override;
			
		
			virtual bool seek(int pos) override;
			virtual int pos() override;
			virtual bool atEnd() override;
			virtual int size() override ;

			bool clear();
		
	};
	
#endif
