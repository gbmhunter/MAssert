//!
//! @file 			MAssert.hpp
//! @author 		Geoffrey Hunter <gbmhunter@gmail.com> (www.mbedded.ninja)
//! @created		2014-08-19
//! @last-modified 	2014-09-02
//! @brief
//! @details
//!					See README.rst in root dir for more info.

#ifndef M_ASSERT_NS_M_ASSERT
#define M_ASSERT_NS_M_ASSERT

#define M_ASSERTS_ENABLED

namespace MbeddedNinja
{
	namespace MAssertNs
	{


		namespace MAssert
		{
			enum FailBehavior
			{
				Halt,			//!< Halts the program
				Continue,		//!< Does not halt the program
			};

			//! @brief		Use this type 'Handler' to create your own error handler function.
			typedef FailBehavior (*Handler)(const char* condition,
											const char* msg,
											const char* file,
											int line);

			Handler GetHandler();

			//! @brief		Use this to assign your own assertion handler, rather than using the default one.
			void SetHandler(Handler newHandler);

			FailBehavior ReportFailure(const char* condition,
									   const char* file,
									   int line,
									   const char* msg, ...);

		}
	}
}

//#define M_HALT() __debugbreak()
//#define M_HALT() __builtin_trap()

//! @brief		Empty halt instruction.
#define M_HALT()

#define M_UNUSED(x) do { (void)sizeof(x); } while(0)

#ifdef M_ASSERTS_ENABLED
	#define M_ASSERT(cond) \
		do \
		{ \
			if (!(cond)) \
			{ \
				if (MbeddedNinja::MAssertNs::MAssert::ReportFailure(#cond, __FILE__, __LINE__, 0) == \
						MbeddedNinja::MAssertNs::MAssert::Halt) \
					M_HALT(); \
			} \
		} while(0)

	#define M_ASSERT_MSG(cond, msg, ...) \
		do \
		{ \
			if (!(cond)) \
			{ \
				if (MbeddedNinja::MAssertNs::MAssert::ReportFailure(#cond, __FILE__, __LINE__, (msg), __VA_ARGS__) == \
						MbeddedNinja::MAssertNs::MAssert::Halt) \
					M_HALT(); \
			} \
		} while(0)

	#define M_ASSERT_FAIL(msg, ...) \
		do \
		{ \
			if (MbeddedNinja::MAssertNs::MAssert::ReportFailure(0, __FILE__, __LINE__, (msg), __VA_ARGS__) == \
					MbeddedNinja::MAssertNs::MAssert::Halt) \
			M_HALT(); \
		} while(0)

	#define M_VERIFY(cond) M_ASSERT(cond)
	#define M_VERIFY_MSG(cond, msg, ...) M_ASSERT_MSG(cond, msg, ##__VA_ARGS__)
// The next section is for defining all macros as essentially nothing if
// asserts has been disabled.
#else // #ifdef M_ASSERTS_ENABLED
	#define M_ASSERT(condition) \
		do { M_UNUSED(condition); } while(0)
	#define M_ASSERT_MSG(condition, msg, ...) \
		do { M_UNUSED(condition); M_UNUSED(msg); } while(0)
	#define M_ASSERT_FAIL(msg, ...) \
		do { M_UNUSED(msg); } while(0)
	#define M_VERIFY(cond) (void)(cond)
	#define M_VERIFY_MSG(cond, msg, ...) \
		do { (void)(cond); M_UNUSED(msg); } while(0)
#endif


#endif // M_ASSERT_NS_M_ASSERT
