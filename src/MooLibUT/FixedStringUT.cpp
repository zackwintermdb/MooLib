#include "pch.h"
#include "catch.hpp"


TEST_CASE( "size at default construction equals zero", "[fixedstring]" )
{
	ml::string512 test;

	REQUIRE(test.length() == 0);
}


TEST_CASE( "can be properly constructed with c-style string", "[fixedstring]" )
{
	ml::string512 test("test");

	REQUIRE(test == "test");
}


TEST_CASE( "can be properly constructed with other fixed string", "[fixedstring]" )
{
	ml::string512 str("test");
	ml::string512 test(str);

	REQUIRE(test == "test");
	REQUIRE(str == "test");
}


TEST_CASE( "can be assigned c-style string value", "[fixedstring]" )
{
	ml::string512 test = "test";

	REQUIRE(test == "test");
}


TEST_CASE( "can be assigned other fixed string value", "[fixedstring]" )
{
	ml::string512 str("test");
	ml::string512 test = str;

	REQUIRE(test == "test");
	REQUIRE(str == "test");
}


TEST_CASE( "can be compared with other fixed strings", "[fixedstring]" )
{
	ml::string512 test1("testing");
	ml::string512 test2("testing");
	ml::string512 test3("TESTING");

	REQUIRE(test1 == test2);
	REQUIRE(!(test1 != test2));
	REQUIRE(!(test1 == test3));
	REQUIRE(test1 != test3);
}


TEST_CASE( "can be compared with c-style strings", "[fixedstring]" )
{
	ml::string512 test1("testing");
	ml::string512 test2("testing");
	ml::string512 test3("TESTING");

	REQUIRE(test1 == "testing");
	REQUIRE(!(test1 != "testing"));
	REQUIRE(!(test1 == "TESTING"));
	REQUIRE(test1 != "TESTING");
}


TEST_CASE( "can be accessed by index", "[fixedstring]" )
{
	ml::string512 test("testing");

	REQUIRE(test[0] == 't');
	REQUIRE(test[0] == 't');
	REQUIRE(test[1] == 'e');
	REQUIRE(test[2] == 's');
	REQUIRE(test[3] == 't');
	REQUIRE(test[4] == 'i');
	REQUIRE(test[5] == 'n');
	REQUIRE(test[6] == 'g');
}


TEST_CASE( "can retreive string length", "[fixedstring]" )
{
	ml::string512 test("testing");
	size_t len = strlen(test.data());

	REQUIRE(len == test.length());
}


TEST_CASE( "can append fixed string", "[fixedstring]" )
{
	ml::string512 test1("testing");
	ml::string512 test2("123");
	test1.append(test2);

	REQUIRE(test1 == "testing123");
	REQUIRE(test2 == "123");
}


TEST_CASE( "can append c-style string", "[fixedstring]" )
{
	ml::string512 test("testing");
	test.append("123");

	REQUIRE(test == "testing123");
}


TEST_CASE( "can append char value", "[fixedstring]" )
{
	ml::string512 test("testing");
	test.append('C');

	REQUIRE(test == "testingC");
}


TEST_CASE( "can append formatted string", "[fixedstring]" )
{
	ml::string512 test("testing");
	test.append_format("%s%d", "TEST", 4);

	REQUIRE(test == "testingTEST4");
}


TEST_CASE( "can find substring", "[fixedstring]" )
{
	ml::string512 test("testing123");

	REQUIRE(test.find("123", 0) == 7);
	REQUIRE(test.find("123", 7) == 7);
}


TEST_CASE( "can find case sensitive substring", "[fixedstring]" )
{
	ml::string512 test("testing123");

	REQUIRE(test.find("123", 0) == 7);
	REQUIRE(test.find("123", 7) == 7);
	REQUIRE(test.find("TEST", 0) == -1);
}


TEST_CASE( "can find case insensitive substring", "[fixedstring]" )
{
	ml::string512 test("testing123");

	REQUIRE(test.find("ING", 0, -1, false) == 4);
}


TEST_CASE( "can find empty substring", "[fixedstring]" )
{
	ml::string512 test("testing123");

	REQUIRE(test.find("", 0, 0) == 0);
}


TEST_CASE( "find empty substring at end of string", "[fixedstring]" )
{
	ml::string512 test("testing123");

	REQUIRE(test.find("", 10, 0) == 10);
}


TEST_CASE( "can replace substring with equal length string", "[fixedstring]" )
{
	ml::string512 test("testing123");

	REQUIRE(test.replace("123", "345", true, -1) == 1);
	REQUIRE(test == "testing345");
}


TEST_CASE( "can replace substring with longer length string", "[fixedstring]" )
{
	ml::string512 test("testing123");

	REQUIRE(test.replace("test", "moomoo", true, -1) == 1);
	REQUIRE(test == "moomooing123");
}


TEST_CASE( "can replace substring with shorter length string", "[fixedstring]" )
{
	ml::string512 test("testing123");

	REQUIRE(test.replace("123", "", true, -1) == 1);
	REQUIRE(test == "testing");
}


TEST_CASE( "can replace multiple substrings", "[fixedstring]" )
{
	ml::string512 test("testtesting");

	REQUIRE(test.replace("test", "TEST", true, -1) == 2);
	REQUIRE(test == "TESTTESTing");
}


TEST_CASE( "can replace limited substrings", "[fixedstring]" )
{
	ml::string512 test("testtest123");

	REQUIRE(test.replace("test", "TEST", true, 1) == 1);
	REQUIRE(test == "TESTtest123");
}