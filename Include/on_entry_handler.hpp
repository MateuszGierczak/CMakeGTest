#pragma once

#include "handler_type.hpp"

struct on_entry_handler
{
	constexpr static handler_type type = handler_type::on_entry;
};

template<typename Function>
auto on_entry(Function)
{
	return on_entry_handler();
}