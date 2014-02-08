// AVRTest
//
// A rapper for a user defined test. Basic tests have a title and a test 
// funtion pointer of type testf. The function itself is defined by 
// the user and registered by the by global test registrar. A funtion of 
// type testf returns void so that the user does not need to provide a
// defaut return value. In order for a test to provide a result that is
// not returend, a pointer of type *bool is passed as a parameter.
// Assertion macros dereference the pointer to pass the result to the
// caller, then return if the assertion failed.
// Test fixtures use the user defined test to define a member function
// so that the test can have access to fixture members.

#ifndef AVRTEST_h
#define AVRTEST_h

//#include <stdlib.h>
//extern "C" void __cxa_pure_virtual() { while (1); }

namespace AVRTest {

typedef void (*voidf)(void);
typedef void (*testf)(bool *);


/* AVRTest class
 *
 * description: An abstract class for wrapping user defined tests
 *
 */
class AVRTest {
	// NOTE: The title member leaks when destructor, copy, 
	// or assigmnment operator are used, but this is ok, 
	// because each object should persist until all tests
	// are done, and assignment is only ever called once.
	// This is done this way so that the objects can be
	// stored in a dynamically allocated array.

protected:
	char* title;	// The title of the test

public:
	AVRTest();
	AVRTest(const char* title); //, testf newTest);
	~AVRTest();
	AVRTest& operator=(const AVRTest& other);

	// Getters
	const char* getTitle(void);

	// Methods
#ifdef __AVR
	virtual bool runTest(void);	// Runs the test and returns whether
								// it passed or not.
#else
	virtual bool runTest(void) = 0;
#endif
};


/* AVRBasicTest class
 *
 * description: A basic test that uses a function pointer to point to the user
 *              test.
 *
 */
class AVRBasicTest : public AVRTest {
protected:
	testf test;		// The pointer to the test function

public:
	AVRBasicTest(const char* title, testf newTest);

	// Methods
	bool runTest(void);	// Runs the test and returns whether
						// it passed or not.
};


/* AVRTestFixture class
 *
 * description: A test that runs setup() before the user test and taredown 
 *              afterwards. This class should be subclassed. Any members 
 *              defined in the subclass will be available to the test.
 *              Any members defined in a subclass should either be protected
 *              or public.
 *
 */
class AVRTestFixture : public AVRTest {
public:
	AVRTestFixture();
	virtual bool runTest(void);

private:
	virtual void fixtureTest(bool*);
	virtual void setup(void);
	virtual void taredown(void);
};

} // namespace


#endif //Whole File