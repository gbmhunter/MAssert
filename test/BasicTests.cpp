//!
//! @file 			BasicTests.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-08-19
//! @last-modified 	2014-09-12
//! @brief 			Contains basic tests.
//! @details
//!					See README.rst in root dir for more info.

//===== SYSTEM LIBRARIES =====//
#include <stdio.h>

//===== USER LIBRARIES =====//
#include "MUnitTest/api/MUnitTestApi.hpp"

//====== USER SOURCE =====//
#include "../api/MAssertApi.hpp"

using namespace MbeddedNinja;

namespace MAssertTestsNs
{

	bool _assertCalled;

	MAssertNs::MAssert::FailBehavior MyHandler(
			const char* condition,
			const char* msg,
			const char* file,
			const int line)
	{
		std::printf("%s(%d): Assert Failure: ", file, line);

		if (condition != NULL)
			std::printf("'%s' ", condition);

		if (msg != NULL)
			std::printf("%s", msg);

		std::printf("\n");

		_assertCalled = true;

		return MAssertNs::MAssert::Halt;
	}

	MTEST(BasicAssertRaisedTest)
	{

		MAssertNs::MAssert::SetHandler(MyHandler);

		_assertCalled = false;

		//M_STATIC_ASSERT(0)

		M_ASSERT(false);

		// Check capacity is calculated correctly
		CHECK_EQUAL(true, _assertCalled);
	}

	MTEST(BasicAssertNotRaisedTest)
	{

		MAssertNs::MAssert::SetHandler(MyHandler);

		_assertCalled = false;

		M_ASSERT(true);

		// Check capacity is calculated correctly
		CHECK_EQUAL(false, _assertCalled);
	}


} // namespace MAssertTestsNs
