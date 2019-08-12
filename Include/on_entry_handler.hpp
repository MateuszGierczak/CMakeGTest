#pragma once

#include "handler_base.hpp"

struct on_entry_handler : handler_base<handler_type::on_entry>
{
    void on_entry() const
    {}
};

template<typename Function>
auto on_entry(Function)
{
	return on_entry_handler();
}