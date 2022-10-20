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




//TEST(PPointTestGroup, setPointByEmptyPointTest)
//{
//	PPoint listToCopy;
//	SValue tabToCopy[LIST_MAX_SIZE];
//	PPointConstruct(&listToCopy, tabToCopy, LIST_MAX_SIZE);
//	
//	list.setPoint(&list.data, &listToCopy.data);
//	LONGS_EQUAL(0, list.data.size);
//	BYTES_EQUAL('\0', list.data.axes[0].acronim);
//	BYTES_EQUAL('\0', list.data.axes[1].acronim);
//	BYTES_EQUAL('\0', list.data.axes[2].acronim);
//	
//	PPoint copyList;
//	SValue copyTab[LIST_MAX_SIZE];
//	PPointConstruct(&copyList, copyTab, LIST_MAX_SIZE);
//	
//	copyList.setPoint(&copyList.data, &listToCopy.data);
//	LONGS_EQUAL(0, copyList.data.size);
//	BYTES_EQUAL('\0', copyList.data.axes[0].acronim);
//	BYTES_EQUAL('\0', copyList.data.axes[1].acronim);
//	BYTES_EQUAL('\0', copyList.data.axes[2].acronim);
//	
//}

//TEST(PPointTestGroup, setPointByValTabTest)
//{

//	SValue tabToSet[5]={{'X', 20},{'Y', 30},{'Z', 40},{'A', 50}};
//	
//	list.setPointByValTab(&list.data, tabToSet, 5);
//	LONGS_EQUAL(4, list.data.size);
//	LONGS_EQUAL(40, list.getAx(&list.data, 'Z').value);

//}


//TEST(PPointTestGroup, comparePointsTest)
//{
//	
//		SValue tabToCompare[LIST_MAX_SIZE];
//		PPoint listToCompare;
//		PPointConstruct(&listToCompare, tabToCompare, LIST_MAX_SIZE);
//	
//		{SValue data={'X', 20};
//		listToCompare.insert(&listToCompare.data, &data);}
//		{SValue data={'Y', 30};
//		listToCompare.insert(&listToCompare.data, &data);}
//		{SValue data={'Z', 40};
//		listToCompare.insert(&listToCompare.data, &data);}
//	
//	
//	CHECK(list.exacComparePoints(&list.data, &listToCompare.data));
//}

//TEST(PPointTestGroup, comparePointWithValTabTest)
//{
//	SValue tabToComp[5]={{'X', 20},{'Y', 30},{'Z', 40}};
//	

//	CHECK(list.comparePointWithValTab(&list.data, tabToComp, 5));
//	CHECK(list.exacComparePointWithValTab(&list.data, tabToComp, 5));
//}

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
	
			
		LONGS_EQUAL(3, list.axes.size());
		LONGS_EQUAL(3, listToComp.axes.size());
		CHECK_TRUE(list==listToComp);
			
		listToComp.axes.insert(pair<char, int>('A', 50));
			
		CHECK_FALSE(list==listToComp);
}

//TEST(PPointTestGroup, comparePointWithValTabTest3)
//{
//	SValue tabToComp[5]={{'X', 25},{'Y', 30},{'Z', 40},{'A', 40}};
//	

//	CHECK_FALSE(list.comparePointWithValTab(&list.data, tabToComp, 5));
//	CHECK_FALSE(list.exacComparePointWithValTab(&list.data, tabToComp, 5));
//}



//TEST(PPointTestGroup, addPointsTest)
//{
//	
//		SValue tabToAdd[LIST_MAX_SIZE];
//		PPoint listToAdd;
//		PPointConstruct(&listToAdd, tabToAdd, LIST_MAX_SIZE);
//	
//		{SValue data={'X', 25};
//		listToAdd.insert(&listToAdd.data, &data);}
//		{SValue data={'Y', 35};
//		listToAdd.insert(&listToAdd.data, &data);}
//	
//		list.addPoints(&list.data, &listToAdd.data);
//		
//		LONGS_EQUAL(45, list.getAxValue(&list.data, 'X'));
//		LONGS_EQUAL(65, list.getAxValue(&list.data, 'Y'));
//		LONGS_EQUAL(40, list.getAxValue(&list.data, 'Z'));
//}

//TEST(PPointTestGroup, subtractPointsTest)
//{
//	
//		SValue tabToAdd[LIST_MAX_SIZE];
//		PPoint listToAdd;
//		PPointConstruct(&listToAdd, tabToAdd, LIST_MAX_SIZE);
//	
//		{SValue data={'X', 5};
//		listToAdd.insert(&listToAdd.data, &data);}
//		{SValue data={'Y', 5};
//		listToAdd.insert(&listToAdd.data, &data);}
//	
//		list.subtractPoints(&list.data, &listToAdd.data);
//		
//		LONGS_EQUAL(15, list.getAxValue(&list.data, 'X'));
//		LONGS_EQUAL(25, list.getAxValue(&list.data, 'Y'));
//		LONGS_EQUAL(40, list.getAxValue(&list.data, 'Z'));
//}
