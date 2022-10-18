#ifndef _PP_DRIVE_COMMAND_H
	#define _PP_DRIVE_COMMAND_H
	
	#include "pp_command.h"
	#include "pp_paramlist.h"
	#include "pp_rtos_queue.h"
	#include "at_tags.h"
	
	#include <map>

class PDriveForValueCommand : public PCommand{
		
		private:
			PMotorsListShdPtr motorsList;
			defOTaskQueuesIntShrPtr taskCommunicationQueues;/**<pointer to queue used to comunication between two threads*/
	
		public:
			PDriveForValueCommand(PMotorsListShdPtr motors, defOTaskQueuesIntShrPtr commQueues):motorsList(motors),taskCommunicationQueues(commQueues){};
	
			virtual bool execute(string &data) override{
				PString str(data);
				auto auxCoord=motorsList->getBaseCoordClone();			
				defOParamList::setParamsBasedString(auxCoord, str);
				
				if(!auxCoord.empty()){
					vector<int> valuesToSend;
				
					valuesToSend.push_back(qMARK_ATC);
					valuesToSend.push_back(AT_TAG_TRVV);
					valuesToSend.push_back(auxCoord.size());
					
					for(auto it:auxCoord){
						valuesToSend.push_back(it.first);
						valuesToSend.push_back(it.second->getValue());
					}
					
					
					taskCommunicationQueues->xQueueSendConteinerToBackWithSemaphore(valuesToSend);
					return true;
				}
				return false;
			};

	};

	
	
	class PDriveToBaseCoordCommand : public PCommand{
		
		private:
			PMotorsListShdPtr motorsList;
			defOTaskQueuesIntShrPtr taskCommunicationQueues;/**<pointer to queue used to comunication between two threads*/
	
		public:
			PDriveToBaseCoordCommand(PMotorsListShdPtr motors, defOTaskQueuesIntShrPtr commQueues):motorsList(motors),taskCommunicationQueues(commQueues){};
	
			virtual bool execute(string &data) override{
				PString str(data);
				auto auxCoord=motorsList->getBaseCoordClone();			
				defOParamList::setParamsBasedString(auxCoord, str);
				
				if(!auxCoord.empty()){
					vector<int> valuesToSend;
				
					valuesToSend.push_back(qMARK_ATC);
					valuesToSend.push_back(AT_TAG_TRVCO);
					valuesToSend.push_back(auxCoord.size());
					
					for(auto it:auxCoord){
						valuesToSend.push_back(it.first);
						valuesToSend.push_back(it.second->getValue());
					}
					
					
					taskCommunicationQueues->xQueueSendConteinerToBackWithSemaphore(valuesToSend);
					return true;
				}
				return false;
			};

	};

//class PDriveToBaseCoordCommand : public PCommand{
//		
//		private:
//			defOParamListShdPtr param;
//			defOTaskQueuesIntShrPtr taskCommunicationQueues;/**<pointer to queue used to comunication between two threads*/
//	
//		public:
//			PDriveToBaseCoordCommand(defOParamListShdPtr par, defOTaskQueuesIntShrPtr commQueues):param(par),taskCommunicationQueues(commQueues){};
//	
//			virtual bool execute(string &data) override{
//				PString str(data);
//				map<char, double> values;
//				values=str.findValuesAfterAcronims();
//				
//				if(!values.empty()){
//					vector<int> valuesToSend;
//				
//					valuesToSend.push_back(qMARK_ATC);
//					valuesToSend.push_back(AT_TAG_TRVCO);
//					valuesToSend.push_back(values.size());
//					
//					for(auto it=values.begin(); it!=values.end(); ++it){
//						valuesToSend.push_back((*it).first);
//						valuesToSend.push_back((*it).second*pow(10.0, param->getParamUnit((*it).first)));
//					}
//					
//					return true;
//					taskCommunicationQueues->xQueueSendConteinerToBackWithSemaphore(valuesToSend);
//				}
//				return false;
//			};

//	};
	
#endif