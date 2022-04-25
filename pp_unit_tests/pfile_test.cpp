#include "CppUTest/TestHarness.h"

//#include "pp_file.h"
//#include "stdio.h"


//TEST_GROUP(PFileTestGroup)
//{
//	PIOdeviceShrPtr file;
//	
//  void setup() {
//		file=make_shared<PFile>("1:/Gc/test.txt");
//	}
//	
//  void teardown() {}
//};


//TEST(PFileTestGroup, createPFileTest_1)
//{
//	STRCMP_EQUAL("1:/", file.data.volume);
//	STRCMP_EQUAL("Gc/test.txt", file.data.path);
//}

//TEST(PFileTestGroup, createPFileTest_2)
//{
//	PFileConstruct(&file, "\0");
//	STRCMP_EQUAL("\0", file.data.volume);
//	STRCMP_EQUAL("\0", file.data.path);
//}

//TEST(PFileTestGroup, createPFileTest_3)
//{
//	PFileConstruct(&file, "1:/");
//	STRCMP_EQUAL("1:/", file.data.volume);
//	STRCMP_EQUAL("\0", file.data.path);
//}

//TEST(PFileTestGroup, getAbsolutePathTest)
//{
//	char absPath[ABS_PATH_LENGTH];
//	file.absolutePath(&file.data, absPath, ABS_PATH_LENGTH);
//	
//	STRCMP_EQUAL("1:/Gc/test.txt", absPath);
//}
