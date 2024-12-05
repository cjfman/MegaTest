// MegaTestLog

#ifndef MEGATESTLOG_h
#define MEGATESTLOG_h

#include <inttypes.h>
#include "MegaTest_Configuration.hpp"

#ifndef AVR_PRINT_BASE
	#ifdef AVR_PRINT_BIN
		#define AVR_PRINT_BASE 2
	#endif
	#ifdef AVR_PRINT_DEC
		#define AVR_PRINT_BASE 10
	#endif
	#ifdef AVR_PRINT_HEX
		#define AVR_PRINT_BASE 16
	#endif
	#ifndef AVR_PRINT_BASE
		#define AVR_PRINT_BASE 10
	#endif
#endif // AVR_PRINT_BASE

namespace MegaTest {

class MegaTestLog {
	bool caseOpen;
	bool testOpen;
	uint16_t failed_cases;
	uint16_t failed_tests;

public:
	MegaTestLog();
	void print(char c);
	void print(const char* message);
	void print(unsigned char c);
	void print(int i);
	void print(unsigned int i);
	void print(long l);
	void print(unsigned long l);
	void print(double d);
	void log(const char* message);
	void nl(void);
	
	//Test Result Log Methods
	void startCase(const char*);
	void endCase(bool);
	void startTest(const char*);
	void endTest(bool);
	void endTest(bool, const char*);
	void testFailed(void);
	template<typename T>
	void expected(T ex, T ac);
	template<typename T>
	void expected(const char* var, T ex, T ac);
	void conclusion(void);

private:
	//void write(char c);
	//void write(const char* message);
	// Copied From Arduino
	void printNumber(unsigned long, uint8_t);
    void printFloat(double, uint8_t);
};

template<typename T>
void MegaTestLog::expected(T ex, T ac) {
	testFailed();
	print("> Expected: ");
	print(ex);
	print("; Actual: ");
	print(ac);
	nl();
	testOpen = false;
}

template<typename T>
void MegaTestLog::expected(const char* var, T ex, T ac) {
	testFailed();
	print("> ");
	print(var);
	print("; Expected: ");
	print(ex);
	print("; Actual: ");
	print(ac);
	nl();
	testOpen = false;
}

} // namespace

extern MegaTest::MegaTestLog megatestlog;

#endif // Whole File
