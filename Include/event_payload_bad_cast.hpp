#pragma once

#include <typeinfo>

struct event_payload_bad_cast : std::bad_cast
{};