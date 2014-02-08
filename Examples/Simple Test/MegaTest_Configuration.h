//MEGATest_Configuration.h

// System Configuration (DO NOT EDIT) //////////////////////////////////////////////////////
#if defined __x86_64__ || defined __x86_32__ || defined __amd64__ || defined __amd32__
#define DESKTOP
#endif

// General Settings ////////////////////////////////////////////////////////////////////////

// The maximum number of tests per test case as well as the maximum number of test cases
// There has been trouble defining this number to be larger than 53. If not defined,
// dynamic test allocation will be used and the limit will be 2^16. NOTE: Dynamic test
// allocation requires a linking to a funtioning version of malloc() and having sufficien
// memory.
#define MEGA_MAX_TESTS 24


// Define ARDUINO_LIBS if you have linked to any of the arduino libraries
#define ARDUINO_LIBS

// Serial Communication ///////////////////////////////////////////////////////////////////

// The baudrate to be used if applicable
#define MEGA_PRINT_BAUD 9600

// Define MEGA_PRINT_ARDUINO if you are using an arduino and want the standard
// arduino libraries to be used for printing. Be sure to define a path to the
// arduino libraries and to link to them in your makefile if not using the 
// Arduino IDE. Define it as the serial port that should be used (i.e. Serial, Serial1).
#define MEGA_PRINT_ARDUINO Serial

// Define MEGA_PRINT_ADDR when you want log messages and results to be written
// to a specific address.
//#define MEGA_PRINT_ADDR 0x00

// Define MEGA_PRINT_USER_DEFINED to define your own printing functions
// The following functions need to be defined with your tests. They are protoyped below.
//#define MEGA_PRINT_USER_DEFINED
#ifdef MEGA_PRINT_USER_DEFINED
//#define MEGA_PRINT_USER_DEFINED_STRING 	// Define this if c string printing should custom
void mega_print_user_setup(void);		// Called once before the first print
void mega_print_user_sendchar(char c);	// Called to send a character
#ifdef MEGA_PRINT_USER_DEFINED_STRING
mega_print_user_sendstring(const char* c);
#endif
#endif // MEGA_PRINT_USER_DEFINED

// Printing Formatting ////////////////////////////////////////////////////////////////////

// The format that should be printed
#define MEGA_LOG_HUMAN_READABLE
//#define MEGA_LOG_XML

#ifdef MEGA_LOG_XML
#define MEGA_LOG_TAB_CHAR "    "
#endif

// Define only one pre-defined base, or define an arbirary base
// This determins the base that will be used to print unsigned integers
//#define MEGA_PRINT_HEX
#define MEGA_PRINT_DEC
//#define MEGA_PRINT_BIN
//#define MEGA_PRINT_BASE 10

#define MEGA_PRINT_SIGNED_DEC	// Define this if you want all signed numbers
                             	// to print in base 10
#define MEGA_FLOAT_POINTS 4 		// The number of decimal points that will be printed
#define MEGA_PRINT_NL '\n' 	 	// the new line character


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
//#define MEGA_FLOAT_MAXULPS 100
#define MEGA_FLOAT_REL_COMPARE

#define MEGA_FLOAT_MAX_REL .00001 	// The maximum relative error allowed between floats
#define MEGA_FLOAT_MAX_ABS .001		// The maximum absolute error allowed between floats

// Custom Printing /////////////////////////////////////////////////////////////////////////

// Define MEGATestCustomePrint to turn on the ability to write custom printing methods for
// for classes. Enabling this option may cause some standard types not to print properly.
//#define MEGATestCustomPrint

// Use this section to declare methods to print your custome objects and classes