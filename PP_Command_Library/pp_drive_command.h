#ifndef _PP_DRIVE_COMMAND_H
	#define _PP_DRIVE_COMMAND_H
	
	#include "pp_command.h"
	#include "pp_paramlist.h"
	#include "pp_rtos_queue.h"
	#include "at_tags.h"
	
	#include <map>

class PDriveForValueCommand : public PCommand{
		
		private:
			defOParamList *param;
			defOTaskQueues<int>* taskCommunicationQueues;/**<pointer to queue used to comunication between two threads*/
	
		public:
			PDriveForValueCommand(defOParamList *par, defOTaskQueues<int>* commQueues):param(par),taskCommunicationQueues(commQueues){};
	
			virtual void execute(map<char, double> &values) override{
					vector<int> valuesToSend;
				
					valuesToSend.push_back(qMARK_ATC);
					valuesToSend.push_back(AT_TAG_TRVV);
					valuesToSend.push_back(values.size());
					
					for(auto it=values.begin(); it!=values.end(); ++it){
						valuesToSend.push_back((*it).first);
						valuesToSend.push_back((*it).second*pow(10.0, param->getParamUnit((*it).first)));
					}
					
					
					taskCommunicationQueues->xQueueSendConteinerToBackWithSemaphore(valuesToSend);
				
			};

	};


class PDriveToBaseCoordCommand : public PCommand{
		
		private:
			defOParamList *param;
			defOTaskQueues<int>* taskCommunicationQueues;/**<pointer to queue used to comunication between two threads*/
	
		public:
			PDriveToBaseCoordCommand(defOParamList *par, defOTaskQueues<int>* commQueues):param(par),taskCommunicationQueues(commQueues){};
	
			virtual void execute(map<char, double> &values) override{
					vector<int> valuesToSend;
				
					valuesToSend.push_back(qMARK_ATC);
					valuesToSend.push_back(AT_TAG_TRVCO);
					valuesToSend.push_back(values.size());
					
					for(auto it=values.begin(); it!=values.end(); ++it){
						valuesToSend.push_back((*it).first);
						valuesToSend.push_back((*it).second*pow(10.0, param->getParamUnit((*it).first)));
					}
					
					
					taskCommunicationQueues->xQueueSendConteinerToBackWithSemaphore(valuesToSend);
				
			};

	};
	
#endif