#ifndef _PP_PROGRAM_RESOLVER_STRATEGY_H
	#define _PP_PROGRAM_RESOLVER_STRATEGY_H
	
	#include "pp_iodevice.h"
	#include "pp_file.h"

constexpr int START_PROG=1;
constexpr int STOP_PROG=1;
constexpr int G_KOD=2;
constexpr int M_KOD=3;

#define GKOD_NIEINTERPRETOWANY (-1)
constexpr int G00=0;
constexpr int G01=1;
constexpr int G02=2;
constexpr int G03=3;
constexpr int G04=4;
constexpr int G50=50;
constexpr int G80=80;
constexpr int G81=81;
constexpr int G87=87;
constexpr int G88=88;
constexpr int G92=92;

#define G0_NR_OF_PAR        6
#define G2_NR_OF_PAR        5
#define G4_NR_OF_PAR        1
#define G87_NR_OF_PAR       6
#define G92_NR_OF_PAR 		8

#define MKOD_NIEINTERPRETOWANY (-1)
#define M00 0
#define M38 38
#define M39 39
#define M40 40
#define M41 41
#define M42 42
#define M43 43
#define M44 44
#define M45 45
#define M46 46

enum class InterpretProgErr{idNO_ERRORS, idNO_FILES, idINCORRECT_NR_OF_BLOCKS, idLACK_MODULO, idLACK_G50_G59};
	
class PProgramResolverStrategy{
		
		protected:
			PIOdeviceShrPtr destDevice;
			PFileShrPtr sourceFile;
			
		public:
			PProgramResolverStrategy()=delete;
			PProgramResolverStrategy(PIOdeviceShrPtr destination, PFileShrPtr source): destDevice(destination), sourceFile(source){};
			virtual ~PProgramResolverStrategy(){};
	
			virtual InterpretProgErr interpretProg()=0;

	};
	
using PProgramResolverStrategyShrPtr = shared_ptr<PProgramResolverStrategy>;
	
class PProgramResolverContext{
		
		private:
			PProgramResolverStrategyShrPtr resolver;
	
		public:
			PProgramResolverContext()=delete;
			PProgramResolverContext(PProgramResolverStrategyShrPtr res): resolver(res){};
//			~PProgramResolverContext(){delete this->resolver;};
				
    void setResolver(PProgramResolverStrategyShrPtr resolver){
     //   delete this->resolver;
        this->resolver = resolver;
    }

		InterpretProgErr interpretProg(){
			
			return resolver->interpretProg();
		};
		
	};
	
using PProgramResolverContextPtr = unique_ptr<PProgramResolverContext>; 	
	
#endif