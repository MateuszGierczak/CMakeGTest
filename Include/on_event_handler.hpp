#pragma once

#include "handler_type.hpp"
#include "event.hpp"

namespace
{
	template<unsigned ID, unsigned... IDs>
	bool has_id(unsigned id)
	{
		return id == ID || ((id == IDs) || ...);
	}
}
template<unsigned ID, unsigned... IDs>
struct on_event_handler
{
	constexpr static handler_type type = handler_type::on_event;

	using FunctionType = bool(*)(const event&);

	on_event_handler(FunctionType function) :
		function_{ function }
	{}

	bool operator()(const event& event) const
	{
		if (has_id<ID, IDs...>(event.id()))
		{
			return function_(event);
		}
		return false;
	}

private:
	FunctionType function_{};
};

template<unsigned ID, unsigned... IDs, typename Function>
auto on_event(Function function)
{
	return on_event_handler<ID, IDs...>(function);
}