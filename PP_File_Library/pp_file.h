#ifndef _PP_FILE_H
	#define _PP_FILE_H

		#include "stm32xx.h"
		#include "pp_iodevice.h"
		
		#include <string>

		#include "ff.h"

		using namespace std;

		class PVolume{
			
			public:
				char volume;
				FATFS g_sFatFs;
			
		}

		class PFile : public PIOdevice{
			private:
				string path;
				PVolume *volume;
				FIL file;
			
			public:
				
				PFile(PVolume *volume, const char* path);	
			
				virtual int size();
				virtual bool isOpen();
				virtual int pos();
				virtual bool atEnd();
				virtual int mode() override {return mode;};
			
				virtual bool open(int mode);
				virtual bool close();
				virtual bool seek(int pos);
				virtual bool write(string *data);
				virtual bool write(const char *data);
				bool writeAtTheEnd(string *data);
				bool writeAtTheEnd(const char *data);
				virtual string readLine();
			
	//			PFile& operator<<(const char *data);
			
				bool clear();

		};
#endif
