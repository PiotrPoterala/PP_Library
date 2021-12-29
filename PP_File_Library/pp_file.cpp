//kod odpowiadający za sprzętową obsługę fileu odczytywanego z karty SD
#include "pp_file.h"
#include <stdio.h>
//#include "input_signals.h"
//#include "configurations_config.h"

//#include "tm_stm32f4_usb_msc_host.h"


//#if defined(FREERTOS)
//	#include "FreeRTOS.h"
//	#include "task.h"
//#endif


PFile::PFile(const char* str){


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


//_Bool saveCharToFileFAT(defOPP_FATFS *oPP_FATFS, FIL *file, char *charakter, _Bool safeWrite){
//		FRESULT fresult;
//		UINT zapisanych_bajtow=0;

//	if(safeWrite){
//		#if defined(FREERTOS)
//			taskENTER_CRITICAL();
//		#else
//			IRQ_DECL_PROTECT(v);
//			IRQ_PROTECT(v, SD_IRQ_LEV_PROTECT);
//		#endif
//	}

//		{
//			oPP_FATFS->pp_f_lseek(file, file->obj.objsize);
//			fresult=oPP_FATFS->pp_f_write(file, charakter, 1, &zapisanych_bajtow);
//		}

//	if(safeWrite){
//		#if defined(FREERTOS)
//				taskEXIT_CRITICAL();
//		#else
//			IRQ_UNPROTECT(v);
//		#endif	
//	}

//		if(fresult==FR_OK) return true;
//		return false;

//}

//_Bool saveStringToFileFAT(defOPP_FATFS *oPP_FATFS, FIL *file, char *string, uint32_t nrOfChar, _Bool safeWrite){
//		FRESULT fresult;
//		UINT zapisanych_bajtow=0;


//	if(safeWrite){
//		#if defined(FREERTOS)
//			taskENTER_CRITICAL();
//		#else
//			IRQ_DECL_PROTECT(v);
//			IRQ_PROTECT(v, SD_IRQ_LEV_PROTECT);
//		#endif
//	}


//	oPP_FATFS->pp_f_lseek(file, file->obj.objsize);
//	fresult=oPP_FATFS->pp_f_write(file, string, nrOfChar, &zapisanych_bajtow);


//	if(safeWrite){
//		#if defined(FREERTOS)
//			taskEXIT_CRITICAL();
//		#else
//			IRQ_UNPROTECT(v);
//		#endif	
//	}

//		if(fresult==FR_OK) return true;
//		return false;

//}

bool PFile::open(int mode){
		bool fresult;
		char path[50];

			fresult=f_mount(&g_sFatFs, volume, 1);
			if(fresult==FR_OK){
				sprintf(path, "%i:%s", volume, fileInfo.fname);
				fresult=f_open(&file, name, mode);
			}
		
			if(fresult==FR_OK) return true;
			return false;

}

bool PFile::close(){
		bool fresult;


			fresult=f_close(&file);
			if(fresult==FR_OK)fresult=f_mount(0, volume, 1);


			if(fresult==FR_OK) return true;
			return false;
}


//_Bool getTextLineFromFAT(defOCheckSignals *oCheckSignals, defOPP_FATFS *oPP_FATFS, uint32_t volume, FIL *file, char *bufor, uint32_t buforSize, uint32_t *cursor){
//		UINT odczytanych_bajtow=0;
//		uint32_t i;


//		if(volume==DEV_USB){
//			if(TM_USB_MSCHOST_Device()!=TM_USB_MSCHOST_Result_Connected) return false;
//		}else if(volume==DEV_SD){
//			if(!(oCheckSignals->checkedResetSignals & mSD_DETECT) && !(oCheckSignals->checkedSetSignals & mSD_DETECT)) return false;
//		}else{
//			return false;
//		}

//		if((*cursor)<file->obj.objsize){
//#if defined(FREERTOS)
//		taskENTER_CRITICAL();
//#else
//		IRQ_DECL_PROTECT(v);
//		IRQ_PROTECT(v, SD_IRQ_LEV_PROTECT);
//#endif
//		{

//			for(i=0; i<buforSize; i++) bufor[i]=0;		//wyczyszczenie bufora
//			oPP_FATFS->pp_f_lseek(file, *cursor);
//			oPP_FATFS->pp_f_read(file, bufor, buforSize, &odczytanych_bajtow);	//pobranie n bajtów (wartość wskazywana przez ) z danego fileu i zapisanie ich do bufora  				
//			for(i=0; bufor[i]!='\n' && (i+1)<buforSize; i++);   //odszukanie w buforze znaku końca linii
//			bufor[++i]='\0'; 	//wstawienie na ostatniej pozycji bufora znaku końca łańcucha
//			(*cursor)+=i;

//		}
//#if defined(FREERTOS)
//		taskEXIT_CRITICAL();
//#else
//	IRQ_UNPROTECT(v);
//#endif
//					return true;
//		}
//		return false;
//}


