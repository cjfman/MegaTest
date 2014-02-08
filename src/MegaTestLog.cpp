// MegaTestLog.cpp

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

#include <inttypes.h>
#include <math.h>
#include <string.h>
#include "MegaTestLog.h"
#include "MegaTest_Default_Configuration.h"

#ifdef DESKTOP
	#include <iostream>
	using std::cout;
#else
	#ifdef MEGA_PRINT_ARDUINO
		#include <HardwareSerial.h>
	#endif
#endif // DESKTOP

namespace MegaTest {

/*
 * MegaTestLog::Constructor
 */
MegaTestLog::MegaTestLog() {
	testOpen = false;
	caseOpen = false;
	setup_done = false;
	failed_cases = 0;
	failed_tests = 0;
	total_failed_tests = 0;
	indent_level = 0;
}

/*
 * MegaTestLog::setup
 *
 * description: Should be called before any other function. Sets up the serial port,
 *              or any other devices that are used for returning the results to
 *              the user.
 *
 */
void MegaTestLog::setup(void) {
	if (setup_done) {
		return;
	}
#ifndef DESKTOP
#ifdef MEGA_PRINT_ARDUINO
	MEGA_PRINT_ARDUINO.begin(MEGA_PRINT_BAUD);
#endif
#ifdef MEGA_PRINT_USER_DEFINED
	mega_print_user_setup();
#endif
#endif // DESKTOP
#ifdef MEGA_LOG_XML
	println("<MegaTestResults>");
	indent_level++;
#endif
	setup_done = true;
}

/*
 * MegaTestLog::print<char>
 *
 * parameter: c, The character to be printed
 *
 * description: The much of the abstraction from the method of printing 
 *              is done here. The specified character is printed.
 *
 */
void MegaTestLog::print(char c) {
#ifdef DESKTOP
	cout << c;
#else
#ifdef MEGA_PRINT_ARDUINO
	MEGA_PRINT_ARDUINO.print(c);
#endif
#ifdef MEGA_PRINT_ADDR
	*((char*)MEGA_PRINT_ADDR) = c;
#endif
#ifdef MEGA_PRINT_USER_DEFINED
	mega_print_user_sendchar(c);
#endif
#endif // DESKTOP
}

/*
 * MegaTestLog::print<char*>
 *
 * parameter: message, a c-string to be printed
 *
 * description: prints a c-string by casting to const char*
 *
 */
void MegaTestLog::print(char* message) {
	print((const char*)message);
}

/*
 * MegaTestLog::print<cosnt char*>
 *
 * parameter: c, The c-string to be printed
 *
 * description: The much of the abstraction from the method of printing 
 *              is done here. The specified string is printed.
 *
 */
void MegaTestLog::print(const char* message) {
#ifdef DESKTOP
	cout << message;
#elif defined MEGA_PRINT_ARDUINO
	MEGA_PRINT_ARDUINO.print(message);
#elif defined MEGA_PRINT_USER_DEFINED_STRING
	mega_print_user_sendstring(message);
#else
	size_t len = strlen(message);
	for (unsigned int i = 0; i < len; i++) {
		print(message[i]);
	}
#endif
}

/*
 * MegaTestLog::print<unsigned char>
 *
 * parameter: c, an unsigned char to be printed
 *
 * description: prints an unsigned char by casting to unsigned long
 *
 */
void MegaTestLog::print(unsigned char c) {
	print((unsigned long) c);
}

/*
 * MegaTestLog::print<int>
 *
 * parameter: i, an ing to be printed
 *
 * description: prints an ing by casting to long
 *
 */
void MegaTestLog::print(int i) {
	print((long) i);
}

/*
 * MegaTestLog::print<unsigned int>
 *
 * parameter: i, an unsigned int to be printed
 *
 * description: prints an unsigned int by casting to unsigned long
 *
 */
void MegaTestLog::print(unsigned int i) {
	print((unsigned long) i);
}

/*
 * MegaTestLog::print<long>
 *
 * parameter: l, a long integer to be printed
 *
 * description: prints the long integer by first printing the negative sign if printing
 *              in base 10, then printing the absolute value of the number.
 *
 */
void MegaTestLog::print(long l) {
#if defined MEGA_PRINT_SIGNED_DEC || MEGA_PRINT_BASE == 10
	if (l < 0) {
		print('-');
	}
	printNumber(abs(l), 10);
#else
	printNumber(l, MEGA_PRINT_BASE));
#endif
}

/*
 * MegaTestLog::print<unsigned long>
 *
 * parameter: l, an unsigned long to be printed
 *
 * description: prints an unsigned long
 *
 */
void MegaTestLog::print(unsigned long l) {
	printNumber(l, MEGA_PRINT_BASE);
}

/*
 * MegaTestLog::print<float>
 *
 * parameter: f, a float to be printed
 *
 * description: prints a float by casting to double
 *
 */
void MegaTestLog::print(float f) {
	print((double)f);
}

/*
 * MegaTestLog::print<double>
 *
 * parameter: d, a double to be printed
 *
 * description: prints a double
 *
 */
void MegaTestLog::print(double d) {
	printFloat(d, MEGA_FLOAT_POINTS);
}

/*
 * MegaTestLog::print<bool>
 *
 * parameter: b, a boolean to be printed
 *
 * description: prints a boolean by translation to c-string
 *
 */
void MegaTestLog::print(bool b) {
	if (b) print("true");
	else   print("false");
}

/*
 * MegaTestLog::log
 *
 * parameter: message, a c-string containing a message to be printed
 *
 * description: Prints the message with a new line. If XML is being printed, 
 *              it is wrapped by a "comment" tag when printed.
 *
 */
