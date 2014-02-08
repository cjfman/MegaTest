// MegaTest.cpp

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

#include <stdlib.h>
#include <string.h>
#include "MegaTest.h"
#include "MegaTestLog.h"

namespace MegaTest {

/*
 * function willPass
 *
 * description: A default test to run if non is specified
 *
 */
void willPass(bool* result) {
	*result = true;
	return;
}

/* 
 * MegaTest::Default Constructor
 */	
MegaTest::MegaTest() {
	// Use default test willPass
#ifndef MegaTEST_MAX_TITLE_LENGTH
	this->title = strdup("Will Pass");
#else
	strlcpy(this->title, "Will Pass", MegaTEST_MAX_TITLE_LENGTH);
#endif
}

/*
 * MegaTest::Contructor that gets the title from the parameter
 */
MegaTest::MegaTest(const char* title) {
#ifndef MegaTEST_MAX_TITLE_LENGTH
	this->title = strdup(title);
#else
	//strlcpy(this->title, title, MegaTEST_MAX_TITLE_LENGTH);
#endif
}

/*
 * MegaTest::Destructor
 */
MegaTest::~MegaTest() {
	// Will leak title. Don't care
	//free(this->title); // Commented out because title would get freed prematurely
}

/*
 * MegaTest::Assignment Operator
 */
MegaTest& MegaTest::operator=(const MegaTest& other) {
	if (this == &other) return *this; // protect against invalid self-assignment
	//free(this->title); // Commented out because title would get freed prematurely
#ifndef MegaTEST_MAX_TITLE_LENGTH
	this->title = strdup(other.title); // Will leak. Don't care
#else
	strlcpy(this->title, other.title, MegaTEST_MAX_TITLE_LENGTH);
#endif
	return *this;
}

#ifdef __Mega
/*
 * MegaTest::runTest
 *
 * returns: True if the test passed. False otherwise.
 *
 * description: Runs the assigned test. This is only defined because
 * using a pure virual function with avr-gcc was casuing problems
 *
 */
bool MegaTest::runTest(void) {
	return true;
}
#endif

/*
 * MegaTest::getTitle
 *
 * returns: The title of the test
 *
 */
const char* MegaTest::getTitle(void) {
	return this->title;
}

// MegaBasicTest //////////////////////////////////////////////////////////////////

/*
 * MegaBasicTest::Constructor
 * 
 * parameters: (title) the title of the test, (testf) function pointer to the test
 *
 * description: The only constructor for a basic test. It takes the title and the 
 *              test to be run when runTest is called.
 *
 */
MegaBasicTest::MegaBasicTest(const char* title, testf test) {
#ifndef MegaTEST_MAX_TITLE_LENGTH
	this->title = strdup(title);
#else
	strlcpy(this->title, title, MegaTEST_MAX_TITLE_LENGTH);
#endif
	this->test = test;
}

/*
 * MegaBasicTest::runTest
 *
 * returns: True if the test passed. False otherwise.
 *
 * description: Runs the test and returns the result
 *
 */
bool MegaBasicTest::runTest(void) {
	// Run the test
	// Create a boolean and pass its address to the test function
	// If needed, the test function will change the bool's value
	bool result = true;
	this->test(&result);
	return result;
}

// MegaTestFixture /////////////////////////////////////////////////////////////////

/*
 * MegaTestFixture::Constructor
 *
 * description: This is a basic contructor. This class is intended to be subclassed
 *
 */
MegaTestFixture::MegaTestFixture() {
#ifndef MegaTEST_MAX_TITLE_LENGTH
	this->title = strdup("UNAMED FIXTURE");
#else
	strlcpy(this->title, "UNAMED FIXTURE", MegaTEST_MAX_TITLE_LENGTH);
#endif
}

/*
 * MegaTestFixture::setTitle
 *
 * parameter: title, the title of the test fixture
 *
 * description: This is the setter for the title member
 *
 */
void MegaTestFixture::setTitle(const char* title) {
#ifndef MegaTEST_MAX_TITLE_LENGTH
	this->title = strdup(title);
#else
	strlcpy(this->title, title, MegaTEST_MAX_TITLE_LENGTH);
#endif
}

/*
 * MegaTestFixture::runTest
 *
 * returns: True is test passed. False otherwise.
 * 
 * description: Runs the defined test. Calls setup before hand and taredown afterwards.
 *
 */
bool MegaTestFixture::runTest(void) {
	setup();
	bool result = true;
	fixtureTest(&result);
	taredown();
	return result;
}


// Private Methods

/*
 * MegaTestFixture::fixtureTest
 *
 * description: This is the test that runs. It is inteneded to be overrided the
 *              this class is subclassed. The default version passes.
 */
void MegaTestFixture::fixtureTest(bool* mega_test_result) { 
	*mega_test_result = true;
}

/* 
 * MegaTestFixture::setup
 *
 * description: Empty setup method that is called before the test is run.
 *              Should be overrided
 */
void MegaTestFixture::setup(void) {

}

/* 
 * MegaTestFixture::taredown
 *
 * description: Empty taredown method that is called before the test is run.
 *              Should be overrided
 */
void MegaTestFixture::taredown(void) {

 }

} //namespace