// MegaTestCase
// 
// Test cases are used to contain and run instances of MegaTest
// They are fairly straitforward. Use the addTest mehtod to add
// add a new test, and use the runTests method to run all tests
// in the case.

#ifndef MEGATESTCASE_h
#define MEGATESTCASE_h

#include <inttypes.h>
#include "MegaTest.h"
#include "AVRVector.h"

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

	char* title; 			// The title of the case
	AVRVector<MegaTest*> tests; // List of tests

public:
	MegaTestCase();
	MegaTestCase(const char* title);
	~MegaTestCase();
	MegaTestCase& operator= (const MegaTestCase& other);
	void addTest(MegaTest* test);
	bool runTests(void);
	uint16_t numberOfTests(void);
	// Getters
	inline const char* getTitle(void);
};

} // namespace

#endif // Whole File