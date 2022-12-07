#include "CppUTest/TestHarness.h"

#include "pp_file_string_mock.h"
#include "pp_prog_edf_resolver_strategy.h"
#include "pp_paramlist.h"
#include "pp_param.h"
#include "stdio.h"

TEST_GROUP(PProgWedmEDFResolverStrategyTestGroup)
{
	PFileShrPtr progFile=make_shared<PFileStringMock>("C:/Gc_test/test.txt");
	PFileShrPtr progAfterItpFile=make_shared<PFileStringMock>("C:/Gc_test/test2.txt");
	
	defOParamListShdPtr phyCoord=make_shared<defOParamList>();
	defOParamListShdPtr workParams=make_shared<defOParamList>();
		
	PPpointIntListShdPtr gBasePoints=make_shared<PPpointIntList>();
	
	PProgWedmEDFResolverStrategy itpStrategy{progAfterItpFile, progFile, workParams, gBasePoints};
	
  void setup() {
			phyCoord->insert(PParamPair('X', make_shared<defOParam>("X", 100000, 0, 999000, 5, 3)));
			phyCoord->insert(PParamPair('Y', make_shared<defOParam>("Y", 100000, 0, 999000, 5, 3)));
			phyCoord->insert(PParamPair('Z', make_shared<defOParam>("Z", 100000, 0, 999000, 5, 3)));
			phyCoord->insert(PParamPair('U', make_shared<defOParam>("U", 100000, 0, 999000, 5, 3)));
			phyCoord->insert(PParamPair('V', make_shared<defOParam>("V", 100000, 0, 999000, 5, 3)));
			phyCoord->insert(PParamPair('z', make_shared<defOParam>("z", 100000, 0, 999000, 5, 3)));

			gBasePoints->insert(gBasePoints->begin(), 5, PPpoint<int>{phyCoord->getParamsValues(), phyCoord->getParamsLimits()});
			if(!gBasePoints->empty()){
		//		basePoint=gBasePoints->front().;
			}
		
			workParams->insert(PParamPair('P', make_shared<defOParam>("work threshold", 50, 1, 90)));
	//		workParams->insert(PParamPair('z', make_shared<defOParam>("circuit threshold", 50, 1, 90)));
			workParams->insert(PParamPair('T', make_shared<defOParam>("impulse", 4750, 1000, 9000, 250, 3)));
			workParams->insert(PParamPair('t', make_shared<defOParam>("break", 160000, 10000, 900000, 100, 3)));
//			workParams->insert(PParamPair('x', make_shared<defOParam>("no. of impulse", 2, 1, 9)));
//			workParams->insert(PParamPair('D', make_shared<defOParam>("wire feed", 6, 1, 9)));
			workParams->insert(PParamPair('N', make_shared<defOParam>("wire tension", 3, 1, 3)));
//			workParams->insert(PParamPair('f', make_shared<defOParam>("velocity", 2500, 1, 2500)));
		
		
	}
	
  void teardown() {
		phyCoord->clear();
		workParams->clear();
		gBasePoints->clear();
	}
};


TEST(PProgWedmEDFResolverStrategyTestGroup, interpretProgTest)
{
	string data;
	
//-2           9000      1000     12000
//5
//       0 100000000 100000000    200000    200000
//       0 100000000 105000000         0         0
//       0 105000000 105000000    200000    200000
//       0 105000000 100000000        -0        -0
//  -29999 100000000 100000000    -29999    -29999

//5
//       0 100000000 100000000    200000    200000
//       0 100000000 105000000         0         0
//       0 105000000 105000000    200000    200000
//       0 105000000 100000000        -0        -0
//  -29999 100000000 100000000    -29999    -29999
//	
//
	
	
	progFile->open(PIOdevice::WriteOnly);
	progFile->write("-2           4400      2000     10000\r\n5\r\n       0 100000000 100000000    200000    200000\r\n       0 100000000 105000000         0         0\r\n       0 105000000 105000000    200000    200000\r\n       0 105000000 100000000        -0        -0\r\n  -29999 100000000 100000000    -29999    -29999\r\n\r\n5\r\n       0 100000000 100000000    200000    200000\r\n       0 100000000 105000000         0         0\r\n       0 105000000 105000000    200000    200000\r\n       0 105000000 100000000        -0        -0\r\n  -29999 100000000 100000000    -29999    -29999\r\n\r\n\r\n");
	
	progFile->close();
	
	
	itpStrategy.interpretProg();
	
	progAfterItpFile->open(PIOdevice::ReadOnly);
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 100000 100000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 105000 100000 100000 105000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());

	data=to_string((G_KOD<<10) | G00);
	data+=" 105000 105000 100000 105000 105000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 105000 100000 100000 105000 100000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 100000 100000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	progAfterItpFile->close();
}

