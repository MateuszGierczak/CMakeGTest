#include <gtest/gtest.h>

#include "sum.hpp"

struct TestSuite : ::testing::Test
{};

TEST_F(TestSuite, shouldGetProperSum)
{
	ASSERT_EQ(2, sum(1, 3));
}