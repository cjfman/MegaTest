#include "AVRTestSuite.h"

AVRTEST_CASE(BooleanCase)

AVRTEST(TrueExpTrue) {
	ASSERT_TRUE(true);
}

AVRTEST(TrueVarExpFalse) {
	bool var = true;
	ASSERT_FALSE(var);
}

AVRTEST(TrueExpFalse) {
	ASSERT_FALSE(true);
}

ENDCASE


AVRTEST_CASE(FloatCase)

AVRTEST(FloatEqual) {
	ASSERT_FLOAT_EQUAL(1.2, 1.2);
}

AVRTEST(FloatNEqual) {
	ASSERT_FLOAT_EQUAL(1.2, 1.200003);	// Should pass
	ASSERT_FLOAT_EQUAL(1.2, 1.2001);	// Should Fail with current settings
}

ENDCASE

AVRTEST_CASE(Equality)

AVRTEST(Same) {
	ASSERT_EQUAL(3, 3);
}

AVRTEST(Different) {
	ASSERT_EQUAL(3, 4);
}

AVRTEST(ShouldBeDifferent) {
	ASSERT_NEQUAL(4, 4);
}

AVRTEST(ShouldBeDifferentAndAreDiff) {
	ASSERT_NEQUAL(4, 5);
}

ENDCASE


AVRTEST_CASE(StringEquality)

AVRTEST(StringsAreSame) {
	ASSERT_STREQUAL("Hello", "Hello");
}

AVRTEST(StringsAreDifferent) {
	ASSERT_STRNEQUAL("Marco", "Polo");
}

AVRTEST(SringsWillFail) {
	const char *controller = "8051";
	ASSERT_STREQUAL(controller, "AVR");
}

ENDCASE

//*
class OceanFixture : public AVRTestFixture {
protected:
	const char* oceans[4];

private:
//public:
	void setup(void) {
		oceans[0] = "Atlantic";
		oceans[1] = "Pacific";
		oceans[2] = "Indian";
		oceans[3] = "Artic";
	};

	void teardown(void) {

	};
};


AVRTEST_CASE(OceanCase)

AVRTESTFIX(favoriteOcean, OceanFixture) {
	ASSERT_STREQUAL(oceans[0], "Atlantic");
}

AVRTESTFIX(oceanFail, OceanFixture) {
	ASSERT_STREQUAL(oceans[1], "Artic");
}

ENDCASE
//*/