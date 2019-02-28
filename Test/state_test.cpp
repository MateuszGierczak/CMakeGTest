#include <gtest/gtest.h>

#include "state.hpp"

namespace
{
	constexpr std::string_view STATE_NAME = "TESTABLE";
	constexpr unsigned DUMMY_EVENT = 10u;
}

unsigned value = 0;

struct state_test : ::testing::Test
{
	void TearDown() { value = 0; }

	static void callable(unsigned) { value++; }

	state sut{ STATE_NAME,
			   &state_test::callable };
};

TEST_F(state_test, should_get_proper_state_name)
{
	ASSERT_STREQ(STATE_NAME.data(), sut.name());
}

TEST_F(state_test, should_call_handler)
{
	constexpr unsigned EXPECTED_VALUE = 1u;

	sut.handle_event(DUMMY_EVENT);

	ASSERT_EQ(value, EXPECTED_VALUE);
}