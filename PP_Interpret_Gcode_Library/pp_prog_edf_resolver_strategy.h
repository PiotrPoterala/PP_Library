#ifndef _PP_PROG_EDF_RESOLVER_STRATEGY_H
	#define _PP_PROG_EDF_RESOLVER_STRATEGY_H
	
	#include <vector>
	
	#include "pp_iodevice.h"
	#include "pp_program_resolver_strategy.h"
	#include "pstring.h"
	#include "pp_point.h"
	#include "pp_paramlist.h"

	class PEDFlinePar{

	public:
			PEDFlinePar(int pblock=0, int psegment=0, int pthreshOfWork=0, int pthreshOfCircuit=0, int ptimeOfImpulse=0, int ptimeOfBreak=0, int pwireFeed=0, int pwireTension=0, int pfeed=0, int ptoolsMask1=0,
									int ptoolsMask2=0, int ptoolsMask3=0, int pfunMask=0):block(pblock), segment(psegment), threshOfWork(pthreshOfWork), threshOfCircuit(pthreshOfCircuit), timeOfImpulse(ptimeOfImpulse),
					timeOfBreak(ptimeOfBreak), wireFeed(pwireFeed), wireTension(pwireTension), feed(pfeed), toolsMask1(ptoolsMask1), toolsMask2(ptoolsMask2), toolsMask3(ptoolsMask3), funMask(pfunMask){}
			int block;
			int segment;
			int threshOfWork;
			int threshOfCircuit;
			int timeOfImpulse;
			int timeOfBreak;
			int wireFeed;
			int wireTension;
			int feed;
			int toolsMask1;
			int toolsMask2;
			int toolsMask3;
			int funMask;
	};

	
	class PProgEDFResolverStrategy : public PProgramResolverStrategy{
	
	protected:
			defOParamListShdPtr baseCoord;
			defOParamListShdPtr phyCoord;
			defOParamListShdPtr workParams;
	
			vector<PEDFlinePar*> changeParList;
		
			InterpretProgErr getPointOfChangeParFromEDFprog();
			void interpretTextLineWithChangeParList(PEDFlinePar &linePar);
			PPpoint<int> getPointFromTextLine(PString &program);
	//		int trimToRange(int value, int upperLimit, int lowerLimit);
			virtual void interpretTextLineWithCoordinates(PString &program)=0;
		public:
			PProgEDFResolverStrategy()=delete;
			PProgEDFResolverStrategy(PIOdeviceShrPtr destination, PFileShrPtr source, defOParamListShdPtr phy, defOParamListShdPtr workPar): PProgramResolverStrategy(destination, source), phyCoord(phy), workParams(workPar){};
			virtual InterpretProgErr interpretProg() final;

	};
	
	
class PProgWedmEDFResolverStrategy : public PProgEDFResolverStrategy{
	
	protected:
			virtual void interpretTextLineWithCoordinates(PString &program) final;

	
	public:
			PProgWedmEDFResolverStrategy()=delete;
			PProgWedmEDFResolverStrategy (PIOdeviceShrPtr destination, PFileShrPtr source, defOParamListShdPtr phy, defOParamListShdPtr workPar): PProgEDFResolverStrategy(destination, source, phy, workPar){};

	};

class PProgDrillEDFResolverStrategy : public PProgEDFResolverStrategy{
	
		protected:
			virtual void interpretTextLineWithCoordinates(PString &program) final;
	
	
		public:
			PProgDrillEDFResolverStrategy()=delete; 
			PProgDrillEDFResolverStrategy (PIOdeviceShrPtr destination, PFileShrPtr source, defOParamListShdPtr phy, defOParamListShdPtr workPar): PProgEDFResolverStrategy(destination, source, phy, workPar){};

	};
	
	
	using PProgWedmEDFResolverStrategyShrPtr = shared_ptr<PProgWedmEDFResolverStrategy>;
	using PProgDrillEDFResolverStrategyShrPtr = shared_ptr<PProgDrillEDFResolverStrategy>;
#endif