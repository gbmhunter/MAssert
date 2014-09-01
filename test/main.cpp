//!
//! @file 			main.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-08-19
//! @last-modified 	2014-09-01
//! @brief 			Contains main entry point for unit tests.
//! @details
//!					See README.rst in root dir for more info.

#include <stdio.h>

#include "../api/MAssertApi.hpp"

#include "unittest-cpp/UnitTest++/UnitTest++.h"
#include "unittest-cpp/UnitTest++/TestReporterStdout.h"

class Printer
{
	public:/*
		void PrintDebug(const char* msg)
		{
			std::cout << msg;
		}

		void PrintCmdLine(const char* msg)
		{
			std::cout << msg;
		}

		void PrintError(const char* msg)
		{
			std::cout << msg;
		}*/
};

int main()
{
/*
	Printer printer;

	// Set up printing
	Clide::Print::AssignCallbacks(
			SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintDebug),
			SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintCmdLine),
			SlotMachine::CallbackGen<Printer, void, const char*>(&printer, &Printer::PrintError));

	Clide::Print::enableCmdLinePrinting = false;
	Clide::Print::enableErrorPrinting = false;
	Clide::Print::enableDebugInfoPrinting = false;*/

	return UnitTest::RunAllTests();
	
	try
    {
        UnitTest::TestReporterStdout reporter;
		UnitTest::TestRunner runner(reporter);
	
	
		return runner.RunTestsIf(
			UnitTest::Test::GetTestList(),
			"ParamTests",
			UnitTest::True(),
			0);
    }
    catch(std::exception const& e)
    {
         printf("%s", e.what());
         // If you are feeling mad (not in main) you could rethrow! 
    }
	
}
