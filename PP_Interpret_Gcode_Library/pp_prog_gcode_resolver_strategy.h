#ifndef _PP_PROG_GCODE_RESOLVER_STRATEGY_H
	#define _PP_PROG_GCODE_RESOLVER_STRATEGY_H
	
	#include <vector>
	
	#include "pp_program_resolver_strategy.h"
	#include "pstring.h"
	#include "pp_point.h"
	#include "pp_paramlist.h"

	
class PProgGcodeResolverStrategy : public PProgramResolverStrategy{
	
	private:
			defOParamListShdPtr phyCoord;
			defOParamListShdPtr workParams;
			PPpointListShdPtr basePointsList;
	
			enum{CLOCKWISE,COUNTERCLOCKWISE};
	
			bool writeInAboluteValues=false;
			bool G00occured=false;
			int GcodeStandardCycle=0;
			int G81nrOfRepetitions=0;
	
	
			PPpoint<double> basePoint;
			PPpoint<double> startPoint;
			PPpoint<double> endPoint;
			PStringList repetitionsList;
	
			void resetInterpretSettings();
			void interpretGcode(PString &program);
			void interpretMcode(PString &program);
	
			PPpointXY<double> getRealEndPointOfArc(PPpointXY<double> &circleCenterPoint, PPpointXY<double> &startCirclePoint, PPpointXY<double> &endCirclePoint, int turnCircle);
			double arcImplicitFunction(double X, double Y, double R2);
			void writeG00Line(PPpoint<double> &point);
			void writePointParam(PPpoint<double> &point);
			int trimToRange(int value, int upperLimit, int lowerLimit);
		public:
			PProgGcodeResolverStrategy()=delete;
			PProgGcodeResolverStrategy(PIOdeviceShrPtr destination, PFileShrPtr source, defOParamListShdPtr phy, defOParamListShdPtr workPar, PPpointListShdPtr bPointsList): PProgramResolverStrategy(destination, source), phyCoord(phy), workParams(workPar), basePointsList(bPointsList){};
			PProgGcodeResolverStrategy& operator=(const PProgGcodeResolverStrategy&)=delete;
				
			virtual InterpretProgErr interpretProg() final;

	};
	
	using PProgGcodeResolverStrategyShrPtr = shared_ptr<PProgGcodeResolverStrategy>;
#endif