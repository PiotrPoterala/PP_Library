#include "CppUTest/TestHarness.h"

#include "pp_sram.h"
#include "stdio.h"


TEST_GROUP(PSRamTestGroup)
{
	unsigned int tab[4];
	PSRam backupSRAM=PSRam(reinterpret_cast<unsigned int>(tab), sizeof(tab)/sizeof(unsigned int));
	
  void setup() {
		backupSRAM.open();
	}
  void teardown() {
	
		backupSRAM.close();
	}
};


TEST(PSRamTestGroup, write_readTest)
{
	backupSRAM.write(2000);
	backupSRAM.write(3000);
	backupSRAM.write(4000);
	
	LONGS_EQUAL(3, backupSRAM.pos());
	
	backupSRAM.seek(0);
	
	LONGS_EQUAL(2000, backupSRAM.read());
	LONGS_EQUAL(3000, backupSRAM.read());
	LONGS_EQUAL(4000, backupSRAM.read());
	
	backupSRAM.seek(1);
	LONGS_EQUAL(3000, backupSRAM.read());
};

TEST(PSRamTestGroup, tryOverflowTest)
{
	CHECK(backupSRAM.write(2000));
	CHECK(backupSRAM.write(3000));
	CHECK(backupSRAM.write(4000));
	CHECK(backupSRAM.write(5000));
	
	CHECK(backupSRAM.atEnd());
	
	CHECK_FALSE(backupSRAM.write(6000));
		
};

TEST(PSRamTestGroup, clearTest)
{
	CHECK(backupSRAM.write(2000));
	CHECK(backupSRAM.write(3000));
	CHECK(backupSRAM.write(4000));

	LONGS_EQUAL(3, backupSRAM.pos());
	
	backupSRAM.clear();
	
	LONGS_EQUAL(0, backupSRAM.pos());
	
	LONGS_EQUAL(0, backupSRAM.read());
	LONGS_EQUAL(0, backupSRAM.read());
	LONGS_EQUAL(0, backupSRAM.read());
	LONGS_EQUAL(0, backupSRAM.read());
};