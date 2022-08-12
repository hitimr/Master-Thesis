#include "math.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

// Demonstrate some basic assertions.
TEST(Math, linspace)
{
  ASSERT_THAT(math::linspace(0., 10., 5), ElementsAre(0, 2, 4, 6, 8));
  ASSERT_THAT(math::linspace(10., 0., 5), ElementsAre(10, 8, 6, 4, 2));
  ASSERT_THAT(math::linspace(10., 0., 0), ElementsAre());
  ASSERT_THAT(math::linspace(0., 0., 0), ElementsAre());
  ASSERT_THAT(math::linspace(10., 10., 3), ElementsAre(10, 10, 10));
}