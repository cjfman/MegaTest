// MegaTest

#include <stdlib.h>
#include <string.h>
#include "MegaTest.hpp"
#include "MegaTestLog.hpp"

namespace MegaTest {

void willPass(bool* result) {
    // A default test to run if non is specified
    *result = true;
    return;
}

MegaTest::MegaTest()
  : title("Will Pass")
{
}

MegaTest::MegaTest(const char* title)
  : title(strdup(title)) // This will leak, and I don't care
{
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


// MegaBasicTest //////////////////////////////////////////////////////////////////

MegaBasicTest::MegaBasicTest(const char* title, testf test)
  : MegaTest(title),
    test(test)
{
}

bool MegaBasicTest::runTest(void) {
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

void MegaTestFixture::fixtureTest(bool* mega_test_result) {
    *mega_test_result = true;
}

void MegaTestFixture::setup(void) {
}

void MegaTestFixture::taredown(void) {
}

} //namespace
