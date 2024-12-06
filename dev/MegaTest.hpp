// MegaTest
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

#ifndef MEGATEST_h
#define MEGATEST_h

//#include <stdlib.h>
//extern "C" void __cxa_pure_virtual() { while (1); }

namespace MegaTest {

typedef void (*voidf)(void);
typedef void (*testf)(bool *);


/* MegaTest class
 *
 * description: An abstract class for wrapping user defined tests
 *
 */
class MegaTest {
    // NOTE: The title member leaks when destructor, copy,
    // or assigmnment operator are used, but this is ok,
    // because each object should persist until all tests
    // are done, and assignment is only ever called once.
    // This is done this way so that the objects can be
    // stored in a dynamically allocated array.

protected:
    const char* title;  // The title of the test

public:
    MegaTest();
    MegaTest(const char* title);
    ~MegaTest();
    MegaTest& operator=(const MegaTest& other);

    // Getters
    const char* getTitle(void) const { return this->title; }

    // Methods
#ifdef __AVR
    virtual bool runTest(void); // Runs the test and returns whether
                                // it passed or not.
#else
    virtual bool runTest(void) = 0;
#endif
};


/* MegaBasicTest class
 *
 * description: A basic test that uses a function pointer to point to the user
 *              test.
 *
 */
class MegaBasicTest : public MegaTest {
protected:
    testf test;     // The pointer to the test function

public:
    MegaBasicTest(const char* title, testf newTest);

    // Methods
    bool runTest(void); // Runs the test and returns whether
                        // it passed or not.
};


/* MegaTestFixture class
 *
 * description: A test that runs setup() before the user test and taredown
 *              afterwards. This class should be subclassed. Any members
 *              defined in the subclass will be available to the test.
 *              Any members defined in a subclass should either be protected
 *              or public.
 *
 */
class MegaTestFixture : public MegaTest {
public:
    MegaTestFixture();
    virtual bool runTest(void);

private:
    virtual void fixtureTest(bool*);
    virtual void setup(void);
    virtual void taredown(void);
};

} // namespace


#endif //Whole File
