#ifndef _PP_IODEVICE_H
	#define _PP_IODEVICE_H

		#include "stm32xx.h"
		
		#include <string>

		using namespace std;

		class PIOdevice{		
			
			public:
				enum{ReadOnly=1, WriteOnly, ReadWrite};
			
			
				PIOdevice(){};	
				virtual ~PIOdevice(){};
					
				virtual bool isOpen()=0;
				virtual int pos(){return 0;};
				virtual bool atEnd(){return false;};
			
				virtual bool open(int mode=ReadWrite)=0;
				virtual bool close()=0;
				virtual bool seek(int pos){return true;};
				virtual bool write(string &data)=0;
				virtual bool write(const char *data)=0;
				virtual string readLine()=0;
				virtual bool canReadLine()=0;
			
				virtual void portListen(){};
				virtual void receiveQueueListen(){};

		};
#endif