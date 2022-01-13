#include "usbh_usr.h"


USB_OTG_CORE_HANDLE     USB_OTG_Core;
USBH_HOST               USB_Host;
USBmscHostState usbhResult;

USBH_Usr_cb_TypeDef USR_Callbacks = {
	USBH_USR_Init,
	USBH_USR_DeInit,
	USBH_USR_DeviceAttached,
	USBH_USR_ResetDevice,
	USBH_USR_DeviceDisconnected,
	USBH_USR_OverCurrentDetected,
	USBH_USR_DeviceSpeedDetected,
	USBH_USR_Device_DescAvailable,
	USBH_USR_DeviceAddressAssigned,
	USBH_USR_Configuration_DescAvailable,
	USBH_USR_Manufacturer_String,
	USBH_USR_Product_String,
	USBH_USR_SerialNum_String,
	USBH_USR_EnumerationDone,
	USBH_USR_UserInput,
	USBH_USR_MSC_Application,
	USBH_USR_DeviceNotSupported,
	USBH_USR_UnrecoveredError
};

uint8_t Application = USH_USR_FS_INIT;

void USBH_USR_Init(void) {
	/* USB Library has been initialized, device is not connected yet */
	usbhResult = USB_MSCHOST_Disconnected;
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
}

void USBH_USR_DeviceAttached(void) {
	/* Device has been initialized, device is not connected yet */
	usbhResult = USB_MSCHOST_Disconnected;
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
}

void USBH_USR_UnrecoveredError (void) {
	/*  */
	usbhResult = USB_MSCHOST_Disconnected;	
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
}

void USBH_USR_DeviceDisconnected (void) {
	/* Device disconnected */
	usbhResult = USB_MSCHOST_Disconnected;
	
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
}

void USBH_USR_ResetDevice(void) {
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
}

void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed) {
	/*if ((DeviceSpeed != HPRT0_PRTSPD_FULL_SPEED) && (DeviceSpeed != HPRT0_PRTSPD_LOW_SPEED)) {
		TM_USB_MSCHOST_INT_Result = TM_USB_MSCHOST_Result_Disconnected;
	}*/
}

void USBH_USR_Device_DescAvailable(void *DeviceDesc) {
	
}

void USBH_USR_DeviceAddressAssigned(void) {
	
}

void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
    USBH_InterfaceDesc_TypeDef *itfDesc,
    USBH_EpDesc_TypeDef *epDesc) {

}

void USBH_USR_Manufacturer_String(void *ManufacturerString) {
	
}

void USBH_USR_Product_String(void *ProductString) {
	
}

void USBH_USR_SerialNum_String(void *SerialNumString) {
	
}

void USBH_USR_EnumerationDone(void) {

} 

void USBH_USR_DeviceNotSupported(void) {
	/* Device is not supported */
	usbhResult = USB_MSCHOST_DeviceNotSupported;
}

USBH_USR_Status USBH_USR_UserInput(void) {
	return USBH_USR_RESP_OK;
}

void USBH_USR_OverCurrentDetected (void) {
	/* Error */
	usbhResult = USB_MSCHOST_Error;
}

int USBH_USR_MSC_Application(void) {
	/* Device is connected */
	if (Application == USH_USR_FS_INIT) {
		Application = USH_USR_FS_LOOP;
		
		/* Device is connected */
		usbhResult = USB_MSCHOST_Connected;
		if (USBH_MSC_Param.MSWriteProtect == DISK_WRITE_PROTECTED) {
			/* Device is write protected */
			usbhResult = USB_MSCHOST_WriteProtected;
		}
	}
	
	return 0;
}

void USBH_USR_DeInit(void) {
	/* Device disconnected */
	//TM_USB_MSCHOST_INT_Result = TM_USB_MSCHOST_Result_Disconnected;
	/* We have to initialize first */
	Application = USH_USR_FS_INIT;
}


