#include "pch.h"
#include "catch.hpp"

namespace
{
	int testvar = 0;
	void testfunc()
	{
		++testvar;
	}
}

TEST_CASE( "can execute functions", "[ActiveObject]" )
{
	ml::ActiveObject active;
	active.Send(testfunc);
	REQUIRE(testvar == 1);
}