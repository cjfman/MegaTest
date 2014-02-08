//MegaTest_Default_Configuration.h

//#include <MegaTest_Configuration.h>
#ifdef MEGA_TEST_CONFIGURATION_FILE
	#define MEGA_TEST_CONFIGURATION <MEGA_TEST_CONFIGURATION_FILE>
	#include MEGA_TEST_CONFIGURATION
#endif

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
#ifndef MEGA_MAX_TESTS
//	#define MEGA_MAX_TESTS 24
#endif

#ifndef MEGA_TEST_MAX_TITLE_LENGTH
//	#define MEGA_TEST_MAX_TITLE_LENGTH 24
#endif

// Define ARDUINO_IDE if you plan on programming your device with the ARDUINO_IDE
// If you do use the Arduino IDE, it is highly suggested that you also define
// MEGA_PRINT_ARDUINO. See below for details.
#ifndef ARDUINO_IDE
//	#define ARDUINO_IDE
#endif


// Define ARDUINO_LIBS if you have linked to any of the arduino libraries
#ifndef ARDUINO_LIBS
//	#define ARDUINO_LIBS
#endif

#ifdef ARDUINO_LIBS
	#define ARDUINO_INIT
#endif

// Settings for printing ///////////////////////////////////////////////////////////////////

// Define MEGA_PRINT_ARDUINO if you are using an arduino and want the standard
// arduino libraries to be used for printing. Be sure to define a path to the
// arduino libraries and to link to them in your makefile if not using the 
// Arduino IDE. Define it as the serial port that should be used (i.e. Serial, Serial1).
#if !defined(MEGA_PRINT_ARDUINO) && !defined(MEGA_PRINT_ADDR) && !defined(MEGA_PRINT_USER_DEFINED)
	#define MEGA_PRINT_ARDUINO Serial
//	#define MEGA_PRINT_ADDR 0x00
#endif

// Define MEGA_PRINT_ADDR when you want log messages and results to be written
// to a specific address.

// The baudrate to be used if applicable
#ifndef MEGA_PRINT_BAUD
	#define MEGA_PRINT_BAUD 9600
#endif

// Printing Formatting ////////////////////////////////////////////////////////////////////

// The format that should be printed
#if !defined(MEGA_LOG_HUMAN_READABLE) && !defined(MEGA_LOG_XML)
	#define MEGA_LOG_HUMAN_READABLE
//	#define MEGA_LOG_XML
#endif

#ifndef MEGA_LOG_TAB_CHAR
	#define MEGA_LOG_TAB_CHAR "    "
#endif

#ifdef MEGA_PRINT_USER_DEFINED
//#define MEGA_PRINT_USER_DEFINED_STRING 	// Define this if c string printing should custom
void mega_print_user_setup(void);		// Called once before the first print
void mega_print_user_sendchar(char c);	// Called to send a character
	#ifdef MEGA_PRINT_USER_DEFINED_STRING
mega_print_user_sendstring(const char* c);
	#endif
#endif // MEGA_PRINT_USER_DEFINED

// Define only one pre-defined base, or define an arbirary base
// This determins the base that will be used to print unsigned integers
#ifndef MEGA_PRINT_BASE
	#ifdef MEGA_PRINT_BIN
		#define MEGA_PRINT_BASE 2
	#elif defined MEGA_PRINT_DEC
		#define MEGA_PRINT_BASE 10
	#elif defined MEGA_PRINT_HEX
		#define MEGA_PRINT_BASE 16
	#else
		#define MEGA_PRINT_BASE 10
	#endif
#endif // MEGA_PRINT_BASE

#ifndef MEGA_FLOAT_POINTS
	#define MEGA_FLOAT_POINTS 4 		// The number of decimal points that will be printed
#endif

#ifndef MEGA_PRINT_NL
	#define MEGA_PRINT_NL '\n' 	 	// the new line character
#endif


// Floating Point Settings ///////////////////////////////////////////////////////////////

// There are two types of floating point comparisons that are supported.
// Define MEGA_FLOAT MAXULPS to compare floats by comparing
// the number of representable floats consecutively between
// the two.
// Define MEGA_FLOAT_REL_COMPARE to compare floats by comparing 
// the relative and absolute difference. The result will be true 
// if either method determins the numbers to be equal. 
// This is not recomended because it uses division.
// Define neither to do a direct comparison. This is not advised as floating point
// arithmatic is not precise
#ifndef MEGA_FLOAT_REL_COMPARE
	#ifndef MEGA_FLOAT_MAXULPS
		#define MEGA_FLOAT_MAXULPS 100
	#endif
#endif

#ifndef MEGA_FLOAT_MAX_REL
	#define MEGA_FLOAT_MAX_REL .00001 	// The maximum relative error allowed between floats
#endif
#ifndef MEGA_FLOAT_MAX_ABS
	#define MEGA_FLOAT_MAX_ABS .000001		// The maximum absolute error allowed between floats
#endif