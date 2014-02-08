// AVRTestCase.h

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

// File Description
// Test cases are used to contain and run instances of AVRTest
// They are fairly straitforward. Use the addTest mehtod to add
// add a new test, and use the runTests method to run all tests
// in the case. See the CPP file for detailed descriptions of
// methods and functions.

#ifndef AVRTESTCASE_h
#define AVRTESTCASE_h

#include <inttypes.h>
#include "AVRTest.h"
#include "AVRVector.h"
#include "AVRTest_Default_Configuration.h"

#ifdef DESKTOP
#include <vector>
using std::vector;
#endif

namespace AVRTest {

class AVRTestCase {
	// NOTE: The title member leaks when destructor, copy, 
	// or assigmnment operator are used, but this is ok, 
	// because each object should persist until all tests
	// are done, and assignment is only ever called once.
	// This is done this way so that the objects can be
	// stored in a dynamically allocated array.

#ifndef AVRTEST_MAX_TITLE_LENGTH
	char* title; 				// The title of the case
#else
	char title[AVRTEST_MAX_TITLE_LENGTH]; // The title of the case
#endif
	AVRVector<AVRTest*> tests;  // List of tests

public:
	AVRTestCase();
	AVRTestCase(const char* title);
	~AVRTestCase();
	AVRTestCase& operator= (const AVRTestCase& other);
	void addTest(AVRTest* test);
	bool runTests(void);
	uint16_t numberOfTests(void);
	// Getters
	const char* getTitle(void);
};

} // namespace

#endif // Whole File