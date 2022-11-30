#include "CppUTest/TestHarness.h"

#include "pp_select_list.h"
#include "stdio.h"

TEST_GROUP(PSelectListTestGroup)
{
	
	vector<string> typeOfProgNames={"EDF", "Gcode", "GCodeDrill"};
	
  void setup() {}
  void teardown() {}
};


TEST(PSelectListTestGroup, initializeTest)
{
	
	PSelectList selList{typeOfProgNames};
	
	LONGS_EQUAL(3, selList.count());
	
	STRCMP_EQUAL("EDF", selList.itemText(0).c_str());

}


TEST(PSelectListTestGroup, setIndexTest)
{
	PSelectList selList{typeOfProgNames};
	
	selList.setCurrentIndex(2);
	
	STRCMP_EQUAL("GCodeDrill", selList.currentText().c_str());
}
