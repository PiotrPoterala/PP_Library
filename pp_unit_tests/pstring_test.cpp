#include "CppUTest/TestHarness.h"

#include "pstring.h"

TEST_GROUP(PStringTestGroup)
{
  void setup() {}
  void teardown() {}
};


TEST(PStringTestGroup, findDataAfterAcronimTest)
{
 // FAIL("Fail me!");
	PString str("X10.123 Y20.458");
	
	STRCMP_EQUAL("10.123", str.findDataAfterAcronim('X').c_str());
	STRCMP_EQUAL("20.458", str.findDataAfterAcronim('Y').c_str());
}



TEST(PStringTestGroup, findValueAfterAcronimTest)
{
	PString str("X10.123 Y20.458");
	
	DOUBLES_EQUAL(10.123, str.findValueAfterAcronim('X', 100000), 0.001);
	DOUBLES_EQUAL(456, str.findValueAfterAcronim('V', 456), 0.001);
}



//    @Test
//    void splitWithClamps() {
//        Pstring str=new Pstring(" \"pio\", \"stasiek\"");

//        assertEquals(2, str.splitWithClamps(',', '"').size());
//        assertEquals("pio", str.splitWithClamps(',', '"').get(0));
//        assertEquals("stasiek", str.splitWithClamps(',', '"').get(1));

//        assertEquals(1, str.splitWithClamps('.', '"').size());
//        assertEquals("pio", str.splitWithClamps(',', '"').get(0));

//        assertEquals(0, str.splitWithClamps(',', '\'').size());

//        str.str=",'stasiek'";
//        assertEquals(1, str.splitWithClamps(',', '\'').size());
//        assertEquals("stasiek", str.splitWithClamps(',', '\'').get(0));

//        str.str=" \"stasiek\"";
//        assertEquals(1, str.splitWithClamps(',', '"').size());
//        assertEquals("stasiek", str.splitWithClamps(',', '"').get(0));

//        str.str="ANET \"pio\", \"stasiek\"";
//        assertEquals(2, str.splitWithClamps(',', '"').size());
//        assertEquals("pio", str.splitWithClamps(',', '"').get(0));
//        assertEquals("stasiek", str.splitWithClamps(',', '"').get(1));

//        str.str="\"\", \"\"";
//        assertEquals(2, str.splitWithClamps(',', '"').size());
//        assertEquals("", str.splitWithClamps(',', '"').get(0));
//        assertEquals("", str.splitWithClamps(',', '"').get(1));
//    }

//    @Test
//    void convertStreamToString() {
//        String initialString = "text\ntext2\ntext3\n";
//        InputStream is = new ByteArrayInputStream(initialString.getBytes());

//        assertEquals("text\ntext2\ntext3\n", Pstring.convertStreamToString(is));
//    }