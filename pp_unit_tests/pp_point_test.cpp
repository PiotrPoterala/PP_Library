#include "CppUTest/TestHarness.h"


#include "pp_point.h"
#include "stdio.h"

#define LIST_MAX_SIZE	10

TEST_GROUP(PPointTestGroup)
{
	
	PPpoint<int> list{};

  void setup() {

		list.addAx('X', 20);
		list.addAx('Y', 30);
		list.addAx('Z', 40);
		

	}
	
  void teardown() {
		
		list.clear();
	}
};


TEST(PPointTestGroup, comparePointsTest)
{

		PPpoint<int> listToComp{};

		listToComp.addAx('X', 20);
		listToComp.addAx('Y', 30);
		listToComp.addAx('Z', 40);
		listToComp.addAx('A', 50);
	
		CHECK_TRUE(list.compare(listToComp));
}

TEST(PPointTestGroup, exacComparePointsTest)
{

		PPpoint<int> listToComp{};

		listToComp.addAx('X', 20);
		listToComp.addAx('Y', 30);
		listToComp.addAx('Z', 40);
	
		CHECK_TRUE(list==listToComp);
			
		listToComp.addAx('A', 50);
			
		CHECK_FALSE(list==listToComp);
}

TEST(PPointTestGroup, comparePointWithMapTest)
{

		map<char, int> listToComp{};

		listToComp.insert(pair<char, int>('X', 20));
		listToComp.insert(pair<char, int>('Y', 30));
		listToComp.insert(pair<char, int>('Z', 40));
		listToComp.insert(pair<char, int>('A', 50));
	
		CHECK_TRUE(list.compare(listToComp));
}

TEST(PPointTestGroup, exacComparePointWithMapTest)
{

		map<char, int> listToComp{};

		listToComp.insert(pair<char, int>('X', 20));
		listToComp.insert(pair<char, int>('Y', 30));
		listToComp.insert(pair<char, int>('Z', 40));
	
		CHECK_TRUE(list==listToComp);
			
		listToComp.insert(pair<char, int>('A', 50));
			
		CHECK_FALSE(list==listToComp);
}


TEST(PPointTestGroup, addPointsTest)
{
	
		PPpoint<int> listToAdd{};

		listToAdd.addAx('X', 25);
		listToAdd.addAx('Y', 35);
	
		PPpoint<int> result=list+listToAdd;
			
		LONGS_EQUAL(45, result.getAxValue('X'));
		LONGS_EQUAL(65, result.getAxValue('Y'));
		LONGS_EQUAL(40, result.getAxValue('Z'));
			
		list+=listToAdd;
			
		LONGS_EQUAL(45, list.getAxValue('X'));
		LONGS_EQUAL(65, list.getAxValue('Y'));
		LONGS_EQUAL(40, list.getAxValue('Z'));
			
}

TEST(PPointTestGroup, addPointsWithLimitsTest)
{
	
		PPpoint<int> listToAdd{};

		listToAdd.addAx('X', 90);
		listToAdd.addAx('Y', -80);
			
		list.addLimit('X', tuple<int, int, int, int>{100, 0, 1, 0});
		list.addLimit('Y', tuple<int, int, int, int>{100, 0, 1, 0});
			
	
		PPpoint<int> result=list+listToAdd;
			
		LONGS_EQUAL(100, result.getAxValue('X'));
		LONGS_EQUAL(0, result.getAxValue('Y'));
		
		result+=listToAdd;
		
		LONGS_EQUAL(100, result.getAxValue('X'));
		LONGS_EQUAL(0, result.getAxValue('Y'));
			
		list+=listToAdd;
			
		LONGS_EQUAL(100, list.getAxValue('X'));
		LONGS_EQUAL(0, list.getAxValue('Y'));
			
}

TEST(PPointTestGroup, subtractPointsTest)
{
	
		PPpoint<int> listToSubtract{};

		listToSubtract.addAx('X', 5);
		listToSubtract.addAx('Y', 15);
	
			
		list-=listToSubtract;
			
		LONGS_EQUAL(15, list.getAxValue('X'));
		LONGS_EQUAL(15, list.getAxValue('Y'));
		LONGS_EQUAL(40, list.getAxValue('Z'));
}


TEST(PPointTestGroup, setAxesBasedStringTest)
{
	
	PString str{"X25 Y56 Z48"};
	
	list.setAxesBasedString(str);
	
	LONGS_EQUAL(25, list.getAxValue('X'));
	LONGS_EQUAL(56, list.getAxValue('Y'));
	LONGS_EQUAL(48, list.getAxValue('Z'));
	
	list.addLimit('X', tuple<int, int, int, int>{100000, 0, 5, 3});
	list.addLimit('Y', tuple<int, int, int, int>{100000, 0, 5, 3});
	list.addLimit('Z', tuple<int, int, int, int>{100000, 0, 5, 3});
	
	str="X25.456 Y56.678 Z48.655";
	
	list.setAxesBasedString(str);
	
	LONGS_EQUAL(25455, list.getAxValue('X'));
	LONGS_EQUAL(56680, list.getAxValue('Y'));
	LONGS_EQUAL(48655, list.getAxValue('Z'));
	
}


TEST(PPointTestGroup, setAxValueWithLimitsTest)
{
	
	list.addLimit('X', tuple<int, int, int, int>{30, 10, 1, 0});
	
	list.setAxValue('X', 25);
	LONGS_EQUAL(25, list.getAxValue('X'));
	
	list.setAxValue('X', 35);
	LONGS_EQUAL(30, list.getAxValue('X'));
	
}




