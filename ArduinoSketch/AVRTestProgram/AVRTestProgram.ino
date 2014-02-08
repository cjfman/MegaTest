#include "AVRTestSuite.h"

AVRTEST_CASE(SampleCase)

AVRTEST_TEST(SampleTest) {
  ASSERT_TRUE(1 + 1 == 2)
}

ENDCASE
