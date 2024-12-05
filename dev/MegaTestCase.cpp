// MegaTestCase.cpp

#include <string.h>
#include <stdlib.h>
#include "MegaTestCase.hpp"
#include "MegaTest.hpp"
#include "MegaTestLog.hpp"

namespace MegaTest {

MegaTestCase::MegaTestCase() {
	title = strdup("UNNAMED_MEGATESTCASE");
	//strncpy(title, "UNNAMED_MEGATESTCASE", 64);
	//title = "UNNAMED_MEGATESTCASE";
}

MegaTestCase::MegaTestCase(const char* title) {
	this->title = strdup(title);
	//strncpy(this->title, title, 64);
	//this->title = title;
}

MegaTestCase::~MegaTestCase() {
	// Will leak title. Don't care
	//free(title);
}

MegaTestCase& MegaTestCase::operator= (const MegaTestCase& other) {
	if (this == &other) return *this; // protect against invalid self-assignment
	//free(this->title);
	this->title = strdup(other.title); // Will leak. Don't care
	this->tests = other.tests;
	return *this;
}

void MegaTestCase::addTest(MegaTest* test) {
	// Adds a new test to the case
	tests.push_back(test);
}

bool MegaTestCase::runTests(void) {
	// Runs all of the tests.
	// Does not run if no title is defined
	if (!title) return true;
	bool final_result = true; // Anded with the result of each test
	// Run though each test
	for (unsigned int i = 0; i < tests.size(); i++) {
		MegaTest* test = tests[i];
		megatestlog.startTest(test->getTitle());
		// Run the test
		bool result = test->runTest();
		megatestlog.endTest(result);
		final_result &= result;
	}
	return final_result;
}

uint16_t MegaTestCase::numberOfTests(void) {
	return tests.size();
}

// Getters////////////////////////////

const char* MegaTestCase::getTitle(void) {
	return title;
}

} // namespace
