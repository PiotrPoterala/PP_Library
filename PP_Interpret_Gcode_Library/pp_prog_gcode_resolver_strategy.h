#ifndef _PP_PROG_GCODE_RESOLVER_STRATEGY_H
	#define _PP_PROG_GCODE_RESOLVER_STRATEGY_H
	
	#include <vector>
	
	#include "pp_program_resolver_strategy.h"
	#include "pstring.h"
	#include "pp_point.h"
	#include "pp_paramlist.h"

	
class PProgGcodeResolverStrategy : public PProgramResolverStrategy{
	
	protected:
			defOParamListShdPtr phyCoord;
			defOParamListShdPtr baseCoord;
			defOParamListShdPtr workParams;
			PPpointListShdPtr basePointsList;
	
			bool writeInAboluteValues=false;
			bool G00occured=false;
			int GcodeStandardCycle=0;
			int G81nrOfRepetitions=0;
	
			PPpoint<int> basePoint;
			PStringList repetitionsList;
	
			void interpretMcode(PString &program);
	
			void writeG00Line(PPpoint<int> &point);

			virtual void resetInterpretSettings();
			virtual void interpretGcode(PString &program)=0;
			virtual void writePointParam(PPpoint<int> &point)=0;
		public:
			PProgGcodeResolverStrategy()=delete;
			PProgGcodeResolverStrategy(PIOdeviceShrPtr destination, PFileShrPtr source, defOParamListShdPtr base, defOParamListShdPtr workPar, PPpointListShdPtr bPointsList): PProgramResolverStrategy(destination, source), baseCoord(base), workParams(workPar), basePointsList(bPointsList){};
			PProgGcodeResolverStrategy& operator=(const PProgGcodeResolverStrategy&)=delete;
				
			virtual InterpretProgErr interpretProg() final;
				

	};

#endif