#pragma once

#include "handler_type.hpp"

template<handler_type TYPE>
struct handler_base
{
    constexpr static handler_type type = TYPE;
};