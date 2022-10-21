#include "CppUTest/TestHarness.h"


#include "pp_motorslist.h"
#include "pp_stepper_motor_2clock_driver.h"
#include "stdio.h"

TEST_GROUP(PMotorsListTestGroup)
{
	
	PMotorsList list{};
		
	PParamPair accelerationMMperSEC2;
	PParamPair feedMMperSEC;
	PParamPair coordPhyX_MM;
	PParamPair coordPhyY_MM;
		
	PParamPair coordBaseX_MM;
	PParamPair coordBaseY_MM;

  void setup() {
		
		accelerationMMperSEC2=PParamPair('a', make_shared<defOParam>("acc", 2000, 1000, 30000, 100, 3));
		feedMMperSEC=PParamPair('f', make_shared<defOParam>("feed", 5, 1, 2500));
		
		coordPhyX_MM=PParamPair('X', make_shared<defOParam>("X", 1235, 0, 999000, 5, 3));
		coordPhyY_MM=PParamPair('Y', make_shared<defOParam>("Y", 12350, 0, 999000, 5, 3));
		
		coordBaseX_MM=PParamPair('X', make_shared<defOParam>("X", 100000, -999000, 999000, 5, 3));
		coordBaseY_MM=PParamPair('Y', make_shared<defOParam>("Y", 100000, -999000, 999000, 5, 3));

		list.motors.insert(PMotorsPair('X', make_shared<defOStepperMotor2clockDriver>
																					(accelerationMMperSEC2.second, feedMMperSEC.second, 
																						coordPhyX_MM.second, coordBaseX_MM.second, MICRO_STEP)));	
		
		list.motors.insert(PMotorsPair('Y', make_shared<defOStepperMotor2clockDriver>
																					(accelerationMMperSEC2.second, feedMMperSEC.second, 
																						coordPhyY_MM.second, coordBaseY_MM.second, MICRO_STEP)));	
	}
	
  void teardown() {
		
		list.motors.clear();
	}
};


TEST(PMotorsListTestGroup, getPhyCoordValuesTest)
{

		auto getList=list.getPhyCoordValues();

		LONGS_EQUAL(1235, getList.find('X')->second);
		LONGS_EQUAL(12350, getList.find('Y')->second);
}

//TEST(PPointTestGroup, exacComparePointsTest)
//{

//		PPpoint<int> listToComp{};

//		listToComp.axes.insert(pair<char, int>('X', 20));
//		listToComp.axes.insert(pair<char, int>('Y', 30));
//		listToComp.axes.insert(pair<char, int>('Z', 40));
//	
//		CHECK_TRUE(list==listToComp);
//			
//		listToComp.axes.insert(pair<char, int>('A', 50));
//			
//		CHECK_FALSE(list==listToComp);
//}

//TEST(PPointTestGroup, comparePointWithMapTest)
//{

//		map<char, int> listToComp{};

//		listToComp.insert(pair<char, int>('X', 20));
//		listToComp.insert(pair<char, int>('Y', 30));
//		listToComp.insert(pair<char, int>('Z', 40));
//		listToComp.insert(pair<char, int>('A', 50));
//	
//		CHECK_TRUE(list.compare(listToComp));
//}

//TEST(PPointTestGroup, exacComparePointWithMapTest)
//{

//		map<char, int> listToComp{};

//		listToComp.insert(pair<char, int>('X', 20));
//		listToComp.insert(pair<char, int>('Y', 30));
//		listToComp.insert(pair<char, int>('Z', 40));
//	
//		CHECK_TRUE(list==listToComp);
//			
//		listToComp.insert(pair<char, int>('A', 50));
//			
//		CHECK_FALSE(list==listToComp);
//}


//TEST(PPointTestGroup, addPointsTest)
//{
//	
//		PPpoint<int> listToAdd{};

//		listToAdd.axes.insert(pair<char, int>('X', 25));
//		listToAdd.axes.insert(pair<char, int>('Y', 35));
//	
//		PPpoint<int> result=list+listToAdd;
//			
//		LONGS_EQUAL(45, result.axes.find('X')->second);
//		LONGS_EQUAL(65, result.axes.find('Y')->second);
//		LONGS_EQUAL(40, result.axes.find('Z')->second);
//			
//		list+=listToAdd;
//			
//		LONGS_EQUAL(45, list.axes.find('X')->second);
//		LONGS_EQUAL(65, list.axes.find('Y')->second);
//		LONGS_EQUAL(40, list.axes.find('Z')->second);
//			
//}

//TEST(PPointTestGroup, subtractPointsTest)
//{
//	
//		PPpoint<int> listToSubtract{};

//		listToSubtract.axes.insert(pair<char, int>('X', 5));
//		listToSubtract.axes.insert(pair<char, int>('Y', 15));
//	
//			
//		list-=listToSubtract;
//			
//		LONGS_EQUAL(15, list.axes.find('X')->second);
//		LONGS_EQUAL(15, list.axes.find('Y')->second);
//		LONGS_EQUAL(40, list.axes.find('Z')->second);
//}


//TEST(PPointTestGroup, setAxesBasedStringTest)
//{
//	
//	PString str{"X25 Y56 Z48"};
//	
//	list.setAxesBasedString(str);
//	
//	LONGS_EQUAL(25, list.axes.find('X')->second);
//	LONGS_EQUAL(56, list.axes.find('Y')->second);
//	LONGS_EQUAL(48, list.axes.find('Z')->second);
//	
//}