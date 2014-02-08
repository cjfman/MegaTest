// AVRTestCase.cpp

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
#include "AVRTestCase.h"
#include "AVRTest.h"
#include "AVRTestLog.h"

namespace AVRTest {

/*
 * AVRTestCase::Default Constructor
 */
AVRTestCase::AVRTestCase() {
#ifndef AVRTEST_MAX_TITLE_LENGTH
	title = strdup("UNNAMED_AVRTESTCASE");
#else
	strlcpy(title, "UNNAMED_AVRTESTCASE", AVRTEST_MAX_TITLE_LENGTH);
#endif
}

/*
 * AVRTestCase::Use this Constructor
 * 
 * parameters: (title) the title of the case.
 *
 */
AVRTestCase::AVRTestCase(const char* title) {
#ifndef AVRTEST_MAX_TITLE_LENGTH
	this->title = strdup(title);
#else
	strlcpy(this->title, title, AVRTEST_MAX_TITLE_LENGTH);
#endif
}

/*
 * AVRTestCase::Destructor
 */
AVRTestCase::~AVRTestCase() {
	// Will leak title. Don't care
	//free(title); // Commented because title was beeing freed prematurely
}

/*
 * AVRTestCase::Assignment Operator
 */
AVRTestCase& AVRTestCase::operator= (const AVRTestCase& other) {
	if (this == &other) return *this; // protect against invalid self-assignment
	//free(this->title);  // Commented because title was beeing freed prematurely
#ifndef AVRTEST_MAX_TITLE_LENGTH
	this->title = strdup(other.title); // Will leak. Don't care
#else
	strlcpy(this->title, other.title, AVRTEST_MAX_TITLE_LENGTH);
#endif
	this->tests = other.tests;
	return *this;
}

/*
 * AVRTestCase::addTest
 *
 * parameters: (test) a pointer to an AVRTest Object to be added to the case
 *
 * description: Addes the specified test to the case. The test will be run
 *              when the case runs.
 *
 */
void AVRTestCase::addTest(AVRTest* test) {
	// Adds a new test to the case
	tests.push_back(test);
}

/*
 * AVRTestCase::runTests
 * 
 * returns: True if all tests passed. False otherwise.
 * 
 * description: Runs all of the tests added by addTest().
 *
 */
bool AVRTestCase::runTests(void) {
	// Runs all of the tests.
	// Does not run if no title is defined
	if (!title) return true;
	bool final_result = true; // Anded with the result of each test.
	// Run though each test
	for (unsigned int i = 0; i < tests.size(); i++) {
		AVRTest* test = tests[i];				// Aquire test from list of tests
		avrtestlog.startTest(test->getTitle());	// Report the test to the log
		// Run the test
		bool result = test->runTest();
		avrtestlog.endTest(result);				// Report teh end of the test
		final_result &= result;
	}
	return final_result;
}

/*
 * AVRTestCase::numberOfTests
 *
 * returns: (uint16_t) The number of tests that are in the case
 *
 */
uint16_t AVRTestCase::numberOfTests(void) {
	return tests.size();
}

// Getters////////////////////////////

/*
 * AVRTestCase::getTitle
 *
 * returns: (const char*) The title of the case
 *
 */
const char* AVRTestCase::getTitle(void) {
	return title;
}

} // namespace
