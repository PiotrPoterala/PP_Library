
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

#ifndef _G_CODE_INTERPRETER_H
	#define _G_CODE_INTERPRETER_H
	
	#include "pp_iodevice_decorator.h"
	#include "pp_rtx5_queue.h"
	#include "pp_paramlist.h"
	
	#include <string>
	
	
	#define qMARK_TAG	(1<<28)
	#define qMARK_KEY	(2<<28)
	#define qMARK_ATC	(3<<28)
	
	using namespace std;

class PGcodeInterpreter: public PIOdeviceDecorator{
		
	private:
		defORTX5TaskQueues<int>* taskCommunicationQueues;/**<pointer to queue used to comunication between two threads*/
		defOParamList *phyCoord; /**<pointer to list with physical coordinates*/
		defOParamList *baseCoord;/**<pointer to list with base coordinates*/
		
		bool response;
	public:
		
		/**
		A constructor.
		@param [in] uQueues a pointer to decorated object.
		@param [in] commQueues a pointer to queue used to comunication between two threads.
		@param [in] pCoord a pointer to list with physical coordinates.
		@param [in] bCoord a pointer to list with base coordinates.
		*/
		PGcodeInterpreter(PIOdevice* IOdevice, defORTX5TaskQueues<int>* commQueues, defOParamList *pCoord, defOParamList *bCoord, bool answer=true);


		virtual string readLine() override;

	};


#endif
