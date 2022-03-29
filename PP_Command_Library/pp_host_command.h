#ifndef _PP_HOST_COMMAND_H
	#define _PP_HOST_COMMAND_H
	
	#include "pp_command.h"
	#include <string>
	#include <map>

class PHostCommand{
		
		private:
			PComandShrPtr command;
			map<int, PComandShrPtr> commandList;
		
		
		public:
			PHostCommand(){};
		
			enum{BASEC, PHYC, TRVV, TRVCO, DIRCD, SPF};
		
			bool executeCommand(string &data){
				if(command!=nullptr) return command->execute(data);
				return false;
			};
			
			void addCommand(int type, PComandShrPtr comm){
				commandList.insert(pair<int, PComandShrPtr>(type, comm));
			};
			
			bool setCommand(int type){
				
				auto it=commandList.find(type);
				if (it != commandList.end()){
					command=(*it).second;
					return true;
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
		
			enum{BASEC, PHYC, DIREL, DIREIL};
		
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
