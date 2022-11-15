#include "CppUTest/TestHarness.h"

#include "pp_file_string_mock.h"
#include "pp_prog_wedm_gcode_resolver_strategy.h"
#include "pp_paramlist.h"
#include "pp_param.h"
#include "stdio.h"

TEST_GROUP(PProgWedmGcodeResolverStrategyTestGroup)
{
	PFileShrPtr progFile=make_shared<PFileStringMock>("C:/Gc_test/test.txt");
	PFileShrPtr progAfterItpFile=make_shared<PFileStringMock>("C:/Gc_test/test2.txt");
	
	defOParamListShdPtr phyCoord=make_shared<defOParamList>();
	defOParamListShdPtr baseCoord=make_shared<defOParamList>();
	defOParamListShdPtr workParams=make_shared<defOParamList>();
		
	PPpointIntListShdPtr gBasePoints=make_shared<PPpointIntList>();
	
	PProgWedmGcodeResolverStrategy itpStrategy{progAfterItpFile, progFile, baseCoord, workParams, gBasePoints};
	
  void setup() {
			phyCoord->insert(PParamPair('X', make_shared<defOParam>("X", 100000, 0, 999000, 5, 3)));
			phyCoord->insert(PParamPair('Y', make_shared<defOParam>("Y", 100000, 0, 999000, 5, 3)));
			phyCoord->insert(PParamPair('Z', make_shared<defOParam>("Z", 100000, 0, 999000, 5, 3)));
			phyCoord->insert(PParamPair('z', make_shared<defOParam>("z", 100000, 0, 999000, 5, 3)));

			gBasePoints->insert(gBasePoints->begin(), 5, PPpoint<int>{phyCoord->getParamsValues(), phyCoord->getParamLimits()});
			
			baseCoord->insert(PParamPair('X', make_shared<defOParam>("X", 100000, -999000, 999000, 5, 3)));
			baseCoord->insert(PParamPair('Y', make_shared<defOParam>("Y", 100000, -999000, 999000, 5, 3)));
			baseCoord->insert(PParamPair('Z', make_shared<defOParam>("Z", 100000, -999000, 999000, 5, 3)));
			baseCoord->insert(PParamPair('z', make_shared<defOParam>("z", 100000, -999000, 999000, 5, 3)));
		
			workParams->insert(PParamPair('P', make_shared<defOParam>("work threshold", 50, 1, 90)));
			workParams->insert(PParamPair('z', make_shared<defOParam>("circuit threshold", 50, 1, 90)));
			workParams->insert(PParamPair('T', make_shared<defOParam>("impulse", 4750, 1000, 9000, 250, 3)));
			workParams->insert(PParamPair('t', make_shared<defOParam>("break", 160000, 10000, 900000, 100, 3)));
			workParams->insert(PParamPair('x', make_shared<defOParam>("no. of impulse", 2, 1, 9)));
			workParams->insert(PParamPair('D', make_shared<defOParam>("wire feed", 6, 1, 9)));
			workParams->insert(PParamPair('N', make_shared<defOParam>("wire tension", 3, 1, 3)));
			workParams->insert(PParamPair('f', make_shared<defOParam>("velocity", 2500, 1, 2500)));
		
		
	}
	
  void teardown() {
		phyCoord->clear();
		baseCoord->clear();
		workParams->clear();
		gBasePoints->clear();
	}
};


TEST(PProgWedmGcodeResolverStrategyTestGroup, interpretG00Test)
{
	string data;
	
	progFile->open(PIOdevice::WriteOnly);
	progFile->write("%\nG56\nG00 X0 Y0 Z0\nG00 X-2\nG00 X2\n%\n");
	progFile->close();
	
	
	itpStrategy.interpretProg();
	
	progAfterItpFile->open(PIOdevice::ReadOnly);
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G50);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 98000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());

	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	progAfterItpFile->close();
}

TEST(PProgWedmGcodeResolverStrategyTestGroup, interpretG81_80Test)
{
	string data;
	
	progFile->open(PIOdevice::WriteOnly);
	progFile->write("%\nG56\nG00 X0 Y0 Z0\nG81 L2\nG00 Z-2\nG00 Z2\nG00 X2\nG80\n%\n");
	progFile->close();
	
	
	itpStrategy.interpretProg();
	
	progAfterItpFile->open(PIOdevice::ReadOnly);
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G50);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 98000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());

	data=to_string((G_KOD<<10) | G00);
	data+=" 102000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 102000 100000 98000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 102000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());

	data=to_string((G_KOD<<10) | G00);
	data+=" 104000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	progAfterItpFile->close();
}

TEST(PProgWedmGcodeResolverStrategyTestGroup, interpretG02Test)
{
	string data;
	
	progFile->open(PIOdevice::WriteOnly);
	progFile->write("%\nG56\nG00 X0 Y0 Z0\nG02 X2 Y-2 I0 J-2\n%\n");
	progFile->close();
	
	
	itpStrategy.interpretProg();
	
	progAfterItpFile->open(PIOdevice::ReadOnly);
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G50);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G02);
	data+=" 102000 98000 100000 100000 98000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	progAfterItpFile->close();
}

TEST(PProgWedmGcodeResolverStrategyTestGroup, interpretG87Test)
{
	string data;
	
	progFile->open(PIOdevice::WriteOnly);
	progFile->write("%\nG56\nG00 X0 Y0 Z0\nG87 z2 s20 d1\n%\n");
	progFile->close();
	
	
	itpStrategy.interpretProg();
	
	progAfterItpFile->open(PIOdevice::ReadOnly);
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G50);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G87);
	data+=" 100000 100000 100000 0 0 80000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 98000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 101000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	progAfterItpFile->close();
}

TEST(PProgWedmGcodeResolverStrategyTestGroup, interpretG88Test)
{
	string data;
	
	progFile->open(PIOdevice::WriteOnly);
	progFile->write("%\nG56\nG00 X0 Y0 Z0\nG88 s20\nG00 z-2\nG00 z3\n%\n");
	progFile->close();
	
	
	itpStrategy.interpretProg();
	
	progAfterItpFile->open(PIOdevice::ReadOnly);
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G50);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G88);
	data+=" 100000 100000 100000 0 0 80000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 98000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 0 0 101000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	progAfterItpFile->close();
}