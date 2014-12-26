#include "pch.h"
#include "catch.hpp"

TEST_CASE( "can tokenize string that doesn't contain delimiter", "[tokenizer]" )
{
	ml::Tokenizer tok("teststr", ' ');

	REQUIRE(tok.GetRef() == "teststr");
	REQUIRE(!tok.Next());
}


TEST_CASE( "can tokenize string that contains delimiter", "[tokenizer]" )
{
	ml::Tokenizer tok("test str", ' ');

	REQUIRE(tok.GetRef() == "test");
	REQUIRE(tok.Next());
	REQUIRE(tok.GetRef() == "str");
	REQUIRE(!tok.Next());
}


TEST_CASE( "can tokenize with multiple delimiters", "[tokenizer]" )
{
	std::set<char> delimiters;
	delimiters.insert(' ');
	delimiters.insert('#');

	ml::Tokenizer tok("test str# two", delimiters);

	REQUIRE(tok.GetRef() == "test");
	REQUIRE(tok.Next());
	REQUIRE(tok.GetRef() == "str");
	REQUIRE(tok.Next());
	REQUIRE(tok.GetRef() == "two");
	REQUIRE(!tok.Next());
}


TEST_CASE( "can tokenize with end position", "[tokenizer]" )
{
	char str[16];
	strcpy(str, "test str 3");
	ml::Tokenizer tok(str, str + 8, ' ');

	REQUIRE(tok.GetRef() == "test");
	REQUIRE(tok.Next());
	REQUIRE(tok.GetRef() == "str");
	REQUIRE(!tok.Next());
}


TEST_CASE( "can tokenize with double quote escape", "[tokenizer]" )
{
	ml::Tokenizer tok("\"test str\" next", ' ', true);

	REQUIRE(tok.GetRef() == "test str");
	REQUIRE(tok.Next());
	REQUIRE(tok.GetRef() == "next");
	REQUIRE(!tok.Next());
}


TEST_CASE( "can escape double quote", "[tokenizer]" )
{
	ml::Tokenizer tok("\\\"test str\\\" next", ' ', true);

	REQUIRE(tok.GetRef() == "\"test");
	REQUIRE(tok.Next());
	REQUIRE(tok.GetRef() == "str\"");
	REQUIRE(tok.Next());
	REQUIRE(tok.GetRef() == "next");
	REQUIRE(!tok.Next());
}


TEST_CASE( "can tokenize with single quote escape", "[tokenizer]" )
{
	ml::Tokenizer tok("'test str' next", ' ', false, true);

	REQUIRE(tok.GetRef() == "test str");
	REQUIRE(tok.Next());
	REQUIRE(tok.GetRef() == "next");
	REQUIRE(!tok.Next());
}


TEST_CASE( "can escape single quote", "[tokenizer]" )
{
	ml::Tokenizer tok("\\'test str\\' next", ' ', false, true);

	REQUIRE(tok.GetRef() == "'test");
	REQUIRE(tok.Next());
	REQUIRE(tok.GetRef() == "str'");
	REQUIRE(tok.Next());
	REQUIRE(tok.GetRef() == "next");
	REQUIRE(!tok.Next());
}