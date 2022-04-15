#ifndef _PP_RTOS_DRIVE_ALGORITHMS_MOCK_H
	#define _PP_RTOS_DRIVE_ALGORITHMS_MOCK_H

#include "pp_drive_algorithms.h"

	
	class defORTOSdriveAlgorithmsMock : public defODriveAlgorithms{

		public:
	//		defORTOSdriveAlgorithmsMock(){};
			defORTOSdriveAlgorithmsMock(defOMotorsListShdPtr motors, defOParamListShdPtr pCoord, defOParamListShdPtr bCoord):defODriveAlgorithms(motors, pCoord, bCoord){};
		
		
				virtual DriveStatus drive(void){return DriveStatus::DRIVE_COMPLETED;};
		
		

	};



#endif