//MegaTestAll

#include "MegaTestRegistrar.hpp"

int main (void) {
	megatestlog.log("Starting Tests");
	MegaTest::getRegistrar()->runAllTests();
	return 0;
}
