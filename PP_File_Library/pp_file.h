#ifndef _PP_FILE_H
	#define _PP_FILE_H

		#include "stm32xx.h"
		
		#include <string>

		#include "ff.h"

using namespace std;

		class PFile{
			private:
				char volume;
				string name;
				FATFS g_sFatFs;
				FIL file;

				bool openFlag;
				int position;
			
			public:
				
				PFile(char vol, const char* path);	
			
				int size();
				bool isOpen();
				int pos();
				bool atEnd();
			
				bool open(int mode);
				bool close();
				bool seek(int pos);
				bool write(string *data);
				bool write(const char *data);
				bool writeAtTheEnd(string *data);
				string readLine();

		};
#endif
