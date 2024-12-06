// MegaTestCase
// 
// Test cases are used to contain and run instances of MegaTest
// They are fairly straitforward. Use the addTest mehtod to add
// add a new test, and use the runTests method to run all tests
// in the case.

#ifndef MEGATESTCASE_h
#define MEGATESTCASE_h

#include <inttypes.h>
#include "MegaTest.hpp"
#include "MegaVector.hpp"

#ifdef DESKTOP
#include <vector>
using std::vector;
#endif

namespace MegaTest {

class MegaTestCase {
    // NOTE: The title member leaks when destructor, copy,
    // or assigmnment operator are used, but this is ok,
    // because each object should persist until all tests
    // are done, and assignment is only ever called once.
    // This is done this way so that the objects can be
    // stored in a dynamically allocated array.

    const char* title;           // The title of the case
    MegaVector<MegaTest*> tests; // List of tests

public:
    MegaTestCase();
    MegaTestCase(const char* title);
    MegaTestCase& operator= (const MegaTestCase& other);
    void addTest(MegaTest* test);
    bool runTests(void);
    uint16_t numberOfTests(void) { return this->tests.size(); }

    // Getters
    const char* getTitle(void) { return this->title; }

    virtual ~MegaTestCase();
};

} // namespace

#endif // Whole File
