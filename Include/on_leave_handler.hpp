#pragma once

#include "handler_type.hpp"

struct on_leave_handler
{
	constexpr static handler_type type = handler_type::on_leave;
};

template<typename Function>
auto on_leave(Function)
{
	return on_leave_handler();
}