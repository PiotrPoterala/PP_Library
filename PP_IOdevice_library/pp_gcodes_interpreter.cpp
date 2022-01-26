/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Piotr Poterała, 2021
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */

#include "pp_gcodes_interpreter.h"
#include "pstring.h"
#include "at_tags.h"

PGcodeInterpreter::PGcodeInterpreter(PIOdevice* IOdevice, defORTX5TaskQueues<int>* commQueues, defOParamList *pCoord, defOParamList *bCoord, bool answer):
																PIOdeviceDecorator(IOdevice), taskCommunicationQueues(commQueues), phyCoord(pCoord), baseCoord(bCoord), response(answer){

};


string PGcodeInterpreter::readLine(){
		
	
	string receiveString=PIOdeviceDecorator::readLine();
	
	if(receiveString.empty()==false){
		
//				if(receiveString.at(0)=='%'){
//						outFile<<(START_PROG<<10)<<" \r\n";			//zapisanie do pamięci flash znaku określającego koniec programu
//				}else{
//					interpretGcodeWEDM(line, outFile, gBaseList);
//					interpretMcodeWEDM(line, outFile);
//				}
	}
    
		return receiveString;
}