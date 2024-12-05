// MegaTestRegistrar

#include <string.h>
#include <stdlib.h>
#include "MegaTestRegistrar.hpp"
#include "MegaTestCase.hpp"
#include "MegaTest.hpp"
#include "MegaTestLog.hpp"

namespace MegaTest {

MegaTestRegistrar::MegaTestRegistrar() {
}

MegaTestRegistrar::~MegaTestRegistrar() {
}

void MegaTestRegistrar::runAllTests(void) {
	// Runs every registered case
	if (caseOpen) {
		submitCase();
	}
	for (unsigned int i = 0; i < testCases.size(); i++) {
		MegaTestCase testcase = testCases[i];
		megatestlog.startCase(testcase.getTitle());
		bool res = testcase.runTests();
		megatestlog.endCase(res);
	}
	megatestlog.conclusion();
}

int MegaTestRegistrar::newCase(const char* title) {
	// Starts the registration of a new case
	if (caseOpen) {
		submitCase();
	}
	currentCase = MegaTestCase(title);
	caseOpen = true;
	return testCases.size();
}

int MegaTestRegistrar::newTest(MegaTest* test) {
	// Register a new test with the currently open case. If a case
	// is not open, open a new case. Technically, this behavior is
	// undefined, but I captured this case anyway.
	if (!caseOpen) {
		this->newCase("UNNAMED_MEGATESTCASE");
	}
	currentCase.addTest(test);
	return numberOfTests++;
}

int MegaTestRegistrar::submitCase() {
	// Complete the registration of a case and add it to the
	// list of cases.
	if (caseOpen) {
		testCases.push_back(currentCase);
		caseOpen = false;
	}
	return 0;
}


MegaTestRegistrar* getRegistrar(void) {
	// Keeps a statically declared copy of the global registrar
	// AVR-GCC seems to have trouble initializing static variables with
	// anything other than a litteral. To work around this, I initialize
	// a pointer to 0. This is followed by a conditional that allocates
	// and initializes an MegaTestRegistrar object.
	static MegaTestRegistrar *registrar = 0;
	if (!registrar) {
		registrar = (MegaTestRegistrar*)malloc(sizeof(MegaTestRegistrar));
		*registrar = MegaTestRegistrar();
	}
	return registrar;
}

} // namespace
