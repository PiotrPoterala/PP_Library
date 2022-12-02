#ifndef _PP_GBASE_POINTS_COMMAND_H
	#define _PP_GBASE_POINTS_COMMAND_H
	
	#include "pp_command.h"
	#include "pp_point.h"
	
	#include <string>
	#include <map>

class PSetGBasePointsCommand : public PCommand{
		
		private:
			PPpointIntListShdPtr gBasePoints;
	
		public:
			PSetGBasePointsCommand()=delete;
			PSetGBasePointsCommand(PPpointIntListShdPtr pointsList):gBasePoints(pointsList){};
	
			virtual bool execute(string &data) override{
					PString str(data);
					int index=str.findValueAfterAcronim('N', -1);
					if(index>=0 && index<gBasePoints->size()){
						gBasePoints->at(index).setAxesBasedString(str);
						return true;
					}
					return false;
			};

	};

	class PSaveGBasePointsCommand : public PCommand{
		
		private:
			PPpointIntListShdPtr gBasePoints;
	
		public:
			PSetGBasePointsCommand()=delete;
			PSetGBasePointsCommand(PPpointIntListShdPtr pointsList):gBasePoints(pointsList){};
	
			virtual bool execute(string &data) override{
					PString str(data);
					int index=str.findValueAfterAcronim('N', -1);
					if(index>=0 && index<gBasePoints->size()){
						gBasePoints->at(index).setAxesBasedString(str);
						return true;
					}
					return false;
			};

	};


class PGetGBasePointsCommand : public PAskCommand{
		
		private:
			PPpointIntListShdPtr gBasePoints;
	
		public:
			PGetGBasePointsCommand()=delete;
			PGetGBasePointsCommand(PPpointIntListShdPtr pointsList):gBasePoints(pointsList){};
	
			virtual string execute() override{
					string answer;	
					
					for(auto point_it:*gBasePoints){
	//				for(auto point_it=gBasePoints->begin(); point_it!=gBasePoints->end(); point_it++){
						for(auto ax_it: point_it.rGetAxes()){
							auto limit=point_it.getLimit(ax_it.first);
							if(!limit.empty()){
								answer+=PString::doubleToString(point_it.getRealAxValue(ax_it.first), std::get<3>(limit.front()));
							}else{
								answer+=PString::doubleToString(point_it.getRealAxValue(ax_it.first), 0);
							}
							answer+=" ";
						}
					}
				
					return answer;
				
			};

	};
	
#endif