TEST(PProgWedmEDFResolverStrategyTestGroup, interpretProgWithBlocksTest)
{
	string data;
	
	progFile->open(PIOdevice::WriteOnly);
	progFile->write("-6           4400      2000     10000\r\n2\r\n       0 100000000 100000000    200000    200000\r\n  -29999 100000000 105000000    -29999    -29999\r\n\r\n2\r\n       0 105000000 100000000    200000    200000\r\n  -29999 105000000 105000000    -29999    -29999\r\n\r\n2\r\n       0 110000000 100000000    200000    200000\r\n  -29999 110000000 105000000    -29999    -29999\r\n\r\n2\r\n       0 100000000 100000000    200000    200000\r\n  -29999 100000000 105000000    -29999    -29999\r\n\r\n2\r\n       0 105000000 100000000    200000    200000\r\n  -29999 105000000 105000000    -29999    -29999\r\n\r\n2\r\n       0 110000000 100000000    200000    200000\r\n  -29999 110000000 105000000    -29999    -29999\r\n\r\n\r\n");
	progFile->close();
	
	
	itpStrategy.interpretProg();
	
	progAfterItpFile->open(PIOdevice::ReadOnly);
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 100000 100000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 105000 100000 100000 105000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());

	data=to_string((M_KOD<<10) | M00);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());

	data=to_string((G_KOD<<10) | G00);
	data+=" 105000 100000 100000 105000 100000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 105000 105000 100000 105000 105000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((M_KOD<<10) | M00);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 110000 100000 100000 110000 100000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 110000 105000 100000 110000 105000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	progAfterItpFile->close();
}



TEST(PProgWedmEDFResolverStrategyTestGroup, interpretProgWithChangeParamTest)
{
	string data;
	
//-2           9000      1000     12000
//5
//       0 100000000 100000000    200000    200000
//       0 100000000 105000000         0         0
//       0 105000000 105000000    200000    200000
//       0 105000000 100000000        -0        -0
//  -29999 100000000 100000000    -29999    -29999

//5
//       0 100000000 100000000    200000    200000
//       0 100000000 105000000         0         0
//       0 105000000 105000000    200000    200000
//       0 105000000 100000000        -0        -0
//  -29999 100000000 100000000    -29999    -29999

//#
//0 3 3 3 3 3 3 3 0 0 0 3 0 0 0 0
//#
//$
//1
//0 1 0 5
//0 2 2 2 2 2 2 2 1 0 0 2 0 0 0 0
//$
//
	
	progFile->open(PIOdevice::WriteOnly);
	progFile->write("-2           9000      1000     12000\r\n5\r\n       0 100000000 100000000    200000    200000\r\n       0 100000000 105000000         0         0\r\n       0 105000000 105000000    200000    200000\r\n       0 105000000 100000000        -0        -0\r\n  -29999 100000000 100000000    -29999    -29999\r\n\r\n5\r\n       0 100000000 100000000    200000    200000\r\n       0 100000000 105000000         0         0\r\n       0 105000000 105000000    200000    200000\r\n       0 105000000 100000000        -0        -0\r\n  -29999 100000000 100000000    -29999    -29999\r\n\r\n#\r\n0 3 3 3 3 3 3 3 0 0 0 3 0 0 0 0\r\n#\r\n$\r\n1\r\n0 1 0 5\r\n0 2 2 2 2 2 2 2 1 0 0 2 0 0 0 0\r\n$\r\n\r\n");
	progFile->close();
	
	itpStrategy.interpretProg();
	
	progAfterItpFile->open(PIOdevice::ReadOnly);
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G92);
	data+=" 8000 60000 30 -1 3 -1 -1 -1\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	
	data=to_string((M_KOD<<10) | M41);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());

	data=to_string((M_KOD<<10) | M45);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((M_KOD<<10) | M43);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((M_KOD<<10) | M39);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 100000 100000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 105000 100000 100000 105000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G92);
	data+=" 6000 40000 20 -1 2 -1 -1 -1\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());


	data=to_string((M_KOD<<10) | M40);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
		data=to_string((M_KOD<<10) | M45);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((M_KOD<<10) | M43);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((M_KOD<<10) | M39);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	

	data=to_string((G_KOD<<10) | G00);
	data+=" 105000 105000 100000 105000 105000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 105000 100000 100000 105000 100000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string((G_KOD<<10) | G00);
	data+=" 100000 100000 100000 100000 100000 100000\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	data=to_string(START_PROG<<10);
	data+="\r\n";
	STRCMP_EQUAL(data.c_str(), progAfterItpFile->readLine().c_str());
	
	progAfterItpFile->close();
}




