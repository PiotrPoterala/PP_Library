#ifndef _FATFS_SD_H
	#define _FATFS_SD_H

#include "diskio.h"
#include "integer.h"

#if defined(STM32F030)
  #include "stm32f0xx.h"
#elif defined(STM32F10X_HD)
	#include "stm32f10x.h"
#elif defined(STM32F446xx) || defined(STM32F427_437xx)
	#include "stm32f4xx.h"
#endif


/*---------------------------------------*/
/* Prototypes for disk control functions */

DSTATUS FATFS_SD_disk_initialize (void);
DSTATUS FATFS_SD_disk_status (void);
DRESULT FATFS_SD_disk_read (BYTE* buff, DWORD sector, UINT count);
DRESULT FATFS_SD_disk_write (const BYTE* buff, DWORD sector, UINT count);
DRESULT FATFS_SD_disk_ioctl (BYTE cmd, void* buff);

#endif

