#include <gtest/gtest.h>

#include "state.hpp"
#include "on_event_hadler.hpp"

namespace
{
	constexpr std::string_view STATE_NAME = "TESTABLE";
	constexpr unsigned DUMMY_EVENT = 10u;
}

unsigned value = 0;

struct state_test : ::testing::Test
{
	void TearDown() { value = 0; }

	static bool callable(unsigned) 
	{ 
		value++;
		return true;
	}

	state sut{ STATE_NAME,
			   on_event(&state_test::callable) };
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

TEST_F(state_test, should_return_true_when_event_was_consumed)
{
	bool was_event_consumed = sut.handle_event(DUMMY_EVENT);

	ASSERT_TRUE(was_event_consumed);
}