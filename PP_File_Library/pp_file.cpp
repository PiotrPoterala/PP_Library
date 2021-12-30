//kod odpowiadający za sprzętową obsługę fileu odczytywanego z karty SD
#include "pp_file.h"
//#include "input_signals.h"
//#include "configurations_config.h"

//#include "tm_stm32f4_usb_msc_host.h"


//#if defined(FREERTOS)
//	#include "FreeRTOS.h"
//	#include "task.h"
//#endif


PFile::PFile(char vol, const char* str){

		volume=vol;
		name=str;

}	

//void OFileFATConstruct(defOFileFAT *oFileFAT, FILINFO fInfo, char *dName){

//		clearFilinfo(&oFileFAT->fileInfo);

//		oFileFAT->fileInfo.fsize=fInfo.fsize;			
//		oFileFAT->fileInfo.fdate=fInfo.fdate;			
//		oFileFAT->fileInfo.ftime=fInfo.ftime;			
//		oFileFAT->fileInfo.fattrib=fInfo.fattrib;		

//		strcpy(oFileFAT->fileInfo.fname, fInfo.fname);	

//		if(*dName!='\0')
//			strcpy(oFileFAT->dirName, dName);
//		else 
//			*oFileFAT->dirName='\0';

//		oFileFAT->cursor=0;	
//		oFileFAT->auxCursor=0;	

//		oFileFAT->saveCharToFileFAT=saveCharToFileFAT;
//		oFileFAT->saveStringToFileFAT=saveStringToFileFAT;
//		oFileFAT->openFileFAT=openFileFAT;
//		oFileFAT->closeFileFAT=closeFileFAT;
//		oFileFAT->getTextLineFromFAT=getTextLineFromFAT;

//		oFileFAT->clearFilinfo=clearFilinfo;
//}

//void clearFilinfo(FILINFO *fInfo){

//	fInfo->fsize=0;			/* File size */
//	fInfo->fdate=0;			/* Modified date */
//	fInfo->ftime=0;			/* Modified time */
//	fInfo->fattrib=0;		/* File attribute */

//	for(uint32_t i=0;i<13;i++)fInfo->fname[i]=0;
//	
//}




bool PFile::isOpen(){
	
	return openFlag;
	
}

int PFile::size(){
	
	return file.obj.objsize;
	
}

int PFile::pos(){
	
	return position;
}

bool PFile::atEnd(){
	
	if(position==file.obj.objsize)return true;
	
	return false;
	
}

bool PFile::open(int mode){
		int fresult;
		string path;

			fresult=f_mount(&g_sFatFs, &volume, 1);
			if(fresult==FR_OK){
				path+=volume;
				path+=":";
				path+=name;
				fresult=f_open(&file, path.c_str(), mode);
			}
		
			if(fresult==FR_OK){
				openFlag=true;
				position=0;
				return true;
			}
			return false;

}

bool PFile::close(){
		int fresult;


			fresult=f_close(&file);
			if(fresult==FR_OK)fresult=f_mount(0, &volume, 1);


			if(fresult==FR_OK){
				openFlag=false;
				return true;
			}
			return false;
}

bool PFile::seek(int pos){
	int fresult;
	fresult=f_lseek(&file, pos);
	
	if(fresult==FR_OK) return true;
	return false;
	
}

bool PFile::write(string *data){
		int fresult;
		unsigned int saveBytes=0;

		fresult=f_write(&file, data->c_str(), data->size(), &saveBytes);

		if(fresult==FR_OK) return true;
		return false;

}

bool PFile::write(const char *data){
		int fresult;
		unsigned int saveBytes=0;

		fresult=f_write(&file, data, strlen(data), &saveBytes);

		if(fresult==FR_OK) return true;
		return false;

}

bool PFile::writeAtTheEnd(string *data){
		bool result=false;
	
		if(seek(file.obj.objsize)){
			result=write(data);
		}

		return result;

}



string PFile::readLine(){
		#define BUFOR_SIZE 64
	
		int fresult, i;
		unsigned int readBytes=BUFOR_SIZE;
		char bufor[BUFOR_SIZE];
		string result;
		bool isEndSign=false;


		if(position<file.obj.objsize){

			while(isEndSign==false && readBytes==BUFOR_SIZE){
				f_lseek(&file, position);
				f_read(&file, bufor, BUFOR_SIZE, &readBytes);	//pobranie n bajtów (wartość wskazywana przez ) z danego fileu i zapisanie ich do bufora  		

				
				for(i=0; bufor[i]!='\0' && i<BUFOR_SIZE; i++){
					if(isEndSign)bufor[i]='\0'; 
					if(bufor[i]=='\n'){
						isEndSign=true;
						position+=i;
					}
				}

				result+=bufor;		
			}
		}

		
		return result;
}


