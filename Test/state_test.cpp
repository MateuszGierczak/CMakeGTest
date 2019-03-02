#include <gtest/gtest.h>

#include "state.hpp"
#include "on_event_handler.hpp"

namespace
{
	constexpr std::string_view STATE_NAME = "TESTABLE";
	constexpr unsigned FIRST_EVENT_ID = 10u;
	constexpr unsigned UNEXPECTED_EVENT_ID = 20u;
}

unsigned value = 0;

struct state_test : ::testing::Test
{
	void TearDown() { value = 0; }

	static bool handler_for_first_event(unsigned) 
	{ 
		value++;
		return true;
	}

	state sut{ STATE_NAME,
			   on_event<FIRST_EVENT_ID>(&state_test::handler_for_first_event) };
};

TEST_F(state_test, should_get_proper_state_name)
{
	ASSERT_STREQ(STATE_NAME.data(), sut.name());
}

TEST_F(state_test, should_call_handler)
{
	constexpr unsigned EXPECTED_VALUE = 1u;

	sut.handle_event(FIRST_EVENT_ID);

	ASSERT_EQ(value, EXPECTED_VALUE);
}

TEST_F(state_test, should_return_true_when_event_was_consumed)
{
	bool was_event_consumed = sut.handle_event(FIRST_EVENT_ID);

	ASSERT_TRUE(was_event_consumed);
}

TEST_F(state_test, should_return_false_when_event_was_not_consumed)
{
	bool was_event_consumed = sut.handle_event(UNEXPECTED_EVENT_ID);

	ASSERT_FALSE(was_event_consumed);
}