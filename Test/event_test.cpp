#include <gtest/gtest.h>

#include "event.hpp"

#include "DummyEvent.hpp"

struct event_test : ::testing::Test
{ 
    event sut { DummyEvent{} };
};

TEST_F(event_test, should_get_proper_event_id)
{
	ASSERT_EQ(DUMMY_EVENT_ID, sut.id());
}

TEST_F(event_test, should_throw_expeption_when_payload_doesnt_match)
{
	ASSERT_THROW(sut.payload<double>(), event_payload_bad_cast);
}

TEST_F(event_test, should_get_proper_payload_and_no_throw_exception)
{
	ASSERT_NO_THROW({
		const auto& payload = sut.payload<DummyEvent>();
		ASSERT_EQ(DUMMY_EVENT_PAYLOAD_VALUE, payload.value);
	});
}