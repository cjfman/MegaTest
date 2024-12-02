// MegaTestLog.h

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
// The MegaTestLog records the results of all cases and tests and presents the results
// to the user. The test log abstracts away the method of printing the results. The
// method used to print can be chosen in the configuration file. This is intended to
// be used as a singleton. Please see the CPP file for detailed of all non-template
// methods and functions.

#ifndef MEGATESTLOG_h
#define MEGATESTLOG_h

#include <inttypes.h>
#include "MegaTest_Default_Configuration.h"

// Conventience Macro defined for printing the values of variables with their names
#define AVR_PRINT_VAR(var) \
	avrtestlog.print(#var": "); \
	avrtestlog.println(var);

namespace MegaTest {

class MegaTestLog {
	bool caseOpen; 					// True if a case is being run
	bool testOpen;					// True if a test is being run
	bool setup_done; 				// True if setup is done
	uint16_t failed_cases;			// The number of failed cases
	uint16_t failed_tests;			// The number of failed tests in the current case
	uint16_t total_failed_tests; 	// The number of failed tests total in all cases
	uint8_t indent_level; 			// The indent level of the output format. Only used
									// when configured to print XML.

public:
	MegaTestLog();
	void setup(void);
	void print(char c);
	void print(char* message);
	void print(const char* message);
	void print(unsigned char c);
	void print(int i);
	void print(unsigned int i);
	void print(long l);
	void print(unsigned long l);
	void print(float f);
	void print(double d);
	void print(bool b);
#ifdef AVR_LOG_XML
	template<typename T>
	void tabprint(T object);
	template<typename T>
	void tabprintln(T object);
#endif
#ifdef MegaTestCustomPrint
	template<typename T>
	void print(T object);
#endif
	template<typename T>
	void println(T var);
	void log(const char* message);
	void nl(void);
	
	//Test Result Log Methods
	void startCase(const char*);
	void endCase(bool);
	void startTest(const char*);
	void endTest(bool);
	void endTest(bool, const char*);
	void testFailed(void);
	template<typename T, typename T2>
	void expected(T ex, T2 ac);
	template<typename T, typename T2>
	void expected(const char* var, T ex, T2 ac);
	void conclusion(void);

private:
	//void write(char c);
	//void write(const char* message);
	// Copied From Arduino
	void printNumber(unsigned long, uint8_t);
    void printFloat(double, uint8_t);
};

///////////////////////////////////////////////////////////////////////////////////
// The following section defines template methods that allow the ASSERTION macros,
// defined in MegaTestSuite.h, to be used with user defined types.
///////////////////////////////////////////////////////////////////////////////////

/*
 * MegaTestLog::print
 *
 * parameter: (object) object to be printed
 *
 * description: Template method that is called if the Log does not know how to print
 *              a user defined object. It calls a function (avrTestCustomPrint)that is 
 *              defined by the user. The user should overload the function for each user
 *              defined class.
 *
 */
#ifdef MegaTestCustomPrint
template<typename T>
void MegaTestLog::print(T object) {
	avrTestCustomPrint(object);
}
#endif

/*
 * MegaTestLog::println
 *
 * parameter: (var) object to be printed
 *
 * description: Like print, but it adds a new line afterwards.
 *
 */
template<typename T>
void MegaTestLog::println(T var) {
	print(var);
	nl();
}

/*
 * MegaTestLog::expected
 *
 * parameters: (ex) the expected value. 
 *             (ac) the actual value.
 *
 * description: Records that the test has failed, and reports 
 *              the expected and actual values that caused the
 *              test to fail.
 *
 */
template<typename T, typename T2>
void MegaTestLog::expected(T ex, T2 ac) {
#ifdef AVR_LOG_XML
	println("</serialLog>");
	tabprintln("<result>false</result>");
	tabprintln("<reason>");
	indent_level++;
	tabprint("<expected>");
	print(ex);
	println("</expected>");
	tabprint("<actual>");
	print(ac);
	println("</actual>");
	indent_level--;
	tabprintln("</reason>");
	indent_level--;
	tabprintln("</MegaTest>");
	failed_tests++;
	testOpen = false;
#else
	endTest(false);
	print("> Expected: ");
	print(ex);
	print("; Actual: ");
	print(ac);
	nl();
#endif
}

/*
 * MegaTestLog::expected
 *
 * parameters: var, The name of the variable who's value is the actual value.
 *             ex, The expected value. 
 *             ac, The actual value.
 *
 * description: Records that the test has failed, and reports 
 *              the expected and actual values that caused the
 *              test to fail.
 *
 */
template<typename T, typename T2>
void MegaTestLog::expected(const char* var, T ex, T2 ac) {
#ifdef AVR_LOG_XML
	println("</serialLog>");
	tabprintln("<result>false</result>");
	tabprintln("<reason>");
	indent_level++;
	tabprint("<variable>");
	print(var);
	println("</variable>");
	tabprint("<expected>");
	print(ex);
	println("</expected>");
	tabprint("<actual>");
	print(ac);
	println("</actual>");
	indent_level--;
	tabprintln("</reason>");
	indent_level--;
	tabprintln("</MegaTest>");
	failed_tests++;
	testOpen = false;
#else
	endTest(false);
	print("> ");
	print(var);
	print("; Expected: ");
	print(ex);
	print("; Actual: ");
	print(ac);
	nl();
#endif
}

/*
 * MegaTestLog::tabprint
 *
 * parameter: object, the object to be printed
 *
 * description: Only used when printing XML. Assuming a new line as been started,
 *              it prints the specified object with the proper indintation.
 */
#ifdef AVR_LOG_XML
template<typename T>
void MegaTestLog::tabprint(T object) {
	for (int i = 0; i < indent_level; i++) {
		print(AVR_LOG_TAB_CHAR);
	}
	print(object);
}

/*
 * MegaTestLog::tabprint
 *
 * parameter: object, the object to be printed
 *
 * description: Only used when printing XML. Like tabprintln, but adds a newline after.
 */
template<typename T>
void MegaTestLog::tabprintln(T object) {
	tabprint(object);
	nl();
}
#endif // AVR_LOG_XML


} // namespace

// The global log ojbect singleton
extern MegaTest::MegaTestLog avrtestlog;

#endif // Whole File