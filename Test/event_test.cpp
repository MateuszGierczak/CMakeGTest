#include <gtest/gtest.h>

#include "event.hpp"

namespace
{
	constexpr unsigned FIRST_EVENT_ID = 10u;
	constexpr unsigned EVENT_PAYLOAD = 5u;
}

struct event_test : ::testing::Test
{ 
	event sut { FIRST_EVENT_ID, EVENT_PAYLOAD }; 
};

TEST_F(event_test, should_get_proper_event_id)
{
	ASSERT_EQ(FIRST_EVENT_ID, sut.id());
}

TEST_F(event_test, should_throw_expeption_when_payload_doesnt_match)
{
	ASSERT_THROW(sut.payload<double>(), bad_event_payload_cast);
}

TEST_F(event_test, should_get_proper_payload_and_no_throw_exception)
{
	ASSERT_NO_THROW({
		auto payload = sut.payload<unsigned>();
		ASSERT_EQ(EVENT_PAYLOAD, payload);
	});
}