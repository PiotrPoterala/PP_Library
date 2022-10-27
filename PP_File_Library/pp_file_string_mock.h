#ifndef _PP_FILE_STRING_MOCK_H
	#define _PP_FILE_STRING_MOCK_H

		#include "pp_file.h"
		#include <string> 

		using namespace std;


		class PFileStringMock : public PFile{
			private:
				string file;

			public:
				PFileStringMock(const string &path):PFile(path){};
				PFileStringMock(const char* path):PFile(path){};	
			
				virtual int size() override ;
				virtual bool atEnd() override ;
			
				virtual bool open(OpenMode mode) override ;
				virtual bool close() override ;
				virtual bool seek(int pos) override ;
				virtual bool write(string &data) override ;
				virtual bool write(const char *data) override ;
				virtual bool writeAtTheEnd(string &data)override ;
				virtual bool writeAtTheEnd(const char *data)override ;
				virtual string read(int maxSize) override ;
				virtual int read(char *data, int maxSize) override ;
				virtual string readLine() override;
			

				bool clear();

		};
#endif
