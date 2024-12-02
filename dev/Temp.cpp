#include "MegaTestSuite.h"

void willPass(bool* result) {
	*result = true;
	return;
}

void willFail(bool* result) {
	*result = false;
	return;
}

int main (void) {
	MegaTest::testlog.log("Starting Tests");
	getRegistrar()->runAllTests();
	return 0;
}
