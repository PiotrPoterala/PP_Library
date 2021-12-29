#ifndef _PP_FILE_H
	#define _PP_FILE_H

		#include "stm32xx.h"

		#include "ff.h"

using namespace std;

		class PFile{
			private:
				const TCHAR* volume;
				FATFS g_sFatFs;
				FIL file;
				FILINFO fileInfo;

			public:
				
			
			
				PFile(const char* str);	
			
				bool open(int mode);
				bool close();
				bool seek();
				bool write();

		};
#endif
