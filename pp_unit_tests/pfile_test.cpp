#include "CppUTest/TestHarness.h"

#include "pp_file_string_mock.h"
#include "stdio.h"


TEST_GROUP(PFileTestGroup)
{
	PFileShrPtr file;
	
  void setup() {
		file=make_shared<PFileStringMock>("C:/Gc_test/test.txt");
		file->open(PIOdevice::WriteOnly);
		file->write("G56\nG00 X0 Y0 Z0 A0\nG00 Z-2\nG00 Z2\n");
		file->close();
	}
	
  void teardown() {}
};



TEST(PFileTestGroup, getAbsolutePathTest)
{
	
	STRCMP_EQUAL("C:/Gc_test/test.txt", file->absolutePath().c_str());
}

TEST(PFileTestGroup, readLineTest)
{
	file->open(PIOdevice::ReadOnly);
	STRCMP_EQUAL("G56\n", file->readLine().c_str());
	STRCMP_EQUAL("G00 X0 Y0 Z0 A0\n", file->readLine().c_str());
	STRCMP_EQUAL("G00 Z-2\n", file->readLine().c_str());
	STRCMP_EQUAL("G00 Z2\n", file->readLine().c_str());
	file->close();
}