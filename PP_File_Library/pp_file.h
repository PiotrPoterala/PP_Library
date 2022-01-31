#ifndef _PP_FILE_H
	#define _PP_FILE_H

		#include "pp_iodevice.h"
		#include "pp_volume.h"
		
		#include <string>

		#include "ff.h"

		using namespace std;


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
				virtual string read(int maxSize) override ;
				virtual int read(char *data, int maxSize) override ;
				virtual string readLine() override;
				virtual bool exists() override;
			
				string fullPath();
				bool clear();

		};
#endif
