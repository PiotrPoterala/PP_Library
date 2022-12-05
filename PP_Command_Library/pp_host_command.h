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
		
			enum{BASEC, PHYC, TRVV, TRVCO, DIRCD, SPF, SPT, GBASE, SaveGBASE};
		
			bool executeCommand(string &data){
				if(command) return command->execute(data);
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
				}else{
					command.reset();
				}
				
				return false;
				
			}
					
	};

	
	class PHostAskCommand{
		
		private:
			PAskComandShrPtr command;
			map<int, PAskComandShrPtr> commandList;
		
		
		public:
			PHostAskCommand(){};
		
			enum{BASEC, PHYC, DIREL, DIREIL, SPT, GBASE};
		
			string executeCommand(){
				string ans;
				if(command)ans=command->execute();
				return ans;
			};
			
			void addCommand(int type, PAskComandShrPtr comm){
				commandList.insert(pair<int, PAskComandShrPtr>(type, comm));
			};
			
			bool setCommand(int type){
				
				auto it=commandList.find(type);
				if (it != commandList.end()){
					command=(*it).second;
					return true;
				}else{
					command.reset();
				}
				return false;
				
			}
					
	};
	
	using PHostCommandShrPtr= shared_ptr<PHostCommand>;
	using PHostAskCommandShrPtr= shared_ptr<PHostAskCommand>;
#endif
