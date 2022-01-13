#include "pp_stm32f4_usb_msc_host.h"

extern USB_OTG_CORE_HANDLE     USB_OTG_Core;
extern USBH_HOST               USB_Host;
extern USBmscHostState usbhResult;

_Bool initialized=FALSE;


void PusbMscHostDeviceConstruct(PusbMscHostDevice* usbMscHostDevice){
	usbMscHostDevice->init=USB_MSCHOST_init;
	usbMscHostDevice->process=USB_MSCHOST_process;
	usbMscHostDevice->disconnected=USB_MSCHOST_disconnected;
	usbMscHostDevice->state=USB_MSCHOST_state;
	
}


void USB_MSCHOST_init() {
	/* Set default */
	usbhResult=USB_MSCHOST_Disconnected;
	
	USBH_HardwareInit();
	
	/* Init Host Library */
	USBH_Init(	&USB_OTG_Core,
			#ifdef USE_USB_OTG_FS
				USB_OTG_FS_CORE_ID,
			#else
				USB_OTG_HS_CORE_ID,
			#endif
				&USB_Host,
				&USBH_MSC_cb, 
				&USR_Callbacks);
	
	/* Process */
//	TM_USB_MSCHOST_Process();
	/* Initialized */
	initialized=TRUE;
	/* Is connected already? */
//	return TM_USB_MSCHOST_Device();
}

void USB_MSCHOST_process(void) {
	/* if library is initialized */
	if (initialized) {
		/* Process */
		USBH_Process(&USB_OTG_Core, &USB_Host);
	}
}

void USB_MSCHOST_disconnected(void) {
		USBH_Dev_Disconnected(&USB_OTG_Core, &USB_Host);
		initialized=FALSE;
}

USBmscHostState USB_MSCHOST_state(void){
	
	return usbhResult;
}

