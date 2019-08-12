#include <gtest/gtest.h>

#include "on_event_handler.hpp"

#include "DummyEvent.hpp"
#include "UnexpectedEvent.hpp"

struct event_handler_test : ::testing::Test
{ 
    static void on_dummy_event_handler(const DummyEvent&) { }

    on_event_handler<DummyEvent> sut{ on_event(&event_handler_test::on_dummy_event_handler) };
};

TEST_F(event_handler_test, eventWithRegisteredHandlerShouldBeProcessed)
{
    event event { DummyEvent{} };
    bool was_event_be_processed = sut.handle_event(event);

    ASSERT_TRUE(was_event_be_processed);
}

TEST_F(event_handler_test, unexpectedEventShouldNotBeProcessed)
{
    event event { UnexpectedEvent{} };
    bool was_event_be_processed = sut.handle_event(event);

    ASSERT_FALSE(was_event_be_processed);
}