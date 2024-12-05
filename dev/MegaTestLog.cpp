// MegaTestLog

#include <inttypes.h>
#include <math.h>
#include <string.h>
#include "MegaTestLog.hpp"
#include "MegaTest_Configuration.hpp"

#ifdef DESKTOP
	#include <iostream>
	using std::cout;
#else
#ifdef AVR_PRINT_ARDUINO
#include <HardwareSerial.cpp>
#endif
#endif // DESKTOP

#define EOL '\n'

namespace MegaTest {

MegaTestLog::MegaTestLog() {
	testOpen = false;
	caseOpen = false;
	failed_cases = 0;
	failed_tests = 0;
#ifndef DESKTOP
#ifdef AVR_PRINT_ARDUINO
	AVR_PRINT_ARDUINO.begin(AVR_PRINT_BAUD);
#endif
#endif // DESKTOP
}

void MegaTestLog::print(char c) {
#ifdef DESKTOP
	cout << c;
#else
#ifdef AVR_PRINT_ARDUINO
	AVR_PRINT_ARDUINO.print(c);
#else
#error "Must define either DESKTOP or AVR_PRINT_ARDUINO"
#endif // AVR_PRINT_ARDUINO
#endif // DESKTOP
}

void MegaTestLog::print(const char* message) {
#ifdef DESKTOP
	cout << message;
#elif defined AVR_PRINT_ARDUINO
	AVR_PRINT_ARDUINO.print(message);
#else
	size_t len = strlen(message);
	for (unsigned int i = 0; i < len; i++) {
		print(message[i]);
	}
#endif
}

void MegaTestLog::print(unsigned char c) {
	print((unsigned long) c);
}

void MegaTestLog::print(int i) {
	print((long) i);
}

void MegaTestLog::print(unsigned i) {
	print((unsigned long) i);
}

void MegaTestLog::print(long l) {
#ifdef AVR_PRINT_SIGNED_DEC
	if (l < 0) {
		print('-');
	}
	printNumber(l, 10);
#else
	printNumber(l, AVR_PRINT_BASE));
#endif
}

void MegaTestLog::print(unsigned long l) {
	printNumber(l, AVR_PRINT_BASE);
}

void MegaTestLog::print(double d) {
	printFloat(d, AVR_FLOAT_POINTS);
}

void MegaTestLog::log(const char* message) {
	print(message);
	print(AVR_PRINT_NL);
}

void MegaTestLog::nl(void) {
	print(AVR_PRINT_NL);
}


//Test Result Log Methods///////////////////////////////

void MegaTestLog::startCase(const char* name) {
	if (caseOpen) {
		nl();
	}
	caseOpen = true;
	log(name);
}

void MegaTestLog::endCase(bool res) {
	if (!caseOpen) return;
	if (res) {
		log("Case Passed");
	}
	else {
		print("Case Failed: ");
		print(failed_tests);
		log(" tests");
		failed_tests = 0;
		failed_cases++;
	}
	caseOpen = false;
	nl();
}

void MegaTestLog::startTest(const char* name) {
	print(name);
	int dots = 32 - strlen(name);
	dots = (dots > 3) ? dots : 3;
	for (int i = 0; i < dots; i++) {
		print('.');
	}
	testOpen = true;
}

void MegaTestLog::endTest(bool res) {
	if (!testOpen) return;
	if (res) {
		log("passed");
	}
	else {
		testFailed();
	}
	testOpen = false;
}

void MegaTestLog::endTest(bool res, const char* message) {
	if (!testOpen) return;
	if (res) {
		log("passed");
	}
	else {
		testFailed();
	}
	print("> ");
	log(message);
	testOpen = false;
}

void MegaTestLog::testFailed(void) {
	log("FAILED");
	failed_tests++;
}

void MegaTestLog::conclusion(void) {
	if (failed_cases) {
		print("FAILED: ");
		print(failed_cases);
		log(" cases");
	}
	else {
		log("Passed");
	}
}

//private//////////////////////////////////////////////

/*
void MegaTestLog::write(char c) {
#ifdef DESKTOP
	cout << c;
#endif
}

void MegaTestLog::write(const char* message) {
#ifdef DESKTOP
	cout << message;
#endif
}
//*/

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
  print(int_part);

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
