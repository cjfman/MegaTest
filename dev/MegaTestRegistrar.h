// MegaTestRegistrar

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
#include "AVRVector.h"

#ifdef DESKTOP
#include <vector>
using std::vector;
#endif

namespace MegaTest {

class MegaTestRegistrar {
	AVRVector<MegaTestCase> testCases;		// List that contains registered cases
	MegaTestCase currentCase; 			// Test case that is being registered
	bool caseOpen;						// Set when a case is being registered
	uint16_t numberOfTests; 			// The total number of tests

public:
	MegaTestRegistrar();
	~MegaTestRegistrar();
	void runAllTests(void);
	int newCase(const char* title);
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