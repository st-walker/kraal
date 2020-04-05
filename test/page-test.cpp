#include "gtest/gtest.h"


class PageTest: public ::testing::Test {


};

TEST_F(PageTest, OneEqualsOne) {
  // ASSERT_THAT(1, testing::Eq(1));
  ASSERT_EQ(1, 1);
}
