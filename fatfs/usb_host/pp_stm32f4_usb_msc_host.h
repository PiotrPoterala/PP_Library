#ifndef TM_USB_MSCHOST
#define TM_USB_MSCHOST  100

#ifdef __cplusplus
extern "C" {
#endif
 


#include "usbh_usr.h"


	typedef struct{
		 				  
				void (*init)(void);
				void (*process)(void);
				void (*disconnected)(void);
				USBmscHostState (*state)(void);
		}PusbMscHostDevice;
	 
	void PusbMscHostDeviceConstruct(PusbMscHostDevice* usbMscHostDevice);
			
	void USB_MSCHOST_init();
	void USB_MSCHOST_process(void);
	void USB_MSCHOST_disconnected(void);		
	USBmscHostState USB_MSCHOST_state(void);
		
#ifdef __cplusplus
}
#endif
		
#endif

