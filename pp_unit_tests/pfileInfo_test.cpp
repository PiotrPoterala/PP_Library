#include "CppUTest/TestHarness.h"

#include "pp_file_info.h"
#include "pp_file.h"
#include "stdio.h"


//TEST_GROUP(PFileInfoTestGroup)
//{
//	PFileInfo fileInfo;
//	PFile file;
//	
//  void setup() {
//		PFileConstruct(&file, "1:/Gc/edf/test.txt");
//		PFileInfoConstruct(&fileInfo);
//		fileInfo.setFile(&fileInfo.data, &file);
//	}
//  void teardown() {}
//};


//TEST(PFileInfoTestGroup, createPFileInfoTest)
//{
//	STRCMP_EQUAL("1:/", fileInfo.data.volume);
//	STRCMP_EQUAL("Gc/edf/test.txt", fileInfo.data.path);
//}

//TEST(PFileInfoTestGroup, setFileTest)
//{
//	PFile file2;
//	PFileConstruct(&file2, "1:/Gc/test.txt");
//	fileInfo.setFile(&fileInfo.data, &file2);
//	STRCMP_EQUAL("1:/", fileInfo.data.volume);
//	STRCMP_EQUAL("Gc/test.txt", fileInfo.data.path);
//	
//}

//TEST(PFileInfoTestGroup, getAbsoluteFilePathTest)
//{
//	char absPath[ABS_PATH_LENGTH];
//	fileInfo.absoluteFilePath(&fileInfo.data, absPath, ABS_PATH_LENGTH);
//	
//	STRCMP_EQUAL("1:/Gc/edf/test.txt", absPath);
//}

//TEST(PFileInfoTestGroup, getFileNameTest)
//{
//	char fileName[ABS_PATH_LENGTH];
//	fileInfo.fileName(&fileInfo.data, fileName, ABS_PATH_LENGTH);
//	
//	STRCMP_EQUAL("test.txt", fileName);
//}

//TEST(PFileInfoTestGroup, isFileTest)
//{
//	CHECK(fileInfo.isFile(&fileInfo.data));
//	fileInfo.setPath(&fileInfo.data, "1:/Gc/test");
//	CHECK_FALSE(fileInfo.isFile(&fileInfo.data));
//}

//TEST(PFileInfoTestGroup, isDirTest)
//{
//	CHECK_FALSE(fileInfo.isDir(&fileInfo.data));
//	fileInfo.setPath(&fileInfo.data, "1:/Gc/test");
//	CHECK(fileInfo.isDir(&fileInfo.data));
//}

//TEST(PFileInfoTestGroup, lastModifiedDateTest)
//{
//	char dateStr[60];
//	fileInfo.lastModifiedDate(&fileInfo.data, dateStr);
//	STRCMP_EQUAL("2022-04-10", dateStr);
//}

//TEST(PFileInfoTestGroup, lastModifiedTimeTest)
//{
//	char timeStr[60];
//	fileInfo.lastModifiedTime(&fileInfo.data, timeStr);
//	STRCMP_EQUAL("15:45:15", timeStr);
//}