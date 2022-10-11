/**
 * @author  Piotr Poterała
 * @email   poterala.piotr@gmail.com
 * @website http://zappp.pl
 * @version v1.0
 * @ide     Keil uVision 5
 * @license GNU GPL v3
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Piotr Poterała, 2021
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */

#ifndef _PP_DRIVE_ALGORITHMS_H
	#define _PP_DRIVE_ALGORITHMS_H

#include <map>
#include "pp_paramlist.h"
#include "pp_motorslist.h"
#include "pp_point.h"


enum class DriveStatus{DRIVE_IN_PROGRESS=-1, DRIVE_COMPLETED=0, DRIVE_ABORTED, DRIVE_PAUSED, DRIVE_INTERRUPTED};
	
	class defODriveAlgorithms{
		
		private:
			void driveToEndPoint(PPpoint<int> &endP, PPpoint<int> &startP);
		
		protected:
			PMotorsListShdPtr motorsList;
			PPpoint<int> phyStartPoint;
			PPpoint<int> phyEndPoint;
			PPpoint<int> phyIndEndPoint;
		
			map<char, int> counter;

		
		public:
			DriveStatus status;
		
			defODriveAlgorithms(PMotorsListShdPtr mot);
		
			void driveForValue(map<char, int> &values);
			void driveForValue(PPpoint<int> &values);
			void driveToBaseCoordinates(map<char, int> &values);
			void driveToBaseCoordinates(PPpoint<int> &values);
			void driveToPhyCoordinates(PPpoint<int> &values);
		
			virtual DriveStatus drive(void)=0;
		
		
			static unsigned int getFrequencykResponsibleForDriveSpeed(unsigned int nrOfStepsFromStart, unsigned int nrOfStepsToEnd, unsigned int accelerationXperSEC2, unsigned int velocityXperSEC, unsigned int stepMX);
			static unsigned int getClockDividerResponsibleForDriveSpeed(unsigned int nrOfStepsFromStart, unsigned int nrOfStepsToEnd, unsigned int accelerationXperSEC2, unsigned int velocityXperSEC, unsigned int frequencyOfClock, unsigned int stepMX);
			static unsigned int getFrequencyOfDriveInUniformMovement(unsigned int velocityXperSEC, unsigned int stepMX);
			static unsigned int getClockDividerInUniformMovement(unsigned int velocityXperSEC, unsigned int frequencyOfClock, unsigned int stepMX);
			static unsigned int calculateAccelerateNumberOfSteps(unsigned int accelerationXperSEC2, unsigned int velocityXperSEC, unsigned int stepMX);
		
		

	};

using defODriveAlgorithmsShdPtr = shared_ptr<defODriveAlgorithms>;

#endif
