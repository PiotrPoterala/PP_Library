#include "CppUTest/TestHarness.h"


#include "pp_point.h"
#include "stdio.h"

#define LIST_MAX_SIZE	10

TEST_GROUP(PPointTestGroup)
{
	
	PPpoint<int> list{};

  void setup() {

		list.axes.insert(pair<char, int>('X', 20));
		list.axes.insert(pair<char, int>('Y', 30));
		list.axes.insert(pair<char, int>('Z', 40));
		

	}
	
  void teardown() {
		
		list.axes.clear();
	}
};


TEST(PPointTestGroup, comparePointsTest)
{

		PPpoint<int> listToComp{};

		listToComp.axes.insert(pair<char, int>('X', 20));
		listToComp.axes.insert(pair<char, int>('Y', 30));
		listToComp.axes.insert(pair<char, int>('Z', 40));
		listToComp.axes.insert(pair<char, int>('A', 50));
	
		CHECK_TRUE(list.compare(listToComp));
}

TEST(PPointTestGroup, exacComparePointsTest)
{

		PPpoint<int> listToComp{};

		listToComp.axes.insert(pair<char, int>('X', 20));
		listToComp.axes.insert(pair<char, int>('Y', 30));
		listToComp.axes.insert(pair<char, int>('Z', 40));
	
		CHECK_TRUE(list==listToComp);
			
		listToComp.axes.insert(pair<char, int>('A', 50));
			
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

		listToAdd.axes.insert(pair<char, int>('X', 25));
		listToAdd.axes.insert(pair<char, int>('Y', 35));
	
		PPpoint<int> result=list+listToAdd;
			
		LONGS_EQUAL(45, result.axes.find('X')->second);
		LONGS_EQUAL(65, result.axes.find('Y')->second);
		LONGS_EQUAL(40, result.axes.find('Z')->second);
			
		list+=listToAdd;
			
		LONGS_EQUAL(45, list.axes.find('X')->second);
		LONGS_EQUAL(65, list.axes.find('Y')->second);
		LONGS_EQUAL(40, list.axes.find('Z')->second);
			
}

TEST(PPointTestGroup, subtractPointsTest)
{
	
		PPpoint<int> listToSubtract{};

		listToSubtract.axes.insert(pair<char, int>('X', 5));
		listToSubtract.axes.insert(pair<char, int>('Y', 15));
	
			
		list-=listToSubtract;
			
		LONGS_EQUAL(15, list.axes.find('X')->second);
		LONGS_EQUAL(15, list.axes.find('Y')->second);
		LONGS_EQUAL(40, list.axes.find('Z')->second);
}


TEST(PPointTestGroup, setAxesBasedStringTest)
{
	
	PString str{"X25 Y56 Z48"};
	
	list.setAxesBasedString(str);
	
	LONGS_EQUAL(25, list.axes.find('X')->second);
	LONGS_EQUAL(56, list.axes.find('Y')->second);
	LONGS_EQUAL(48, list.axes.find('Z')->second);
	
}