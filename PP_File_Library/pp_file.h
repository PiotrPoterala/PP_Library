#ifndef _PP_FILE_H
	#define _PP_FILE_H

		#include "pp_iodevice.h"
		
		#include <string>

		#include "ff.h"

		using namespace std;


		class PFile : public PIOdevice{
			protected:
			
				string volume;
				string path;
			
				bool openFlag=false;
				OpenMode openMode;
				int position;
			public:
				PFile(const string &path);
				PFile(const char* path);	
			
				virtual bool isOpen() override ;
				virtual int pos() override ;
				string absolutePath();
				virtual OpenMode mode() override {return openMode;};
				
				virtual bool open(OpenMode mode)override {return false;};
				virtual bool close()override {return false;};
				
				virtual bool writeAtTheEnd(string &data)=0;
				virtual bool writeAtTheEnd(const char *data)=0;

		};
#endif
