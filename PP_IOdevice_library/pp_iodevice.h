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
				virtual int mode()=0;
			
				virtual bool open(int mode=ReadWrite)=0;
				virtual bool close()=0;
				virtual bool write(string &data)=0;
				virtual bool write(const char *data)=0;
				virtual string readLine()=0;
				virtual bool canReadLine()=0;
			
				//file
				virtual bool seek(int pos){return true;};
				virtual int size(){return 0;};
				virtual int pos(){return 0;};
				virtual bool atEnd(){return false;};
				
				//uart
				virtual void portListen(){};
				virtual void receiveQueueListen(){};

		};
#endif