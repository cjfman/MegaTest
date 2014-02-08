//AVRTest_Default_Configuration.h

#include <AVRTest_Configuration.h>

// System Configuration (DO NOT EDIT) //////////////////////////////////////////////////////
#if defined __x86_64__ || defined __x86_32__ || defined __amd64__ || defined __amd32__
	#ifndef DESKTOP
		#define DESKTOP
	#endif
#endif



// General Settings ////////////////////////////////////////////////////////////////////////

// The maximum number of tests per test case as well as the maximum number of test cases
// There has been trouble defining this number to be larger than 53. If not defined,
// dynamic test allocation will be used and the limit will be 2^16. NOTE: Dynamic test
// allocation requires a linking to a funtioning version of malloc() and having sufficien
// memory.
#ifndef AVR_MAX_TESTS
//	#define AVR_MAX_TESTS 24
#endif

#ifndef AVRTEST_MAX_TITLE_LENGTH
//	#define AVRTEST_MAX_TITLE_LENGTH 24
#endif

// Define ARDUINO_IDE if you plan on programming your device with the ARDUINO_IDE
// If you do use the Arduino IDE, it is highly suggested that you also define
// AVR_PRINT_ARDUINO. See below for details.
#ifndef ARDUINO_IDE
	#define ARDUINO_IDE
#endif


// Define ARDUINO_LIBS if you have linked to any of the arduino libraries
#ifndef ARDUINO_LIBS
//	#define ARDUINO_LIBS
#endif

#ifdef ARDUINO_LIBS
	#define ARDUINO_INIT
#endif

// Settings for printing ///////////////////////////////////////////////////////////////////

// Define AVR_PRINT_ARDUINO if you are using an arduino and want the standard
// arduino libraries to be used for printing. Be sure to define a path to the
// arduino libraries and to link to them in your makefile if not using the 
// Arduino IDE. Define it as the serial port that should be used (i.e. Serial, Serial1).
#if !defined(AVR_PRINT_ARDUINO) && !defined(AVR_PRINT_ADDR) && !defined(AVR_PRINT_USER_DEFINED)
	#define AVR_PRINT_ARDUINO Serial
//	#define AVR_PRINT_ADDR 0x00
#endif

// Define AVR_PRINT_ADDR when you want log messages and results to be written
// to a specific address.

// The baudrate to be used if applicable
#ifndef AVR_PRINT_BAUD
	#define AVR_PRINT_BAUD 9600
#endif

// Printing Formatting ////////////////////////////////////////////////////////////////////

// The format that should be printed
#if !defined(AVR_LOG_HUMAN_READABLE) && !defined(AVR_LOG_XML)
	#define AVR_LOG_HUMAN_READABLE
//	#define AVR_LOG_XML
#endif

#ifndef AVR_LOG_TAB_CHAR
	#define AVR_LOG_TAB_CHAR "    "
#endif

#ifdef AVR_PRINT_USER_DEFINED
//#define AVR_PRINT_USER_DEFINED_STRING 	// Define this if c string printing should custom
void avr_print_user_setup(void);		// Called once before the first print
void avr_print_user_sendchar(char c);	// Called to send a character
	#ifdef AVR_PRINT_USER_DEFINED_STRING
avr_print_user_sendstring(const char* c);
	#endif
#endif // AVR_PRINT_USER_DEFINED

// Define only one pre-defined base, or define an arbirary base
// This determins the base that will be used to print unsigned integers
#ifndef AVR_PRINT_BASE
	#ifdef AVR_PRINT_BIN
		#define AVR_PRINT_BASE 2
	#elif defined AVR_PRINT_DEC
		#define AVR_PRINT_BASE 10
	#elif defined AVR_PRINT_HEX
		#define AVR_PRINT_BASE 16
	#else
		#define AVR_PRINT_BASE 10
	#endif
#endif // AVR_PRINT_BASE

#ifndef AVR_FLOAT_POINTS
	#define AVR_FLOAT_POINTS 4 		// The number of decimal points that will be printed
#endif

#ifndef AVR_PRINT_NL
	#define AVR_PRINT_NL '\n' 	 	// the new line character
#endif


// Floating Point Settings ///////////////////////////////////////////////////////////////

// There are two types of floating point comparisons that are supported.
// Define AVR_FLOAT MAXULPS to compare floats by comparing
// the number of representable floats consecutively between
// the two.
// Define AVR_FLOAT_REL_COMPARE to compare floats by comparing 
// the relative and absolute difference. The result will be true 
// if either method determins the numbers to be equal. 
// This is not recomended because it uses division.
// Define neither to do a direct comparison. This is not advised as floating point
// arithmatic is not precise
#ifndef AVR_FLOAT_REL_COMPARE
	#ifndef AVR_FLOAT_MAXULPS
		#define AVR_FLOAT_MAXULPS 100
	#endif
#endif

#ifndef AVR_FLOAT_MAX_REL
	#define AVR_FLOAT_MAX_REL .00001 	// The maximum relative error allowed between floats
#endif
#ifndef AVR_FLOAT_MAX_ABS
	#define AVR_FLOAT_MAX_ABS .000001		// The maximum absolute error allowed between floats
#endif
