#include "CppUTest/TestHarness.h"

#include "pp_flash.h"
#include "pp_iodevice.h"
#include "stdio.h"


TEST_GROUP(PFlashTestGroup)
{
	

	unsigned int page1[2];
	unsigned int page2[3];
	
	PFlash flash=PFlash{{1, reinterpret_cast<unsigned int>(page1), sizeof(page1)/sizeof(unsigned int)}, {2, reinterpret_cast<unsigned int>(page2), sizeof(page2)/sizeof(unsigned int)}};
	
  void setup() {
		flash.open(PIOdevice::ReadWrite);
	
	}
  void teardown() {
		flash.close();
	}
};


TEST(PFlashTestGroup, constructTest){
	
	LONGS_EQUAL(0, flash.pos());
	LONGS_EQUAL(5, flash.size());
	
}

TEST(PFlashTestGroup, write_readTest)
{
	flash.writeAtTheEnd(2000);
	flash.writeAtTheEnd(3000);
	flash.writeAtTheEnd(4000);
	
	LONGS_EQUAL(3, flash.pos());
	
	flash.seek(0);
	
	LONGS_EQUAL(2000, flash.read());
	LONGS_EQUAL(3000, flash.read());
	LONGS_EQUAL(4000, flash.read());
	
	flash.seek( 1);
	LONGS_EQUAL(3000, flash.read());
}

TEST(PFlashTestGroup, tryOverflowTest)
{
	flash.writeAtTheEnd(2000);
	flash.writeAtTheEnd(3000);
	flash.writeAtTheEnd(4000);
	flash.writeAtTheEnd(5000);
	flash.writeAtTheEnd(6000);
	
	CHECK(flash.atEnd());
	
	CHECK_FALSE(flash.writeAtTheEnd(7000));
		
}

TEST(PFlashTestGroup, clearTest)
{
	flash.writeAtTheEnd(2000);
	flash.writeAtTheEnd(3000);
	flash.writeAtTheEnd(4000);
	
	flash.clear();
	
	LONGS_EQUAL(0, flash.pos());
	
	LONGS_EQUAL(0, flash.read());
	LONGS_EQUAL(0, flash.read());
	LONGS_EQUAL(0, flash.read());
}