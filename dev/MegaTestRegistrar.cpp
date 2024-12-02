// AVRTestRegistrar

#include <string.h>
#include <stdlib.h>
#include "AVRTestRegistrar.h"
#include "AVRTestCase.h"
#include "AVRTest.h"
#include "AVRTestLog.h"

namespace AVRTest {

AVRTestRegistrar::AVRTestRegistrar() {
}

AVRTestRegistrar::~AVRTestRegistrar() {
}

void AVRTestRegistrar::runAllTests(void) {
	// Runs every registered case
	if (caseOpen) {
		submitCase();
	}
	for (unsigned int i = 0; i < testCases.size(); i++) {
		AVRTestCase testcase = testCases[i];
		avrtestlog.startCase(testcase.getTitle());
		bool res = testcase.runTests();
		avrtestlog.endCase(res);
	}
	avrtestlog.conclusion();
}

int AVRTestRegistrar::newCase(const char* title) {
	// Starts the registration of a new case
	if (caseOpen) {
		submitCase();
	}
	currentCase = AVRTestCase(title);
	caseOpen = true;
	return testCases.size();
}

int AVRTestRegistrar::newTest(AVRTest* test) {
	// Register a new test with the currently open case. If a case
	// is not open, open a new case. Technically, this behavior is
	// undefined, but I captured this case anyway.
	if (!caseOpen) {
		this->newCase("UNNAMED_AVRTESTCASE");
	}
	currentCase.addTest(test);
	return numberOfTests++;
}

int AVRTestRegistrar::submitCase() {
	// Complete the registration of a case and add it to the
	// list of cases.
	if (caseOpen) {
		testCases.push_back(currentCase);
		caseOpen = false;
	}
	return 0;
}


AVRTestRegistrar* getRegistrar(void) {
	// Keeps a statically declared copy of the global registrar
	// AVR-GCC seems to have trouble initializing static variables with
	// anything other than a litteral. To work around this, I initialize
	// a pointer to 0. This is followed by a conditional that allocates
	// and initializes an AVRTestRegistrar object.
	static AVRTestRegistrar *registrar = 0;
	if (!registrar) {
		registrar = (AVRTestRegistrar*)malloc(sizeof(AVRTestRegistrar));
		*registrar = AVRTestRegistrar();
	}
	return registrar;
}

} // namespace