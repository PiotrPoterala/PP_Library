#include "CppUTest/TestHarness.h"

#include "pp_math_ext.h"
#include "stdio.h"


TEST_GROUP(PPmathExtTestGroup)
{
	
  void setup() {}
  void teardown() {}
};


TEST(PPmathExtTestGroup, trimTest)
{
	int data=25;
	int upperLimit=30;
	int lowerLimit=20;
	
	LONGS_EQUAL(25, trim_pp(data, upperLimit, lowerLimit));
	
	data=15;
	LONGS_EQUAL(20, trim_pp(data, upperLimit, lowerLimit));
		
}

TEST(PPmathExtTestGroup, trimAccIntTest)
{
	int data=25001;
	int upperLimit=30000;
	int lowerLimit=20000;
	
	LONGS_EQUAL(25000, trimAcc_pp(data, upperLimit, lowerLimit, 5));
	
	data=25004;
	LONGS_EQUAL(25005, trimAcc_pp(data, upperLimit, lowerLimit, 5));
		
}

TEST(PPmathExtTestGroup, trimAccDoubleTest)
{
	double data=25.001;
	double upperLimit=30;
	double lowerLimit=20;
	
	DOUBLES_EQUAL(25, trimAcc_pp(data, upperLimit, lowerLimit, 0.005), 0.0001);
	
	data=25.004;
	DOUBLES_EQUAL(25.005, trimAcc_pp(data, upperLimit, lowerLimit, 0.005), 0.0001);
		
}