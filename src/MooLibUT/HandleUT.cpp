#include "pch.h"
#include "catch.hpp"

TEST_CASE( "can default construct", "[handle]" )
{
	ml::Handle handle;

	REQUIRE(handle.GetNative() == INVALID_HANDLE_VALUE);
}


TEST_CASE( "can assign HANDLE value", "[handle]" )
{
	ml::Handle handle = GetCurrentThread();

	REQUIRE(handle.GetNative() == GetCurrentThread());
}


TEST_CASE( "can check validity on invalid handle", "[handle]" )
{
	ml::Handle handle;

	REQUIRE(!handle.IsValid());
}


TEST_CASE( "can check validity on valid handle", "[handle]" )
{
	ml::Handle handle = GetCurrentThread();

	REQUIRE(handle.IsValid());
}


TEST_CASE( "can compare with equal Handle", "[handle]" )
{
	ml::Handle handle1;
	ml::Handle handle2;

	REQUIRE(handle1 == handle2);
	REQUIRE(!(handle1 != handle2));
}


TEST_CASE( "can compare with inequal Handle", "[handle]" )
{
	ml::Handle handle1 = GetCurrentThread();
	ml::Handle handle2;

	REQUIRE(handle1 != handle2);
	REQUIRE(!(handle1 == handle2));
}


TEST_CASE( "can compare with equal HANDLE", "[handle]" )
{
	ml::Handle handle1;
	ml::Handle handle2;

	REQUIRE(handle1 == handle2.GetNative());
	REQUIRE(!(handle1 != handle2.GetNative()));
}


TEST_CASE( "can compare with inequal HANDLE", "[handle]" )
{
	ml::Handle handle1 = GetCurrentThread();
	ml::Handle handle2;

	REQUIRE(handle1 != handle2.GetNative());
	REQUIRE(!(handle1 == handle2.GetNative()));
}


TEST_CASE( "can close properly", "[handle]" )
{
	ml::Handle handle = GetCurrentThread();
	handle.Close();

	REQUIRE(!handle.IsValid());
}