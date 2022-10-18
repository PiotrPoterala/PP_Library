#include "CppUTest/TestHarness.h"

#include "pp_rtos_drive_algorithms_mock.h"
#include "stdio.h"

TEST_GROUP(defODriveAlgorithmsTestGroup)
{
	
	//defODriveAlgorithmsShdPtr motorsAlgorithms;
	
  void setup() {
//		motorsAlgorithms=make_shared<defORTOSdriveAlgorithmsMock>();

	}
	
  void teardown() {

	}
};


//TEST(defODriveAlgorithmsTestGroup, getFrequencykResponsibleForDriveSpeedTest)
//{

//	LONGS_EQUAL(1000, defODriveAlgorithms::getFrequencykResponsibleForDriveSpeed(2000, 2000, 2, 2500, 2500));
//	LONGS_EQUAL(500, defODriveAlgorithms::getFrequencykResponsibleForDriveSpeed(2000, 2000, 2, 2500, 5000));
//}


//TEST(defODriveAlgorithmsTestGroup, getClockDividerResponsibleForDriveSpeedTest)
//{

//	LONGS_EQUAL(10, defODriveAlgorithms::getClockDividerResponsibleForDriveSpeed(2000, 2000, 2, 2500,  10000, 2500));
//}

//TEST(defOParamTestGroup, comparingParamsValueWithParamsMap)
//{
//	PParamMap paramToComp={PParamPair {'f', make_shared<defOParam>("velocity", 2500, 1, 2500)}, PParamPair {'a', make_shared<defOParam>("acceleration", 2, 1, 30)}, PParamPair {'T', make_shared<defOParam>("impulse", 4750, 1000, 9000)}};
//	CHECK(list->comparingParamsValue(paramToComp));
//}

//TEST(defOParamTestGroup, comparingParamsValueWithTooBigParamsMap)
//{
//	PParamMap paramToComp={PParamPair {'f', make_shared<defOParam>("velocity", 2500, 1, 2500)}, PParamPair {'a', make_shared<defOParam>("acceleration", 2, 1, 30)}, PParamPair {'T', make_shared<defOParam>("impulse", 4750, 1000, 9000)}, PParamPair {'d', make_shared<defOParam>("acceleration", 2, 1, 30)}};
//	CHECK_FALSE(list->comparingParamsValue(paramToComp));
//}

//TEST(defOParamTestGroup, comparingParamsValueWithDifferentValuesParamsMap)
//{
//	PParamMap paramToComp={PParamPair {'f', make_shared<defOParam>("velocity", 2500, 1, 2500)}, PParamPair {'a', make_shared<defOParam>("acceleration", 25, 1, 30)}, PParamPair {'T', make_shared<defOParam>("impulse", 4750, 1000, 9000)}};
//	CHECK_FALSE(list->comparingParamsValue(paramToComp));
//}

//TEST(defOParamTestGroup, comparingParamsValueWithIntMap)
//{
//	map<char, int> paramToComp={pair<char, int>{'f', 2500}, pair<char, int>{'a', 2}, pair<char, int>{'T', 4750}};
//	CHECK(list->comparingParamsValue(paramToComp));
//}

//TEST(defOParamTestGroup, comparingParamsValueWithTooBigIntMap)
//{
//	map<char, int> paramToComp={pair<char, int>{'f', 2500}, pair<char, int>{'a', 2}, pair<char, int>{'T', 4750}, pair<char, int>{'d', 25}};
//	CHECK_FALSE(list->comparingParamsValue(paramToComp));
//}

//TEST(defOParamTestGroup, comparingParamsValueWithDifferentValuesIntMap)
//{
//	map<char, int> paramToComp={pair<char, int>{'f', 2500}, pair<char, int>{'a', 25}, pair<char, int>{'T', 4750}};
//	CHECK_FALSE(list->comparingParamsValue(paramToComp));
//}

//TEST(defOParamTestGroup, setParamsBasedString)
//{

//		list->setParamsBasedString("a6.87 f1200 d5 T5.25");
//		LONGS_EQUAL(1200, list->getParamValue('f'));
//		LONGS_EQUAL(6, list->getParamValue('a'));
//		LONGS_EQUAL(5250, list->getParamValue('T'));
//	
//}