void MegaTestLog::log(const char* message) {
#ifdef MEGA_LOG_XML
	tabprint("<comment>");
	print(message);
	println("</comment>");
#else
	println(message);
#endif
}

/*
 * MegaTestLog::nl
 *
 * description: prints a new line character
 *
 */
void MegaTestLog::nl(void) {
	print(MEGA_PRINT_NL);
}


//Test Result Log Methods///////////////////////////////

/*
 * MegaTestLog::startCase
 *
 * description: Called to report the start of a case to the log. Should be called
 *              before any of the tests of a given case are run and reported.
 *
 */
void MegaTestLog::startCase(const char* name) {
	if (caseOpen) {
		endCase(true);
	}
	caseOpen = true;
#ifdef MEGA_LOG_XML
	tabprint("<MegaTestCase title=\"");
	print(name);
	print("\"");
	println(">");
	indent_level++;
#else
	println(name);
#endif
}

/*
 * MegaTestLog::endCase
 *
 * parameter: res, The result of the case. Should be true if passed and false otherwise. 
 *
 * description: Called to report the conclution of a case.
 *
 */
void MegaTestLog::endCase(bool res) {
	if (!caseOpen) return;	
#ifdef MEGA_LOG_XML
	if (res) {
		tabprintln("<result>true</result>");
	}
	else {
		tabprintln("<result>false</result>");
	}
	indent_level--;
	tabprintln("</MegaTestCase>");
#else
	if (res) {
		println("Case Passed");
	}
	else {
		print("Case Failed: ");
		print(failed_tests);
		println(" tests");
	}
	nl();
#endif
	if (!res) {
		total_failed_tests += failed_tests;
		failed_tests = 0;
		failed_cases++;
	}
	caseOpen = false;
}

/*
 * MegaTestLog::startTest
 *
 * description: Called to report the start of a test to the log.
 *
 */
void MegaTestLog::startTest(const char* name) {	
#ifdef MEGA_LOG_XML
	tabprint("<MegaTest title=\"");
	print(name);
	print("\"");
	println(">");
	indent_level++;
	tabprint("<serialLog>");
#else
	print(name);
	int dots = 32 - strlen(name);
	dots = (dots > 3) ? dots : 3;
	for (int i = 0; i < dots; i++) {
		print('.');
	}
#endif
	testOpen = true;
}

/*
 * MegaTestLog::endTest
 *
 * parameter: res, The result of the test. Should be true if passed and false otherwise. 
 *
 * description: Called to report the conclution of a test.
 *
 */
void MegaTestLog::endTest(bool res) {
	if (!testOpen) return;
#ifdef MEGA_LOG_XML
	println("</serialLog>");
	if (res) {
		tabprintln("<result>true</result>");
	}
#else
	if (res) {
		log("passed");
	}
#endif
	else {
		testFailed();
	}
	testOpen = false;
#ifdef MEGA_LOG_XML
	indent_level--;
	tabprintln("</MegaTest>");
#endif
}

/*
 * MegaTestLog::endTest
 *
 * parameter: res, The result of the test. Should be true if passed and false otherwise. 
 *            message, a c-string containing a message about the conclution of the test.
 *
 * description: Called to report the conclution of a test. The message will be included
 *              in the results when reported to the user.
 *
 */
void MegaTestLog::endTest(bool res, const char* message) {
	if (!testOpen) return;
#ifdef MEGA_LOG_XML
	println("</serialLog>");
	if (res) {
		tabprintln("<result>true</result>");
	}
	else {
		testFailed();
	}
	tabprint("<message>");
	print(message);
	println("</message>");
	indent_level--;
	tabprintln("</MegaTest>");
#else
	if (res) {
		log("passed");
	}
	else {
		testFailed();
	}
	print("> ");
	log(message);
#endif
	testOpen = false;
}

/*
 * MegaTestLog::testFailed
 *
 * description: Called when a test has failed. It calls what would be common code between
 *              the two differenet endTest methods.
 *
 */
void MegaTestLog::testFailed(void) {
#ifdef MEGA_LOG_XML
	tabprintln("<result>false</result>");
#else
	log("FAILED");
#endif
	failed_tests++;
}

/*
 * MegaTestLog::conclution
 *
 * description: Should be called after the conclution of the last case. Reports the
 *              final results to the user and does some clean up.
 *
 */
void MegaTestLog::conclusion(void) {
#ifdef MEGA_LOG_XML
	tabprint("<result>");
	if (failed_cases) {
		println("false</result>");
		tabprint("<failed type=\"case\">");
		print(failed_cases);
		println("</failed>");
		tabprint("<failed type=\"test\">");
		print(total_failed_tests);
		println("</failed>");
	}
	else {
		println("true</result>");
	}
	println("</MegaTestResults>");
	indent_level--;
#else
	if (failed_cases) {
		print("FAILED: ");
		print(failed_cases);
		println(" cases");
	}
	else {
		println("Passed");
	}
#endif
}

//Copied from Arduino//////////////////////////////////////////////

void MegaTestLog::printNumber(unsigned long n, uint8_t base) {
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    unsigned long m = n;
    n /= base;
    char c = m - base * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  print(str);
}

void MegaTestLog::printFloat(double number, uint8_t digits) 
{ 
  //size_t n = 0;
  
  if (isnan(number)) return print("nan");
  if (isinf(number)) return print("inf");
  if (number > 4294967040.0) return print ("ovf");  // constant determined empirically
  if (number <-4294967040.0) return print ("ovf");  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0)
  {
     //n += 
  	 print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  //n += 
  printNumber(int_part, 10);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    //n += 
    print(".");
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    //n += 
    print(toPrint);
    remainder -= toPrint; 
  } 
  
  //return n;
}

} //namespace

MegaTest::MegaTestLog megatestlog;