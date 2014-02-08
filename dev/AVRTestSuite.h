// AVRTestSuite

/*
 * This Test Suite is a light weight testing suite designed for AVR.
 * To add a test, first define a test using the AVRTEST_CASE(<casename>) macro
 * Any test defined afterwards will be part of that test case. Please
 * end a test case with the ENDCASE macro, or your compiler will through a 
 * syntax error. To define a test, use the AVRTESET(<testname>) macro.
 * DO NOT define tests outside of a test case. This will result in undefined 
 * behavior.
 *
 * These macros automatically register with the global registrar, defined in
 * AVRTestRegistrar.cpp. In the main loop, use getRegistrar()->runAllTests()
 * to run all of the registered tests.
 *
 * Each macro defines and instantiates an integer using the result of the 
 * registration method. This number is of non-consequence and is there
 * purely so that the registration function will run.
 */


#ifndef AVRTESTSUITE_h
#define AVRTESTSUITE_h

#include <math.h>
#include <string.h>
#include <inttypes.h>
#include "AVRTest_Configuration.h"
#include "AVRTestRegistrar.h"
#include "AVRTest.h"
 
#include "AVRTestLog.h"
#include "AVRTestCase.h"
#include "AVRVector.h"


using AVRTest::getRegistrar;
using AVRTest::AVRTestFixture;


/***************************************************************************
                            Function Prototypes
***************************************************************************/

namespace AVRTest {

bool floatCompare(float a, float b);
bool AlmostEqual2sComplement(float A, float B, int maxUlps);
bool AlmostEqualRelativeOrAbsolute(float A, float B,
            float maxRelativeError, float maxAbsoluteError);

} //namespace

/***************************************************************************
                          Test and Case Registration
***************************************************************************/

/* AVRTEST_CASE macro
 *
 * parameter case_name : The name of the test case.
 * 						 Must contain no spaces.
 * 
 * description: Used to define the start of a test case.
 * 				Define any tests to be part of this case
 * 				between this macro and the ENDCASE macro.
 *
 */
#define AVRTEST_CASE(case_name) const uint8_t AVR_TEST_CASE_##case_name \
	= getRegistrar()->newCase(#case_name); \
	namespace  AVR_TEST_CASE_SPACE_##case_name {

/* ENDCASE macro
 *
 * description : Used to close a test case definition.
 *				 Must contain no spaces.
 *
 */
#define ENDCASE } //namespace

/* AVR_CASE macro
 *
 * parameter test_name : The name of the test case.
 *						 Must contain no spaces.
 * 
 * description: Used to define a test. The macro should be 
 * 				followed by a test definition enclosed in 
 * 				{<code>}
 *
 */
#define AVRTEST(test_name) \
	void AVR_TEST_##test_name(bool*); \
	AVRTest::AVRBasicTest AVR_BASIC_TEST_##test_name(#test_name, AVR_TEST_##test_name); \
	const uint8_t AVR_TEST_##test_name##_ID = \
		getRegistrar()->newTest(&AVR_BASIC_TEST_##test_name); \
	void AVR_TEST_##test_name(bool* avr_test_result)

/* AVRTEXTFIX macro
 *
 * description: Defines a test using a test fixture 
 *              and registers it with the global registrar
 *
 */
#define AVRTESTFIX(test_name, fixture) \
	class AVR_TEST_FIXTURE_##test_name : public fixture { \
	public: \
		AVR_TEST_FIXTURE_##test_name() { title = strdup(#test_name); }; \
	private: \
		void fixtureTest(bool*); \
	}; \
	AVR_TEST_FIXTURE_##test_name avrTestFixture_##test_name; \
	const uint8_t AVR_TEST_##test_name##_ID = \
		getRegistrar()->newTest(&avrTestFixture_##test_name); \
	void AVR_TEST_FIXTURE_##test_name::fixtureTest(bool* avr_test_result)


/***************************************************************************
                                  Assertions
***************************************************************************/


#define ASSERT_FAIL *avr_test_result = false; \
     avrtestlog.endTest(false, "Asserted Fail");

#define ASSERT_TRUE(candidate) \
    if (!candidate) { \
        avrtestlog.endTest(false, #candidate ": Expected True"); \
		*avr_test_result = false; \
		return; \
	}

#define ASSERT_FALSE(candidate) \
	if (candidate) { \
		*avr_test_result = false; \
		avrtestlog.endTest(false, #candidate ": Expected False"); \
		return; \
	}

#define ASSERT_EQUAL(act, exp) \
	if (exp != act) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act, exp, act); \
		return; \
	}

#define ASSERT_NEQUAL(act, exp) \
	if (exp == act) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act ": Expected Not Equal", exp, act); \
		return; \
	}

#define ASSERT_STREQUAL(act, exp) \
	if (strcmp(exp, act)) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act, exp, act); \
		return; \
	}

#define ASSERT_STRNEQUAL(act, exp) \
	if (!strcmp(exp, act)) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act, exp, act); \
		return; \
	}

#define ASSERT_FLOAT_EQUAL(act, exp) \
	if (!AVRTest::floatCompare(exp, act)) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act, exp, act); \
		return; \
	}

#endif // Whole file