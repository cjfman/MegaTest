// MegaTestSuite.h

// The MIT License (MIT)
// Copyright (c) 2013, Charles Jessup Franklin

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


// This Test Suite is a light weight testing suite designed for AVR.
// To add a test, first define a test using the MEGATEST_CASE(<casename>) macro
// Any test defined afterwards will be part of that test case. Please
// end a test case with the ENDCASE macro, or your compiler will through a 
// syntax error. To define a test, use the AVRTESET(<testname>) macro.
// DO NOT define tests outside of a test case. This will result in undefined 
// behavior.

// These macros automatically register with the global registrar, defined in
// MegaTestRegistrar.cpp. In the main loop, use avrTestRegistrar.runAllTests()
// to run all of the registered tests.

// Each macro defines and instantiates an integer using the result of the 
// registration method. This number is of non-consequence and is there
// purely so that the registration function will run.


#ifndef MEGATESTSUITE_h
#define MEGATESTSUITE_h

#ifndef MEGATEST
#define MEGATEST
#endif

#include <math.h>
#include <string.h>
#include <inttypes.h>
#include "MegaTest_Default_Configuration.h"
#include "MegaTestRegistrar.h"
#include "MegaTest.h"

#if defined AVR_PRINT_ARDUINO || defined ARDUINO_LIBS
#include <Arduino.h>
#endif

using MegaTest::getRegistrar;
using MegaTest::MegaTestFixture;


/***************************************************************************
                            Function Prototypes
***************************************************************************/

namespace MegaTest {

bool floatCompare(float a, float b);
bool AlmostEqual2sComplement(float A, float B, long maxUlps);
bool AlmostEqualRelativeOrAbsolute(float A, float B,
            float maxRelativeError, float maxAbsoluteError);
} //namespace

void avrtest_init(void);

/***************************************************************************
                          Test and Case Registration
***************************************************************************/

MegaTest::MegaTestRegistrar avrTestRegistrar;

#ifndef ARDUINO_IDE
int main(void) {
	avrtest_init();
	avrTestRegistrar.runAllTests();
	#ifndef DESKTOP
	while(true);
	#endif
	return 0;
}
#else
void setup() {
	avrtest_init();
}

void loop() {
	avrTestRegistrar.runAllTests();
	while(true);
}
#endif

/* MEGATEST_CASE macro
 *
 * parameter case_name : The name of the test case.
 * 						 Must contain no spaces.
 * 
 * description: Used to define the start of a test case.
 * 				Define any tests to be part of this case
 * 				between this macro and the ENDCASE macro.
 *
 */
#define MEGATEST_CASE(case_name) \
 	MegaTest::MegaTestCase MEGA_TEST_CASE_##case_name(#case_name); \
 	const uint8_t MEGA_TEST_CASE_int_##case_name \
	= avrTestRegistrar.newCase(&MEGA_TEST_CASE_##case_name); \
	namespace  MEGA_TEST_CASE_SPACE_##case_name {

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
#define MEGATEST_TEST(test_name) \
	void MEGA_TEST_##test_name(bool*); \
	MegaTest::AVRBasicTest AVR_BASIC_TEST_##test_name(#test_name, MEGA_TEST_##test_name); \
	const uint8_t MEGA_TEST_##test_name##_ID = \
		avrTestRegistrar.newTest(&AVR_BASIC_TEST_##test_name); \
	void MEGA_TEST_##test_name(bool* avr_test_result)

/* AVRTEXTFIX macro
 *
 * description: Defines a test using a test fixture 
 *              and registers it with the global registrar
 *
 */
#define MEGATEST_FIX(test_name, fixture) \
	class MEGA_TEST_FIXTURE_##test_name : public fixture { \
	public: \
		MEGA_TEST_FIXTURE_##test_name() { setTitle(#test_name); }; \
	private: \
		void fixtureTest(bool*); \
	}; \
	MEGA_TEST_FIXTURE_##test_name avrTestFixture_##test_name; \
	const uint8_t MEGA_TEST_##test_name##_ID = \
		avrTestRegistrar.newTest(&avrTestFixture_##test_name); \
	void MEGA_TEST_FIXTURE_##test_name::fixtureTest(bool* avr_test_result)


/***************************************************************************
                                  Assertions
***************************************************************************/

#define ASSERT_PASS \
     *avr_test_result = true; \
     return;

#define ASSERT_FAIL \
     *avr_test_result = false; \
     avrtestlog.endTest(false, "Asserted Fail");

#define ASSERT_TRUE(candidate) \
    if (!(candidate)) { \
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
	if ((exp) != (act)) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act, (exp), (act)); \
		return; \
	}

#define ASSERT_NEQUAL(act, exp) \
	if ((exp) == (act)) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act ": Expected Not Equal", (exp), (act)); \
		return; \
	}

