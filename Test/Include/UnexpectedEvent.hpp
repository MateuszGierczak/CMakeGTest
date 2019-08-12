#pragma once

#include "event_type_traits.hpp"

struct UnexpectedEvent
{ };

constexpr unsigned UNEXPECTED_EVENT_ID = 2u;

template<>
struct event_type_traits<UnexpectedEvent>
{
    constexpr static unsigned id = UNEXPECTED_EVENT_ID;
};