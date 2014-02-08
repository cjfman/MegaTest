// AVRTestCase.cpp

#include <string.h>
#include <stdlib.h>
#include "AVRTestCase.h"
#include "AVRTest.h"
#include "AVRTestLog.h"

namespace AVRTest {

AVRTestCase::AVRTestCase() {
	title = strdup("UNNAMED_AVRTESTCASE");
	//strncpy(title, "UNNAMED_AVRTESTCASE", 64);
	//title = "UNNAMED_AVRTESTCASE";
}

AVRTestCase::AVRTestCase(const char* title) {
	this->title = strdup(title);
	//strncpy(this->title, title, 64);
	//this->title = title;
}

AVRTestCase::~AVRTestCase() {
	// Will leak title. Don't care
	//free(title);
}

AVRTestCase& AVRTestCase::operator= (const AVRTestCase& other) {
	if (this == &other) return *this; // protect against invalid self-assignment
	//free(this->title);
	this->title = strdup(other.title); // Will leak. Don't care
	this->tests = other.tests;
	return *this;
}

void AVRTestCase::addTest(AVRTest* test) {
	// Adds a new test to the case
	tests.push_back(test);
}

bool AVRTestCase::runTests(void) {
	// Runs all of the tests.
	// Does not run if no title is defined
	if (!title) return true;
	bool final_result = true; // Anded with the result of each test
	// Run though each test
	for (unsigned int i = 0; i < tests.size(); i++) {
		AVRTest* test = tests[i];
		avrtestlog.startTest(test->getTitle());
		// Run the test
		bool result = test->runTest();
		avrtestlog.endTest(result);
		final_result &= result;
	}
	return final_result;
}

uint16_t AVRTestCase::numberOfTests(void) {
	return tests.size();
}

// Getters////////////////////////////

inline const char* AVRTestCase::getTitle(void) {
	return title;
}

} // namespace