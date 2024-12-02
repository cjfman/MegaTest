#include "MegaTestSuite.h"

MEGATEST_CASE(SampleCase)

MEGATEST_TEST(SampleTest) {
  ASSERT_TRUE(1 + 1 == 2)
}

ENDCASE
