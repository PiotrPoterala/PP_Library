#ifndef _PP_FILE_FATFS_H
	#define _PP_FILE_FATFS_H

		#include "pp_file.h"
		#include "ff.h"

		using namespace std;


		class PFileFATFS : public PFile{
			private:
				FIL file;
				FATFS g_sFatFs;
			
			public:
				PFileFATFS(const string &path):PFile(path){};
					PFileFATFS(const char* path):PFile(path){};	
			
				virtual int size() override ;
				virtual bool atEnd() override ;
			
				virtual bool open(OpenMode mode) override ;
				virtual bool close() override ;
				virtual bool seek(int pos) override ;
				virtual bool write(string &data) override ;
				virtual bool write(const char *data) override ;
				virtual bool write(int data) override;
				virtual bool writeAtTheEnd(string &data)override ;
				virtual bool writeAtTheEnd(const char *data)override ;
				virtual bool writeAtTheEnd(int data)override ;
				virtual string read(int maxSize) override ;
				virtual int read(char *data, int maxSize) override ;
				virtual string readLine() override;
				virtual bool exists() override;
			

				bool clear();

		};
#endif
