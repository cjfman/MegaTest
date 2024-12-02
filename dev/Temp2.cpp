#include "MegaTestSuite.h"

MEGATEST_CASE(BooleanCase)

MEGATEST(TrueExpTrue) {
	ASSERT_TRUE(true);
}

MEGATEST(TrueVarExpFalse) {
	bool var = true;
	ASSERT_FALSE(var);
}

MEGATEST(TrueExpFalse) {
	ASSERT_FALSE(true);
}

ENDCASE


MEGATEST_CASE(FloatCase)

MEGATEST(FloatEqual) {
	ASSERT_FLOAT_EQUAL(1.2, 1.2);
}

MEGATEST(FloatNEqual) {
	ASSERT_FLOAT_EQUAL(1.2, 1.200003);	// Should pass
	ASSERT_FLOAT_EQUAL(1.2, 1.2001);	// Should Fail with current settings
}

ENDCASE

MEGATEST_CASE(Equality)

MEGATEST(Same) {
	ASSERT_EQUAL(3, 3);
}

MEGATEST(Different) {
	ASSERT_EQUAL(3, 4);
}

MEGATEST(ShouldBeDifferent) {
	ASSERT_NEQUAL(4, 4);
}

MEGATEST(ShouldBeDifferentAndAreDiff) {
	ASSERT_NEQUAL(4, 5);
}

ENDCASE


MEGATEST_CASE(StringEquality)

MEGATEST(StringsAreSame) {
	ASSERT_STREQUAL("Hello", "Hello");
}

MEGATEST(StringsAreDifferent) {
	ASSERT_STRNEQUAL("Marco", "Polo");
}

MEGATEST(SringsWillFail) {
	const char *controller = "8051";
	ASSERT_STREQUAL(controller, "AVR");
}

ENDCASE

//*
class OceanFixture : public MegaTestFixture {
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


MEGATEST_CASE(OceanCase)

MEGATESTFIX(favoriteOcean, OceanFixture) {
	ASSERT_STREQUAL(oceans[0], "Atlantic");
}

MEGATESTFIX(oceanFail, OceanFixture) {
	ASSERT_STREQUAL(oceans[1], "Artic");
}

ENDCASE
//*/