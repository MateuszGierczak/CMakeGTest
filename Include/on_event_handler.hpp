#pragma once

#include "handler_type.hpp"

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

	using FunctionType = bool(*)(unsigned);

	on_event_handler(FunctionType function) :
		function_{ function }
	{}

	bool operator()(unsigned event) const
	{
		if (has_id<ID, IDs...>(event))
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