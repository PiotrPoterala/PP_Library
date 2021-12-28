/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "fatfs_sd.h"
#include "fatfs_usb.h"

#define DEV_SD			0	/* Example: Map MMC/SD card to physical drive 0 */
#define DEV_USB			1	/* Example: Map USB MSD to physical drive 1 */

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
		case DEV_SD :
			stat = FATFS_SD_disk_status();


			return stat;

		case DEV_USB :

			stat = TM_FATFS_USB_disk_status();

			return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
		case DEV_SD :
			stat = FATFS_SD_disk_initialize();

			return stat;

		case DEV_USB :

			stat = TM_FATFS_USB_disk_initialize();

			return stat;
		}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;

	switch (pdrv) {
		case DEV_SD :
			// translate the arguments here

			res = FATFS_SD_disk_read(buff, sector, count);

			// translate the reslut code here

			return res;

		case DEV_USB :

			res = TM_FATFS_USB_disk_read(buff, sector, count);

			return res;
		}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;

	switch (pdrv) {
		case DEV_SD :

			res = FATFS_SD_disk_write(buff, sector, count);

			return res;

		case DEV_USB :

			res = TM_FATFS_USB_disk_write(buff, sector, count);

			return res;
		}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

	switch (pdrv) {
	case DEV_SD :

		res=FATFS_SD_disk_ioctl(cmd, buff);

		return res;

	case DEV_USB :

		res=TM_FATFS_USB_disk_ioctl(cmd, buff);

		return res;
	}

	return RES_PARERR;
}

