#pragma once

#include "event_type_traits.hpp"

constexpr unsigned DUMMY_EVENT_PAYLOAD_VALUE = 101u;

struct DummyEvent
{
    unsigned value{ DUMMY_EVENT_PAYLOAD_VALUE };
};

constexpr unsigned DUMMY_EVENT_ID = 1u;

template<>
struct event_type_traits<DummyEvent>
{
    constexpr static unsigned id = DUMMY_EVENT_ID;
};