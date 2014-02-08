// MegaTestRegistrar.cpp

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
#include "MegaTestRegistrar.h"
#include "MegaTestCase.h"
#include "MegaTest.h"
#include "MegaTestLog.h"

namespace MegaTest {

/*
 * MegaTestRegistrar::runAllTests
 *
 * description: After all tests, cases, and fixtures have been registered with
 *              the registrar, calling this method will run each case and report
 *              the results back to the user.
 */
void MegaTestRegistrar::runAllTests(void) {
	// Close and complete registration of any open cases
	if (caseOpen) {
		submitCase();
	}
	// Startup the main log
	megatestlog.setup();
	megatestlog.log("Running all Tests");
	// Run through each case
	for (unsigned int i = 0; i < testCases.size(); i++) {
		MegaTestCase* testcase = testCases[i];		// Get case from list
		megatestlog.startCase(testcase->getTitle());	// Report to the log
		bool res = testcase->runTests();			// Run the case
		megatestlog.endCase(res);					// Retport to the log
	}
	megatestlog.conclusion();						// Finish up
}

/*
 * MegaTestRegistrar::newCase
 *
 * parameters: (newcase) Pointer to the case to be registered. Instance of MegaTestCase.
 *
 * returns: (int) The number of cases registred, excluding this one.
 *
 * description: Opens the specified case for registration. Will be run when all cases
 *              are run. Any tests registered before submitCase() is called will be added
 *              to this case.
 *
 */
int MegaTestRegistrar::newCase(MegaTestCase* newcase) {
	// Close and complete registration of any open case.
	if (caseOpen) {
		submitCase();
	}
	currentCase = newcase;
	caseOpen = true;
	return testCases.size();
}

/*
 * MegaTestRegistsrar::newTest
 *
 * parameters: (test) Pointer to the test to be added. Instance of MegaTest
 *
 * returns: (int) The number of tests total across all cases, excluding this one.
 *
 * description: Registers a new test and adds the test to the currently open case.
 *              If a case is not open, a new case will be opened. DO NOT count on
 *              this behavior.
 *
 */
int MegaTestRegistrar::newTest(MegaTest* test) {
	if (!caseOpen) {
		//this->newCase("UNNAMED_MEGA_TESTCASE");
		return 0;
	}
	currentCase->addTest(test);
	return numberOfTests++;
}

/*
 * MegaTestRegistrar::submitCase
 *
 * returns: (int) 0. The return value of this method is non consequential.
 *
 * description: Submits the currently open case and closes it for registration.
 *              Any tests added after this is called will be added to another case.
 *
 */
int MegaTestRegistrar::submitCase() {
	// Complete the registration of a case and add it to the
	// list of cases.
	if (caseOpen) {
		testCases.push_back(currentCase);
		caseOpen = false;
	}
	return 0;
}

/*
 * function getRegistrar
 *
 * returns: A pointer to the global registrar
 * 
 * description: Keeps a statically declared copy of the global registrar.
 *              Mega-GCC seems to have trouble initializing static variables with
 *              anything other than a litteral. To work around this, I initialize
 *              a pointer to 0. This is followed by a conditional that allocates
 *              and initializes an MegaTestRegistrar object.
 *
 */
MegaTestRegistrar* getRegistrar(void) {
	static MegaTestRegistrar *registrar = 0;
	if (!registrar) {
		registrar = (MegaTestRegistrar*)malloc(sizeof(MegaTestRegistrar));
		*registrar = MegaTestRegistrar();
	}
	return registrar;
}

} // namespace