#include "CppUTest/TestHarness.h"

#include "pp_dir_mock.h"
#include "stdio.h"

TEST_GROUP(PDirTestGroup)
{
	PDirPtr dir;
	
  void setup() {
		dir=make_unique<PDirMock>("1:/data/Gc/");
	}
  void teardown() {}
};

TEST(PDirTestGroup, absoluteFilePathTest)
{
	STRCMP_EQUAL("1:/data/Gc/test", dir   ->absoluteFilePath("test").c_str());
}


TEST(PDirTestGroup, absolutePathTest)
{
	STRCMP_EQUAL("1:/data/Gc", dir->absolutePath().c_str());
}

TEST(PDirTestGroup, dirNameTest)
{
	STRCMP_EQUAL("Gc", dir->dirName().c_str());
}


//TEST(PDirTestGroup, createPDirTest_2)
//{
//	PDirConstruct(&dir,"\0");
//	STRCMP_EQUAL("\0", dir.data.volume);
//	STRCMP_EQUAL("\0", dir.data.dirPath);
//}

//TEST(PDirTestGroup, createPDirTest_3)
//{
//	PDirConstruct(&dir,"1:/");
//	STRCMP_EQUAL("1:/", dir.data.volume);
//	STRCMP_EQUAL("\0", dir.data.dirPath);
//}


//TEST(PDirTestGroup, getAbsolutePathTest)
//{
//	PDirConstruct(&dir, "1:/data/Gc/");
//	char absPath[ABS_PATH_LENGTH];
//	dir.absolutePath(&dir.data, absPath, ABS_PATH_LENGTH);
//	
//	STRCMP_EQUAL("1:/data/Gc", absPath);
//}

//TEST(PDirTestGroup, getAbsoluteFilePathTest)
//{
//	char absPath[ABS_PATH_LENGTH];
//	dir.absoluteFilePath(&dir.data, "test.txt", absPath, ABS_PATH_LENGTH);
//	
//	STRCMP_EQUAL("1:/data/Gc/test.txt", absPath);
//}

//TEST(PDirTestGroup, getDirNameTest)
//{
//	char dirName[ABS_PATH_LENGTH];
//	dir.dirName(&dir.data, dirName, ABS_PATH_LENGTH);
//	
//	STRCMP_EQUAL("Gc", dirName);
//}

//TEST(PDirTestGroup, cdTest)
//{
//	CHECK(dir.cd(&dir.data, "test"));
//	
//	STRCMP_EQUAL("1:/", dir.data.volume);
//	STRCMP_EQUAL("data/Gc/test", dir.data.dirPath);
//}

//TEST(PDirTestGroup, cdUpTest)
//{
//	CHECK(dir.cdUp(&dir.data));
//	
//	STRCMP_EQUAL("1:/", dir.data.volume);
//	STRCMP_EQUAL("data", dir.data.dirPath);
//}

//TEST(PDirTestGroup, getEntryListTest)
//{
//	PConstCharList list;
//	char tab[20][PLIST_STR_LENGTH];
//	PConstCharListConstruct(&list, tab, 20);
//	
//	dir.entryList(&dir.data, NoFilter, &list);
//	
//	STRCMP_EQUAL("file_10", list.data.names[9]);
//}