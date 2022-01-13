#include "usb_conf.h"
#include "usbh_usr.h"
#include "fatfs_usb.h"
#include "pp_stm32f4_usb_msc_host.h"

static volatile DSTATUS USB_Stat = STA_NOINIT;	/* Disk status */

extern USB_OTG_CORE_HANDLE     USB_OTG_Core;
extern USBH_HOST               USB_Host;
extern USBmscHostState usbhResult;

/*-----------------------------------------------------------------------*/
/* Initialize USB                                                        */
/*-----------------------------------------------------------------------*/
DSTATUS TM_FATFS_USB_disk_initialize(void) {
	if (HCD_IsDeviceConnected(&USB_OTG_Core) && usbhResult == USB_MSCHOST_Connected) {
		USB_Stat &= ~STA_NOINIT;
	} else {
		USB_Stat |= STA_NOINIT;
	}

	return USB_Stat;
}

/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/
DSTATUS TM_FATFS_USB_disk_status(void) {
	return USB_Stat;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT TM_FATFS_USB_disk_read (
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	UINT count		/* Number of sectors to read (1..128) */
)
{
	BYTE status = USBH_MSC_OK;

	if (!count) {
		return RES_PARERR;
	}
	if (USB_Stat & STA_NOINIT) {
		return RES_NOTRDY;
	}

	if (HCD_IsDeviceConnected(&USB_OTG_Core) && usbhResult == USB_MSCHOST_Connected) {
		do
		{
			status = USBH_MSC_Read10(&USB_OTG_Core, buff, sector, 512 * count);
			USBH_MSC_HandleBOTXfer(&USB_OTG_Core, &USB_Host);

			if (!HCD_IsDeviceConnected(&USB_OTG_Core)) { 
				return RES_ERROR;
			}
		} while (status == USBH_MSC_BUSY);
	}

	if (status == USBH_MSC_OK) {
		return RES_OK;
	}
	return RES_ERROR;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
#if _READONLY == 0
DRESULT TM_FATFS_USB_disk_write (
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	UINT count			/* Number of sectors to write (1..128) */
)
{
	BYTE status = USBH_MSC_OK;
	if (!count) {
		return RES_PARERR;
	}
	if (USB_Stat & STA_NOINIT) {
		return RES_NOTRDY;
	}
	if (usbhResult == USB_MSCHOST_WriteProtected) {
		return RES_WRPRT;
	}

	if (HCD_IsDeviceConnected(&USB_OTG_Core) && usbhResult == USB_MSCHOST_Connected) {
		do
		{
			status = USBH_MSC_Write10(&USB_OTG_Core, (BYTE*)buff, sector, 512 * count);
			USBH_MSC_HandleBOTXfer(&USB_OTG_Core, &USB_Host);

			if (!HCD_IsDeviceConnected(&USB_OTG_Core)) {
				return RES_ERROR;
			}
		} while (status == USBH_MSC_BUSY);
	}

	if (status == USBH_MSC_OK) {
		return RES_OK;
	}
	return RES_ERROR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT TM_FATFS_USB_disk_ioctl (
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_OK;

	if (USB_Stat & STA_NOINIT) {
		return RES_NOTRDY;
	}

	switch (cmd) {
		case CTRL_SYNC :		/* Make sure that no pending write process */
			res = RES_OK;
			break;

		case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
			*(DWORD*)buff = (DWORD) USBH_MSC_Param.MSCapacity;
			res = RES_OK;
			break;

		case GET_SECTOR_SIZE :	/* Get R/W sector size (WORD) */
			*(WORD*)buff = 512;
			res = RES_OK;
			break;

		case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
			*(DWORD*)buff = 512;
			break;

		default:
			res = RES_PARERR;
	}

	return res;
}

