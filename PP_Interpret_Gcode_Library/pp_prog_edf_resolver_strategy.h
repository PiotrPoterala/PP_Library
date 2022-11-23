#ifndef _PP_PROG_EDF_RESOLVER_STRATEGY_H
	#define _PP_PROG_EDF_RESOLVER_STRATEGY_H
	
	#include <vector>
	
	#include "pp_iodevice.h"
	#include "pp_program_resolver_strategy.h"
	#include "pstring.h"
	#include "pp_point.h"
	#include "pp_paramlist.h"
	
	map<char, vector<int>> parTab={pair<char, vector<int>>{'X', {10,20,30,40,50,60,70,80,90}}};
	

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
		//	defOParamListShdPtr baseCoord;
		//	defOParamListShdPtr phyCoord;
			PPpointIntShdPtr basePoint;
			defOParamListShdPtr workParams;
			map<char, vector<int>> changeParRealValueList;
	
			vector<PEDFlinePar*> changeParList;
		
			InterpretProgErr getPointOfChangeParFromEDFprog();
			void interpretTextLineWithChangeParList(PEDFlinePar &linePar);
			PPpoint<int> getPointFromTextLine(PString &program);
			double getDrillingDepthFromTextLine(PString &program);
			int getWorkParamFromParTab(char acronim, int index);
	//		int trimToRange(int value, int upperLimit, int lowerLimit);
	
			void writeG00Line(PPpoint<int> &point);
			void writePointParam(PPpoint<int> &point);
	
			virtual void interpretTextLineWithCoordinates(PString &program)=0;
		public:
			PProgEDFResolverStrategy()=delete;
			PProgEDFResolverStrategy(PIOdeviceShrPtr destination, PFileShrPtr source, PPpointIntShdPtr basePt, defOParamListShdPtr workPar): PProgramResolverStrategy(destination, source), basePoint(basePt), workParams(workPar){
			
				changeParRealValueList.insert(pair<char, vector<int>>{'P', {10,20,30,40,50,60,70,80,90}});
				changeParRealValueList.insert(pair<char, vector<int>>{'z', {10,20,30,40,50,60,70,80,90}});
				changeParRealValueList.insert(pair<char, vector<int>>{'D', {1, 2, 3, 4, 5, 6, 7, 8, 9}});
				changeParRealValueList.insert(pair<char, vector<int>>{'N', {1, 2, 3}});
				changeParRealValueList.insert(pair<char, vector<int>>{'T', {4, 6, 8}});
				changeParRealValueList.insert(pair<char, vector<int>>{'t', {20, 40, 60, 80, 100, 120, 160, 200, 400}});
				changeParRealValueList.insert(pair<char, vector<int>>{'f', {1, 2, 5, 7, 11, 16, 22, 32, 47, 67, 95, 137, 203, 282, 425, 567}});
			
			};
			virtual InterpretProgErr interpretProg() final;

	};
	
	
class PProgWedmEDFResolverStrategy : public PProgEDFResolverStrategy{
	
	protected:
			virtual void interpretTextLineWithCoordinates(PString &program) final;

	
	public:
			PProgWedmEDFResolverStrategy()=delete;
			PProgWedmEDFResolverStrategy (PIOdeviceShrPtr destination, PFileShrPtr source, PPpointIntShdPtr basePt, defOParamListShdPtr workPar): PProgEDFResolverStrategy(destination, source, basePt, workPar){};

	};

class PProgDrillEDFResolverStrategy : public PProgEDFResolverStrategy{
	
		protected:
			virtual void interpretTextLineWithCoordinates(PString &program) final;
	
	
		public:
			PProgDrillEDFResolverStrategy()=delete; 
			PProgDrillEDFResolverStrategy (PIOdeviceShrPtr destination, PFileShrPtr source, PPpointIntShdPtr basePt, defOParamListShdPtr workPar): PProgEDFResolverStrategy(destination, source, basePt, workPar){};

	};
	
	
	using PProgWedmEDFResolverStrategyShrPtr = shared_ptr<PProgWedmEDFResolverStrategy>;
	using PProgDrillEDFResolverStrategyShrPtr = shared_ptr<PProgDrillEDFResolverStrategy>;
#endif