//AVRTestAll

#include "AVRTest.cpp"
#include "AVRTestCase.cpp"
#include "AVRTestRegistrar.cpp"
#include "AVRTestLog.cpp"
#include "AVRTestSuite.cpp"

int main (void) {
	avrtestlog.log("Starting Tests");
	AVRTest::getRegistrar()->runAllTests();
	return 0;
}