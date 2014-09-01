//!
//! @file 			MAssert.cpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-08-19
//! @last-modified 	2014-09-01
//! @brief
//! @details
//!					See README.rst in root dir for more info.


#include "../include/MAssert.hpp"

#include <cstdio>
#include <cstdarg>

namespace MbeddedNinja
{
	namespace MAssertNs
	{
		namespace
		{


			MAssert::FailBehavior DefaultHandler(
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

				return MAssert::Halt;
			}

			MAssert::Handler& GetAssertHandlerInstance()
			{
				// Creates a default handler and returns it
				static MAssert::Handler s_handler = &DefaultHandler;
				return s_handler;
			}

		}

		MAssert::Handler MAssert::GetHandler()
		{
			return GetAssertHandlerInstance();
		}

		void MAssert::SetHandler(MAssert::Handler newHandler)
		{
			// Sets handler to a new function
			GetAssertHandlerInstance() = newHandler;
		}

		MAssert::FailBehavior MAssert::ReportFailure(
			const char* condition,
			const char* file,
			const int line,
			const char* msg, ...)
		{
			const char* message = NULL;

			// Check if a message was provided
			if (msg != NULL)
			{
				//! @todo Make buffer smaller.
				static char msgBuff[100];
				{
					va_list args;
					va_start(args, msg);
					vsnprintf(
						msgBuff,
						sizeof(msgBuff),
						msg,
						args);
					va_end(args);
				}

				message = msgBuff;
			}

			return GetAssertHandlerInstance()(condition, message, file, line);
		}
	}
}
