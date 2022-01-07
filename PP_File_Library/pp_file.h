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
			
		};

		class PFile : public PIOdevice{
			private:
				string path;
				PVolume *volume;
				FIL file;
			
				bool openFlag=false;
				int openMode;
				int position;
			public:
				
				PFile(PVolume *volume, const char* path);	
			
				virtual int size() override ;
				virtual bool isOpen() override ;
				virtual int pos() override ;
				virtual bool atEnd() override ;
				virtual int mode() override {return openMode;};
			
				virtual bool open(int mode) override ;
				virtual bool close() override ;
				virtual bool seek(int pos) override ;
				virtual bool write(string &data) override ;
				virtual bool write(const char *data) override ;
				bool writeAtTheEnd(string &data);
				bool writeAtTheEnd(const char *data);
				virtual string readLine() override;
			
				bool clear();

		};
#endif
