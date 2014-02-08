// MegaTest.h

// The MIT License (MIT)
// Copyright (c) 2013, Charles Jessup Franklin

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// File Description
// A rapper for a user defined test. Basic tests have a title and a test 
// funtion pointer of type testf. The function itself is defined by 
// the user and registered by the by global test registrar. A funtion of 
// type testf returns void so that the user does not need to provide a
// defaut return value. In order for a test to provide a result that is
// not returned, a pointer of type *bool is passed as a parameter.
// Assertion macros dereference the pointer to pass the result to the
// caller, then return if the assertion failed.
// Test fixtures use the user defined test to define a member function
// so that the test can have access to fixture members. Please see the
// cpp file for detailed descriptions of all methods and functions.

#ifndef MEGATEST_h
#define MEGATEST_h

#include "MegaTest_Default_Configuration.h"


namespace MegaTest {

typedef void (*voidf)(void);
typedef void (*testf)(bool *);


/* MegaTest class
 *
 * description: An abstract class for wrapping user defined tests.
 *              DO NOT make an instance of this class.
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
#ifndef MEGA_TEST_MAX_TITLE_LENGTH
	char* title;	// The title of the test
#else
	char title[MEGA_TEST_MAX_TITLE_LENGTH];	// The title of the test
#endif

public:
	MegaTest();
	MegaTest(const char* title);
	~MegaTest();
	MegaTest& operator=(const MegaTest& other);

	// Getters
	const char* getTitle(void);

	// Methods
#ifdef __Mega
	virtual bool runTest(void);	// Runs the test and returns whether
								// it passed or not.
#else
	virtual bool runTest(void) = 0;
#endif
};


/* MegaBasicTest class
 *
 * description: A basic test that uses a function pointer to point to the user
 *              test. Most tests will be instances of this class. Can be part of
 *              and MegaTestCase.
 *
 */
class MegaBasicTest : public MegaTest {
protected:
	testf test;		// The pointer to the test function

public:
	MegaBasicTest(const char* title, testf newTest);

	// Methods
	bool runTest(void);	// Runs the test and returns whether
						// it passed or not.
};


/* MegaTestFixture class
 *
 * description: A test that runs setup() before the user test and taredown 
 *              afterwards. This class should be subclassed. Any members 
 *              defined in the subclass will be in the same scope as the test.
 *              Any members defined in a subclass should either be protected
 *              or public. Can be part of an MegaTestCase.
 *              DO NOT make an instance of this class.
 *
 */
class MegaTestFixture : public MegaTest {
public:
	MegaTestFixture();
	void setTitle(const char* title);
	virtual bool runTest(void);

private:
	virtual void fixtureTest(bool*);
	virtual void setup(void);
	virtual void taredown(void);
};

} // namespace


#endif //Whole File