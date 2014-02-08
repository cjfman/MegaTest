#include "AVRTestSuite.h"

void willPass(bool* result) {
	*result = true;
	return;
}

void willFail(bool* result) {
	*result = false;
	return;
}

int main (void) {
	AVRTest::testlog.log("Starting Tests");
	getRegistrar()->runAllTests();
	return 0;
}
