#ifndef _PP_PROG_WEDM_GCODE_RESOLVER_STRATEGY_H
	#define _PP_PROG_WEDM_GCODE_RESOLVER_STRATEGY_H
	
	#include <vector>
	
	#include "pp_prog_gcode_resolver_strategy.h"
	#include "pstring.h"
	#include "pp_point.h"
	#include "pp_paramlist.h"

	
class PProgWedmGcodeResolverStrategy : public PProgGcodeResolverStrategy{
	
	private:
			PPpoint<int> endPoint;			
		protected:
			virtual void resetInterpretSettings() final;
			virtual void interpretGcode(PString &program) final;
			virtual void writePointParam(PPpoint<int> &point) final;
		public:
			PProgWedmGcodeResolverStrategy()=delete;
			PProgWedmGcodeResolverStrategy(PIOdeviceShrPtr destination, PFileShrPtr source, defOParamListShdPtr base, defOParamListShdPtr workPar, PPpointIntListShdPtr bPointsList): PProgGcodeResolverStrategy(destination, source, base, workPar, bPointsList){};
			PProgWedmGcodeResolverStrategy& operator=(const PProgGcodeResolverStrategy&)=delete;
				

	};
	
	using PProgGcodeResolverStrategyShrPtr = shared_ptr<PProgGcodeResolverStrategy>;
#endif