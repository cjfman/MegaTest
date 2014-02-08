// MegaTestRegistrar.h

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
// The main test registrar. All test cases and tests are to be registered with 
// the global definition of the registrar. DO NOT instantiate your own.
// To access the registar, use the getRegistrar() function, which returns a 
// pointer of type *MegaTestRegistar. 
//
// To register a case, use the newCase method. Any tests registered with the 
// newTest method will be added to the most recently registered case. After 
// each test has been registered, use the submitCase method or register a new 
// case, to finish the registration. Do not register a test without registering
// a case first. This has undefined behavior. When all tests have been 
// registered, use the runAllTests method. 
//
// Please see the CPP file for detailed descriptions of all methods and functions.
//
// Notes:
// - When a case is being registered, or is open, that means that any new test
// that is registered will be added to that case.
// - Opening a new case for registration will automatically submit any open
//   case.
// - The registration functions return type int so that they can be run before
//   main, but the value is nonconsequential.

#ifndef MEGATESTREGISTRAR_h
#define MEGATESTREGISTRAR_h

#include <inttypes.h>
#include "MegaTest.h"
#include "MegaTestCase.h"
#include "MegaTestLog.h"
#include "MegaVector.h"

#ifdef DESKTOP
#include <vector>
using std::vector;
#endif

namespace MegaTest {

class MegaTestRegistrar {
	MegaVector<MegaTestCase*> testCases;	// List that contains registered cases
	MegaTestCase* currentCase; 			// Test case that is being registered
	bool caseOpen;						// Set when a case is being registered
	uint16_t numberOfTests; 			// The total number of tests

public:
	void runAllTests(void);
	int newCase(MegaTestCase* newcase);
	int newTest(MegaTest* test);
	int submitCase();
};

/* getRegistrar
 *
 * returns : A pointer to the global registrar.
 *
 * description : Used to get the main registrar. This fuction must be used
 * 				 so that the a static instance of the registrar can be
 * 				 operated upon before the mainloop is called without the 
 *				 constructor being called again.
 *
 */
MegaTestRegistrar* getRegistrar(void);

} //namespace

#endif // Whole File