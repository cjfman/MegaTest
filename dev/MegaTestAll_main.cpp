//MegaTestAll

#include "MegaTest.cpp"
#include "MegaTestCase.cpp"
#include "MegaTestRegistrar.cpp"
#include "MegaTestLog.cpp"
#include "MegaTestSuite.cpp"

int main (void) {
	avrtestlog.log("Starting Tests");
	MegaTest::getRegistrar()->runAllTests();
	return 0;
}