#ifndef _PP_IODEVICE_H
	#define _PP_IODEVICE_H

		#include "stm32xx.h"
		
		#include <string>

		#include "ff.h"

		using namespace std;

		class PIOdevice{		
			private:
				bool openFlag;
				int position;
			
			public:
				PIOdevice();	
				virtual ~PIOdevice();
					
				virtual bool isOpen();
				virtual int pos();
				virtual bool atEnd();
			
				virtual bool open();
				virtual bool close();
				virtual bool seek(int pos);
				virtual bool write(string *data);
				virtual bool write(const char *data);
				virtual string readLine();
				virtual bool canReadLine();
			

		};
#endif