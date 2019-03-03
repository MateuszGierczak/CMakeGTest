#include <gtest/gtest.h>

#include "on_event_handler.hpp"

namespace
{
	constexpr unsigned FIRST_EVENT_ID = 10u;
	constexpr unsigned SECOND_EVENT_ID = 15u;
	constexpr unsigned UNEXPECTED_EVENT_ID = 20u;
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

TEST_F(on_event_handler_test, should_call_handler_when_event_id_matched)
{
	constexpr unsigned EXPECTED_VALUE = 1u;

	auto sut = on_event<FIRST_EVENT_ID>(&on_event_handler_test::callable);

	sut(FIRST_EVENT_ID);

	ASSERT_EQ(EXPECTED_VALUE, on_event_handler_test::value);
}

TEST_F(on_event_handler_test, should_call_single_handler_for_multi_event_ids)
{
	constexpr unsigned EXPECTED_VALUE = 2u;

	auto sut = on_event<FIRST_EVENT_ID, SECOND_EVENT_ID>(&on_event_handler_test::callable);

	ASSERT_TRUE(sut(FIRST_EVENT_ID));
	ASSERT_TRUE(sut(SECOND_EVENT_ID));

	ASSERT_EQ(EXPECTED_VALUE, value);
}

TEST_F(on_event_handler_test, should_return_false_when_event_doesnt_consumed)
{
	auto sut = on_event<FIRST_EVENT_ID, SECOND_EVENT_ID>(&on_event_handler_test::callable);

	bool was_event_consumed = sut(UNEXPECTED_EVENT_ID);

	ASSERT_FALSE(was_event_consumed);
}