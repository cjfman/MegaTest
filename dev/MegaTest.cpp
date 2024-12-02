// MegaTest

#include <stdlib.h>
#include <string.h>
#include "MegaTest.h"
#include "MegaTestLog.h"

namespace MegaTest {

void willPass(bool* result) {
	// A default test to run if non is specified
	*result = true;
	return;
}
	
MegaTest::MegaTest() {
	// Use default test willPass
	this->title = strdup("Will Pass");
	//this->test = willPass;
}

MegaTest::MegaTest(const char* title) { //, testf test) {
	this->title = strdup(title);
	//this->test = test;
}

MegaTest::~MegaTest() {
	// Will leak title. Don't care
	//free(this->title);
}

MegaTest& MegaTest::operator=(const MegaTest& other) {
	if (this == &other) return *this; // protect against invalid self-assignment
	//free(this->title);
	this->title = strdup(other.title); // Will leak. Don't care
	return *this;
}

#ifdef __AVR
// Using a pure virual function with avr-gcc was casuing problems
bool MegaTest::runTest(void) {
	return true;
}
#endif

const char* MegaTest::getTitle(void) {
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

// MegaTestFixture /////////////////////////////////////////////////////////////////

MegaTestFixture::MegaTestFixture() {
	this->title = strdup("UNAMED FIXTURE");
}

bool MegaTestFixture::runTest(void) {
	setup();
	bool result = true;
	fixtureTest(&result);
	taredown();
	return result;
}


// Private Methods

void MegaTestFixture::fixtureTest(bool* avr_test_result) { 
	*avr_test_result = true;
}

void MegaTestFixture::setup(void) {

}

void MegaTestFixture::taredown(void) {

 }

} //namespace