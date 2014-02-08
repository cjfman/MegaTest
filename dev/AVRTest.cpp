// AVRTest

#include <stdlib.h>
#include <string.h>
#include "AVRTest.h"
#include "AVRTestLog.h"

namespace AVRTest {

void willPass(bool* result) {
	// A default test to run if non is specified
	*result = true;
	return;
}
	
AVRTest::AVRTest() {
	// Use default test willPass
	this->title = strdup("Will Pass");
	//this->test = willPass;
}

AVRTest::AVRTest(const char* title) { //, testf test) {
	this->title = strdup(title);
	//this->test = test;
}

AVRTest::~AVRTest() {
	// Will leak title. Don't care
	//free(this->title);
}

AVRTest& AVRTest::operator=(const AVRTest& other) {
	if (this == &other) return *this; // protect against invalid self-assignment
	//free(this->title);
	this->title = strdup(other.title); // Will leak. Don't care
	return *this;
}

#ifdef __AVR
// Using a pure virual function with avr-gcc was casuing problems
bool AVRTest::runTest(void) {
	return true;
}
#endif

const char* AVRTest::getTitle(void) {
	return this->title;
}

// AVRBasicTest //////////////////////////////////////////////////////////////////

AVRBasicTest::AVRBasicTest(const char* title, testf test) {
	this->title = strdup(title);
	this->test = test;
}

bool AVRBasicTest::runTest(void) {
	// Run the test
	// Create a boolean and pass its address to the test function
	// If needed, the test function will change the bool's value
	bool result = true;
	this->test(&result);
	return result;
}

// AVRTestFixture /////////////////////////////////////////////////////////////////

AVRTestFixture::AVRTestFixture() {
	this->title = strdup("UNAMED FIXTURE");
}

bool AVRTestFixture::runTest(void) {
	setup();
	bool result = true;
	fixtureTest(&result);
	taredown();
	return result;
}


// Private Methods

void AVRTestFixture::fixtureTest(bool* avr_test_result) { 
	*avr_test_result = true;
}

void AVRTestFixture::setup(void) {

}

void AVRTestFixture::taredown(void) {

 }

} //namespace