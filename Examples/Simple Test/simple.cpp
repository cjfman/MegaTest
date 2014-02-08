#include <MegaTestSuite.h>

MEGA_CASE(example_case)

MEGA_TEST(example_test) {
	ASSERT_TRUE(1 + 1 == 2);
}

ENDCASE
