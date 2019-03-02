#pragma once

#include "handler_type.hpp"

struct on_event_handler
{
	constexpr static handler_type type = handler_type::on_event;

	using FunctionType = bool(*)(unsigned);

	on_event_handler(FunctionType function) :
		function_{ function }
	{}

	bool operator()(unsigned event) const
	{
		return function_(event);
	}

private:
	FunctionType function_{};
};

template<typename Function>
auto on_event(Function function)
{
	return on_event_handler(function);
}