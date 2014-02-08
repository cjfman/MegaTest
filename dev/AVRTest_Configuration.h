//AVRTest_Configuration.h

// System Configuration (DO NOT EDIT) //////////////////////////////////////////////////////
#if defined __x86_64__ || defined __x86_32__ || defined __amd64__ || defined __amd32__
#define DESKTOP
#endif

// Settings for printing ///////////////////////////////////////////////////////////////////

// Define AVR_PRINT_ARDUINO if you are using an arduino and want the standard
// arduino libraries to be used for printing. Be sure to define a path to the
// arduino libraries and to link to them in your makefile if not using the 
// Arduino IDE. Define it as the serial port that should be used (i.e. Serial, Serial1).
#define AVR_PRINT_ARDUINO Serial

// Define AVR_PRINT_ADDR when you want log messages and results to be written
// to a specific address.
//#define AVR_PRINT_ADDR 0x00

// The baudrate to be used if applicable
#define AVR_PRINT_BAUD 9600


// Settings for printing formatting //////////////////////////////////////////////////////

#define AVR_LOG_HUMAN_READABLE

// Define only one pre-defined base, or define an arbirary base
// This determins the base that will be used to print unsigned integers
#define AVR_PRINT_HEX
//#define AVR_PRINT_DEC
//#define AVR_PRINT_BIN
//#define AVR_PRINT_BASE 10

#define AVR_PRINT_SIGNED_DEC	// Define this if you want all signed numbers
                             	// to print in base 10
#define AVR_FLOAT_POINTS 3 		// The number of decimal points that will be printed
#define AVR_PRINT_NL '\n' 	 	// the new line character


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
#define AVR_FLOAT_MAXULPS 100
//#define AVR_FLOAT_REL_COMPARE
#define AVR_FLOAT_MAX_REL .00001 	// The maximum relative error allowed between floats
#define AVR_FLOAT_MAX_ABS .0000001	// The maximum absolute error allowed between floats
