#ifndef _PP_VOLUME_H
	#define _PP_VOLUME_H

		#include <string>

		#include "ff.h"

		using namespace std;

		class PVolume{
			
			public:
				PVolume(const char* vol):volume(vol){};
				PVolume(int vol){
					volume=to_string(vol);
					volume+=":";
				};
				string volume;
				FATFS g_sFatFs;
			
		};
		
#endif 