#define ASSERT_STREQUAL(act, exp) \
	if (strcmp((exp), (act))) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act, (exp), (act)); \
		return; \
	}

#define ASSERT_STRNEQUAL(act, exp) \
	if (!strcmp((exp), (act))) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act, (exp), (act)); \
		return; \
	}

#define ASSERT_FLOAT_EQUAL(act, exp) \
	if (!MegaTest::floatCompare((exp), (act))) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act, (exp), (act)); \
		return; \
	}

#define ASSERT_FLOAT_NEQUAL(act, exp) \
	if (MegaTest::floatCompare((exp), (act))) { \
		*avr_test_result = false; \
		avrtestlog.expected(#act, (exp), (act)); \
		return; \
	}

#define ASSERT_ZERO(act) \
	if ((act) != 0) { \
		*avr_test_result = false; \
		avrtestlog.endTest(false, #act ": Expected 0"); \
	} 

#define ASSERT_NZERO(act) \
	if ((act) == 0) { \
		*avr_test_result = false; \
		avrtestlog.endTest(false, #act ": Expected 0"); \
	} 

/***************************************************************************
                                Helper Functions
***************************************************************************/

namespace MegaTest {

bool floatCompare(float a, float b) {
#ifdef AVR_FLOAT_MAXULPS
	return AlmostEqual2sComplement(a, b, AVR_FLOAT_MAXULPS);
#elif defined AVR_FLOAT_REL_COMPARE
	return AlmostEqualRelativeOrAbsolute(a, b, AVR_FLOAT_MAX_REL, AVR_FLOAT_MAX_ABS);
#else
	return a == b;
#endif
}

#define AVR_FLIP_VECTOR (unsigned long) 0x80000000UL

bool AlmostEqual2sComplement(float A, float B, long maxUlps)
{
    // Make sure maxUlps is non-negative and small enough that the
    // default NAN won't compare as equal to anything.
    if (maxUlps < 0 || maxUlps > 4L * 1024L * 1024L) return false;
    long aInt = *(long*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = AVR_FLIP_VECTOR - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    long bInt = *(long*)&B;
    if (bInt < 0)
        bInt = AVR_FLIP_VECTOR - bInt;
    long intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;
    return false;
}

bool AlmostEqualRelativeOrAbsolute(float A, float B,
                float maxRelativeError, float maxAbsoluteError)
{
    if (fabs(A - B) < maxAbsoluteError)
        return true;
    float relativeError;
    if (fabs(B) > fabs(A))
        relativeError = fabs((A - B) / B);
    else
        relativeError = fabs((A - B) / A);
    if (relativeError <= maxRelativeError)
        return true;
    return false;
}

} //namespace


void avrtest_init(void) {
#ifndef ARDUINO_IDE
	#if defined AVR_PRINT_ARDUINO || defined ARDUINO_INIT
	init();
		#if defined(USBCON) 
	USBDevice.attach();
		#endif
	#endif // arduino mixed
#endif //ARDUINO_IDE
}

#endif // Whole file
