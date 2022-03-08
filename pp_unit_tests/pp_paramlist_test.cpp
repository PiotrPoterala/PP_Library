#include "CppUTest/TestHarness.h"

#include "pp_paramlist.h"
#include "pp_param.h"
#include "stdio.h"


#define COORD_PRECISION_MM 0.0025
#define COORD_UNIT 6	

#define MIN_PHY_COORD_MM		0
#define MIN_BASE_COORD_MM	(-999)
#define MAX_PHY_COORD_MM		999
#define MAX_BASE_COORD_MM		999

defOParamList *phyCoord;

TEST_GROUP(defOParamTestGroup)
{
  void setup() {
		phyCoord=new defOParamList();
		phyCoord->insert(pair<char, defOParamGeneral*>('X', new defOParam("X", 123*pow(10.0, COORD_UNIT), 100*pow(10.0, COORD_UNIT), COORD_PRECISION_MM*pow(10.0, COORD_UNIT), COORD_UNIT, MIN_PHY_COORD_MM*pow(10.0, COORD_UNIT), MAX_PHY_COORD_MM*pow(10.0, COORD_UNIT))));
		phyCoord->insert(pair<char, defOParamGeneral*>('Y', new defOParam("Y", 148*pow(10.0, COORD_UNIT), 100*pow(10.0, COORD_UNIT), COORD_PRECISION_MM*pow(10.0, COORD_UNIT), COORD_UNIT, MIN_PHY_COORD_MM*pow(10.0, COORD_UNIT), MAX_PHY_COORD_MM*pow(10.0, COORD_UNIT))));

	}
	
  void teardown() {
	
		delete phyCoord;
	}
};


TEST(defOParamTestGroup, getParamValue)
{
	LONGS_EQUAL(123*pow(10.0, COORD_UNIT), phyCoord->getParamValue('X'));
	LONGS_EQUAL(0, phyCoord->getParamValue('g'));
}

TEST(defOParamTestGroup, getParamUpperLimit)
{
	LONGS_EQUAL(MAX_PHY_COORD_MM*pow(10.0, COORD_UNIT), phyCoord->getParamUpperLimit('X'));
	LONGS_EQUAL(0, phyCoord->getParamValue('g'));
}

TEST(defOParamTestGroup, getParamUnit)
{
	LONGS_EQUAL(COORD_UNIT, phyCoord->getParamUnit('X'));
	LONGS_EQUAL(0, phyCoord->getParamValue('g'));
}

TEST(defOParamTestGroup, getStringWithParams)
{
	STRCMP_EQUAL("X123.000000 Y148.000000", phyCoord->getStringWithParams().c_str());

}

//TEST(PStringTestGroup, findValueAfterAcronimTest)
//{
//	PString str("X10.123 Y20.458");
//	
//	DOUBLES_EQUAL(10.123, str.findValueAfterAcronim('X', 100000), 0.001);
//	DOUBLES_EQUAL(456, str.findValueAfterAcronim('V', 456), 0.001);
//}

//TEST(PStringTestGroup, findValuesAfterAcronimTest)
//{
//	PString str("X10.123 Y20.458");
//	map<char, double> val=str.findValuesAfterAcronims();
//	LONGS_EQUAL(2, val.size());
//	
//	auto it=val.begin();
//	
//	BYTES_EQUAL('X', (*it).first);
//	DOUBLES_EQUAL(10.123, (*it).second, 0.001);
//	
//	it++;
//	BYTES_EQUAL('Y', (*it).first);
//	DOUBLES_EQUAL(20.458, (*it).second, 0.001);
//	
//}

//TEST(PStringTestGroup, split)
//{
//	PString str("login, pass1, pass2");
//	vector<string> vec=str.split(',');
//	
//	LONGS_EQUAL(3, vec.size());
//	STRCMP_EQUAL("login", vec.at(0).c_str());
//	STRCMP_EQUAL(" pass1", vec.at(1).c_str());
//	STRCMP_EQUAL(" pass2", vec.at(2).c_str());
//	
//	str="login";
//	vec=str.split(',');
//	LONGS_EQUAL(1, vec.size());
//	STRCMP_EQUAL("login", vec.at(0).c_str());
//	
//	str="login,,pass2";
//	vec=str.split(',');
//	LONGS_EQUAL(2, vec.size());
//	STRCMP_EQUAL("login", vec.at(0).c_str());
//	STRCMP_EQUAL("pass2", vec.at(1).c_str());
//	
//	vec=str.split(',',PString::KeepEmptyParts);
//	LONGS_EQUAL(3, vec.size());
//	STRCMP_EQUAL("login", vec.at(0).c_str());
//	STRCMP_EQUAL("", vec.at(1).c_str());
//	STRCMP_EQUAL("pass2", vec.at(2).c_str());
//}



//TEST(PStringTestGroup, splitWithClamps)
//{
//        PString str(" \"pio\", \"stasiek\"");

//				vector<string> vec=str.splitWithClamps(',', '"');
//				LONGS_EQUAL(2, vec.size());
//				STRCMP_EQUAL("pio", vec.at(0).c_str());
//				STRCMP_EQUAL("stasiek", vec.at(1).c_str());
//	
//				vec=str.splitWithClamps('.', '"');
//				LONGS_EQUAL(1, vec.size());
//				STRCMP_EQUAL("pio", vec.at(0).c_str());

//				str=",'stasiek'";
//        vec=str.splitWithClamps(',', '\'');
//				LONGS_EQUAL(1, vec.size());
//				STRCMP_EQUAL("stasiek", vec.at(0).c_str());

//        str="ANET \"pio\", \"stasiek\"";
//				vec=str.splitWithClamps(',', '"');
//				LONGS_EQUAL(2, vec.size());
//				STRCMP_EQUAL("pio", vec.at(0).c_str());
//				STRCMP_EQUAL("stasiek", vec.at(1).c_str());

//        str="\"\", \"\"";
//				vec=str.splitWithClamps(',', '"');
//				LONGS_EQUAL(2, vec.size());
//				STRCMP_EQUAL("", vec.at(0).c_str());
//				STRCMP_EQUAL("", vec.at(1).c_str());
//}
