#include <gtest/gtest.h>

#include "on_event_handler.hpp"

namespace
{
	constexpr unsigned FIRST_EVENT_ID = 10u;
	constexpr unsigned SECOND_EVENT_ID = 15u;
}

struct on_event_handler_test : ::testing::Test
{
	void TearDown() { value = 0; }

	static bool callable(unsigned) 
	{
		value++;
		return true;
	}

	static unsigned value;
};

unsigned on_event_handler_test::value = 0;


TEST_F(on_event_handler_test, should_call_handler_for_multiple_events)
{
	constexpr unsigned EXPECTED_VALUE = 2u;

	auto sut = on_event<FIRST_EVENT_ID, SECOND_EVENT_ID>(&on_event_handler_test::callable);

	sut(FIRST_EVENT_ID);
	sut(SECOND_EVENT_ID);

	ASSERT_EQ(EXPECTED_VALUE, value);
}