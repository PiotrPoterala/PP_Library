#ifndef _PP_HOST_COMMAND_H
	#define _PP_HOST_COMMAND_H
	
	#include "pp_command.h"
	#include <string>
	#include <map>

class PHostCommand{
		
		private:
			PCommand* command;
			map<int, PCommand*> commandList;
		
		
		public:
			PHostCommand(){};
		
			enum{BASEC, PHYC, TRVV, TRVCO};
		
			void executeCommand(map<char, double> &values){
				if(command!=nullptr)command->execute(values);
			};
			
			void addCommand(int type, PCommand* comm){
				commandList.insert(pair<int, PCommand*>(type, comm));
			};
			
			bool setCommand(int type){
				
				auto it=commandList.find(type);
				if (it != commandList.end()){
					command=(*it).second;
					return true;
				}else{
					command=nullptr;
				}
				return false;
				
			}
					
	};

	
	class PHostAskCommand{
		
		private:
			PAskCommand* command;
			map<int, PAskCommand*> commandList;
		
		
		public:
			PHostAskCommand(){};
		
			enum{BASEC,PHYC};
		
			string executeCommand(){
				string ans;
				if(command!=nullptr)ans=command->execute();
				return ans;
			};
			
			void addCommand(int type, PAskCommand* comm){
				commandList.insert(pair<int, PAskCommand*>(type, comm));
			};
			
			bool setCommand(int type){
				
				auto it=commandList.find(type);
				if (it != commandList.end()){
					command=(*it).second;
					return true;
				}else{
					command=nullptr;
				}
				return false;
				
			}
					
	};
	

#endif
