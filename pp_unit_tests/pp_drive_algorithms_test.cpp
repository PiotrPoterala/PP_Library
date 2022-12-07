#include "CppUTest/TestHarness.h"

#include "pp_motorslist.h"
#include "pp_control_coordinate_decorator.h"
#include "pp_stepper_motor_2clock_driver.h"
#include "pp_path_drive_algorithms.h"
#include "pp_fast_drive_algorithms.h"
#include "pp_point.h"
#include "stdio.h"

TEST_GROUP(defODriveAlgorithmsTestGroup)
{
	
	PMotorsListShdPtr motorsList=make_shared<PMotorsList>();
	defOParamListShdPtr phyCoord=make_shared<defOParamList>();
	defOParamListShdPtr baseCoord=make_shared<defOParamList>();
	defOParamListShdPtr workParams=make_shared<defOParamList>();
	defOParamListShdPtr boltParams;
	PParamPair accelerationMMperSEC2;
	
	PPdriveAlgorithmsContextPtr algContext;
//	defODriveAlgorithmsShdPtr algorithm;
	
  void setup() {
		phyCoord->insert(PParamPair('X', make_shared<defOParam>("X", 100000, 0, 999000, 5, 3)));
		phyCoord->insert(PParamPair('Y', make_shared<defOParam>("Y", 100000, 0, 999000, 5, 3)));
		
		baseCoord->insert(PParamPair('X', make_shared<defOParam>("X", 100000, -999000, 999000, 5, 3)));
		baseCoord->insert(PParamPair('Y', make_shared<defOParam>("Y", 100000, -999000, 999000, 5, 3)));
		
		boltParams=baseCoord->clone();
		boltParams->setParamsValue(0);
		
		workParams->insert(PParamPair('f', make_shared<defOParam>("velocity", 2500, 1, 2500)));
		
		accelerationMMperSEC2=PParamPair('a', make_shared<defOParam>("acc", 2000, 1000, 30000, 100, 3));
		
		motorsList->motors.insert(PMotorsPair('X', make_shared<defOControlCoordinateDecorator>
																	(make_shared<defOStepperMotor2clockDriver>(accelerationMMperSEC2.second, workParams->getParam('f').front(), phyCoord->getParam('X').front(), baseCoord->getParam('X').front(), FULL_STEP),
																		boltParams->getParam('X').front())));		
		motorsList->motors.insert(PMotorsPair('Y', make_shared<defOControlCoordinateDecorator>
																	(make_shared<defOStepperMotor2clockDriver>(accelerationMMperSEC2.second, workParams->getParam('f').front(), phyCoord->getParam('Y').front(), baseCoord->getParam('Y').front(), FULL_STEP),
																		boltParams->getParam('Y').front())));		
	//	algorithm=make_shared<defOFastDriveAlgorithms>(motorsList);
		algContext=make_unique<PPdriveAlgorithmsContext>(make_shared<defOPathDriveAlgorithms>(motorsList));
	}
	
  void teardown() {
		motorsList->motors.clear();
		phyCoord->clear();
		baseCoord->clear();
		workParams->clear();
	}
};


TEST(defODriveAlgorithmsTestGroup, driveAheadForValueTest)
{
	PPpoint<int> endPoint{};
		
	endPoint.addAx('X', 200);
	endPoint.addAx('Y', 300);
	
	
	algContext->setAlgorithm(make_shared<defOFastDriveAlgorithms>(motorsList));
	algContext->driveForValue(endPoint);
	
	LONGS_EQUAL(100200, phyCoord->getParamValue('X'));
	LONGS_EQUAL(100300, phyCoord->getParamValue('Y'));
}

TEST(defODriveAlgorithmsTestGroup, driveBackForValueTest)
{
	PPpoint<int> endPoint{};
		
	endPoint.addAx('X', -200);
	endPoint.addAx('Y', -300);
	
	
	algContext->setAlgorithm(make_shared<defOFastDriveAlgorithms>(motorsList));
	algContext->driveForValue(endPoint);
	
	LONGS_EQUAL(99800, phyCoord->getParamValue('X'));
	LONGS_EQUAL(99700, phyCoord->getParamValue('Y'));
}

TEST(defODriveAlgorithmsTestGroup, driveAheadForValueTest2)
{
	PPpoint<int> endPoint{};
		
	endPoint.addAx('X', 203);
	endPoint.addAx('Y', 303);
	
	
	algContext->setAlgorithm(make_shared<defOFastDriveAlgorithms>(motorsList));
	algContext->driveForValue(endPoint);
	
	LONGS_EQUAL(100205, phyCoord->getParamValue('X'));
	LONGS_EQUAL(100305, phyCoord->getParamValue('Y'));
}

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