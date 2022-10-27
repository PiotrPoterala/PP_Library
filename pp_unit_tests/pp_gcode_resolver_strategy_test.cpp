#include "CppUTest/TestHarness.h"

#include "pp_file_string_mock.h"
#include "pp_prog_gcode_resolver_strategy.h"
#include "pp_paramlist.h"
#include "pp_param.h"
#include "stdio.h"

TEST_GROUP(PProgGcodeResolverStrategyTestGroup)
{
	PFileShrPtr progFile=make_shared<PFileStringMock>("C:/Gc_test/test.txt");
	PFileShrPtr progAfterItpFile=make_shared<PFileStringMock>("C:/Gc_test/test2.txt");
	
	defOParamListShdPtr phyCoord=make_shared<defOParamList>();
	defOParamListShdPtr workParams=make_shared<defOParamList>();
		
	PPpointList gBasePoints;
	
	PProgGcodeResolverStrategy itpStrategy{progAfterItpFile, progFile, phyCoord, workParams, gBasePoints};
	
  void setup() {
			phyCoord->insert(PParamPair('X', make_shared<defOParam>("X", 100000, -999000, 999000, 5, 3)));
			phyCoord->insert(PParamPair('Y', make_shared<defOParam>("Y", 100000, -999000, 999000, 5, 3)));

			gBasePoints=PPpointList{5, PPpoint<double>(phyCoord->getParamsRealValues())};
		
			workParams->insert(PParamPair('P', make_shared<defOParam>(strings->find("thrw")->second, 50, 1, 90)));
			workParams->insert(PParamPair('z', make_shared<defOParam>(strings->find("thrc")->second, 50, 1, 90)));
			workParams->insert(PParamPair('T', make_shared<defOParam>("impulse", 4750, 1000, 9000, 250, 3)));
			workParams->insert(PParamPair('t', make_shared<defOParam>(strings->find("brk")->second, 1160*pow_pp(10, breakUnit), 10*pow_pp(10, breakUnit), 900*pow_pp(10, breakUnit), 1*pow_pp(10, breakUnit), breakUnit)));
			workParams->insert(PParamPair('x', make_shared<defOParam>(strings->find("noImp")->second, 2, 1, 9)));
			workParams->insert(PParamPair('D', make_shared<defOParam>(strings->find("wFeed")->second, 6, 1, 9)));
			workParams->insert(PParamPair('N', make_shared<defOParam>(strings->find("wTens")->second, 3, 1, 3)));
			workParams->insert(PParamPair('f', make_shared<defOParam>("velocity", 2500, 1, 2500)));
		
	}
	
  void teardown() {
		phyCoord->clear();
		workParams->clear();
	}
};


TEST(PProgGcodeResolverStrategyTestGroup, findDataAfterAcronimTest)
{
	
	progFile->open(PIOdevice::WriteOnly);
	progFile->write("G56\nG00 X0 Y0 Z0 A0\nG00 Z-2\nG00 Z2\n");
	progFile->close();
	
	
	PString str("X10.123 Y20.458");
	STRCMP_EQUAL("10.123", str.findDataAfterAcronim('X').c_str());
	STRCMP_EQUAL("20.458", str.findDataAfterAcronim('Y').c_str());
}


TEST(PStringTestGroup, midTest)
{
	PString str("X10.123 Y20.458");
	
	STRCMP_EQUAL(".123 Y", str.mid(3,6).c_str());
}

TEST(PStringTestGroup, toIntTest)
{
	PString str("234");
	LONGS_EQUAL(234, str.toInt());
	
	str=" ";
	LONGS_EQUAL(0, str.toInt());
	
	str="1 ";
	LONGS_EQUAL(1, str.toInt());
	
	str="2;";
	LONGS_EQUAL(2, str.toInt());
	
	str="CD";
	LONGS_EQUAL(205, str.toInt(16));
	
}

TEST(PStringTestGroup, findValueAfterAcronimTest)
{
	PString str("X10.123 Y20.458");
	
	DOUBLES_EQUAL(10.123, str.findValueAfterAcronim('X', 100000), 0.001);
	DOUBLES_EQUAL(456, str.findValueAfterAcronim('V', 456), 0.001);
}

TEST(PStringTestGroup, findValuesAfterAcronimTest)
{
	PString str("X10.123 Y20.458");
	map<char, double> val=str.findValuesAfterAcronims();
	LONGS_EQUAL(2, val.size());
	
	auto it=val.begin();
	
	BYTES_EQUAL('X', (*it).first);
	DOUBLES_EQUAL(10.123, (*it).second, 0.001);
	
	it++;
	BYTES_EQUAL('Y', (*it).first);
	DOUBLES_EQUAL(20.458, (*it).second, 0.001);
	
}

TEST(PStringTestGroup, trimmedTest)
{
	PString str("  lots\t of\nwhitespace\r\n ");
	STRCMP_EQUAL("lots\t of\nwhitespace", str.trimmed().c_str());
	
	str="lots of whitespace";
	STRCMP_EQUAL("lots of whitespace", str.trimmed().c_str());
}


TEST(PStringTestGroup, split)
{
	PString str("login, pass1, pass2");
	vector<PString> vec=str.split(',');
	
	LONGS_EQUAL(3, vec.size());
	STRCMP_EQUAL("login", vec.at(0).c_str());
	STRCMP_EQUAL(" pass1", vec.at(1).c_str());
	STRCMP_EQUAL(" pass2", vec.at(2).c_str());
	
	str="login";
	vec=str.split(',');
	LONGS_EQUAL(1, vec.size());
	STRCMP_EQUAL("login", vec.at(0).c_str());
	
	str="login,,pass2";
	vec=str.split(',');
	LONGS_EQUAL(2, vec.size());
	STRCMP_EQUAL("login", vec.at(0).c_str());
	STRCMP_EQUAL("pass2", vec.at(1).c_str());
	
	vec=str.split(',',PString::KeepEmptyParts);
	LONGS_EQUAL(3, vec.size());
	STRCMP_EQUAL("login", vec.at(0).c_str());
	STRCMP_EQUAL("", vec.at(1).c_str());
	STRCMP_EQUAL("pass2", vec.at(2).c_str());
}



TEST(PStringTestGroup, splitWithClamps)
{
        PString str(" \"pio\", \"stasiek\"");

				vector<string> vec=str.splitWithClamps(',', '"');
				LONGS_EQUAL(2, vec.size());
				STRCMP_EQUAL("pio", vec.at(0).c_str());
				STRCMP_EQUAL("stasiek", vec.at(1).c_str());
	
				vec=str.splitWithClamps('.', '"');
				LONGS_EQUAL(1, vec.size());
				STRCMP_EQUAL("pio", vec.at(0).c_str());

				str=",'stasiek'";
        vec=str.splitWithClamps(',', '\'');
				LONGS_EQUAL(1, vec.size());
				STRCMP_EQUAL("stasiek", vec.at(0).c_str());

        str="ANET \"pio\", \"stasiek\"";
				vec=str.splitWithClamps(',', '"');
				LONGS_EQUAL(2, vec.size());
				STRCMP_EQUAL("pio", vec.at(0).c_str());
				STRCMP_EQUAL("stasiek", vec.at(1).c_str());

        str="\"\", \"\"";
				vec=str.splitWithClamps(',', '"');
				LONGS_EQUAL(2, vec.size());
				STRCMP_EQUAL("", vec.at(0).c_str());
				STRCMP_EQUAL("", vec.at(1).c_str());
}
