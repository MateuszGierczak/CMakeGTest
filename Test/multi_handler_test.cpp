#include <gtest/gtest.h>

#include "multi_handler.hpp"

struct multi_handler_test : ::testing::Test
{
	void TearDown()
	{
		value = 0;
	}

	static void callable() 
	{
		value++;
	}

	static unsigned value;
};

unsigned multi_handler_test::value = 0u;

TEST_F(multi_handler_test, should_call_functions)
{
	multi_handler sut(&multi_handler_test::callable);

	sut();

	ASSERT_EQ(value, 1);
}