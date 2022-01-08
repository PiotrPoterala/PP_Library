#ifndef _PP_FILE_H
	#define _PP_FILE_H

		#include "stm32xx.h"
		#include "pp_iodevice.h"
		
		#include <string>

		#include "ff.h"

		using namespace std;

		class PVolume{
			
			public:
				PVolume(char vol):volume(vol){};
				char volume;
				FATFS g_sFatFs;
			
		};

		class PFile : public PIOdevice{
			private:
				string path;
				PVolume *volume;
				FIL file;
			
				bool openFlag=false;
				OpenMode openMode;
				int position;
			public:
				
				PFile(PVolume *volume, const char* path);	
			
				virtual int size() override ;
				virtual bool isOpen() override ;
				virtual int pos() override ;
				virtual bool atEnd() override ;
				virtual OpenMode mode() override {return openMode;};
			
				virtual bool open(OpenMode mode) override ;
				virtual bool close() override ;
				virtual bool seek(int pos) override ;
				virtual bool write(string &data) override ;
				virtual bool write(const char *data) override ;
				bool writeAtTheEnd(string &data);
				bool writeAtTheEnd(const char *data);
				virtual string readLine() override;
			
				string fullPath();
				bool exists();
				bool clear();

		};
#endif
