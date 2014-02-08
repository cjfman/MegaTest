// MegaTestCase.cpp

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

#include <string.h>
#include <stdlib.h>
#include "MegaTestCase.h"
#include "MegaTest.h"
#include "MegaTestLog.h"

namespace MegaTest {

/*
 * MegaTestCase::Default Constructor
 */
MegaTestCase::MegaTestCase() {
#ifndef MEGA_TEST_MAX_TITLE_LENGTH
	title = strdup("UNNAMED_MEGA_TESTCASE");
#else
	strlcpy(title, "UNNAMED_MEGA_TESTCASE", MEGA_TEST_MAX_TITLE_LENGTH);
#endif
}

/*
 * MegaTestCase::Use this Constructor
 * 
 * parameters: (title) the title of the case.
 *
 */
MegaTestCase::MegaTestCase(const char* title) {
#ifndef MEGA_TEST_MAX_TITLE_LENGTH
	this->title = strdup(title);
#else
	strlcpy(this->title, title, MEGA_TEST_MAX_TITLE_LENGTH);
#endif
}

/*
 * MegaTestCase::Destructor
 */
MegaTestCase::~MegaTestCase() {
	// Will leak title. Don't care
	//free(title); // Commented because title was beeing freed prematurely
}

/*
 * MegaTestCase::Assignment Operator
 */
MegaTestCase& MegaTestCase::operator= (const MegaTestCase& other) {
	if (this == &other) return *this; // protect against invalid self-assignment
	//free(this->title);  // Commented because title was beeing freed prematurely
#ifndef MEGA_TEST_MAX_TITLE_LENGTH
	this->title = strdup(other.title); // Will leak. Don't care
#else
	strlcpy(this->title, other.title, MEGA_TEST_MAX_TITLE_LENGTH);
#endif
	this->tests = other.tests;
	return *this;
}

/*
 * MegaTestCase::addTest
 *
 * parameters: (test) a pointer to an MegaTest Object to be added to the case
 *
 * description: Addes the specified test to the case. The test will be run
 *              when the case runs.
 *
 */
void MegaTestCase::addTest(MegaTest* test) {
	// Adds a new test to the case
	tests.push_back(test);
}

/*
 * MegaTestCase::runTests
 * 
 * returns: True if all tests passed. False otherwise.
 * 
 * description: Runs all of the tests added by addTest().
 *
 */
bool MegaTestCase::runTests(void) {
	// Runs all of the tests.
	// Does not run if no title is defined
	if (!title) return true;
	bool final_result = true; // Anded with the result of each test.
	// Run though each test
	for (unsigned int i = 0; i < tests.size(); i++) {
		MegaTest* test = tests[i];				// Aquire test from list of tests
		megatestlog.startTest(test->getTitle());	// Report the test to the log
		// Run the test
		bool result = test->runTest();
		megatestlog.endTest(result);				// Report teh end of the test
		final_result &= result;
	}
	return final_result;
}

/*
 * MegaTestCase::numberOfTests
 *
 * returns: (uint16_t) The number of tests that are in the case
 *
 */
uint16_t MegaTestCase::numberOfTests(void) {
	return tests.size();
}

// Getters////////////////////////////

/*
 * MegaTestCase::getTitle
 *
 * returns: (const char*) The title of the case
 *
 */
const char* MegaTestCase::getTitle(void) {
	return title;
}

} // namespace