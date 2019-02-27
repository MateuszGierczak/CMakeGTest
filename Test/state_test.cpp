#include <gtest/gtest.h>

#include "state.hpp"

struct state_test : ::testing::Test
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

unsigned state_test::value = 0u;

TEST_F(state_test, should_get_proper_state_name)
{
	state sut{ "idle",
			   &state_test::callable };

	sut.handle_event(10);

	ASSERT_EQ(1, 10000);
}