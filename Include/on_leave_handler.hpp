#pragma once

#include "handler_type.hpp"

struct on_leave_handler
{
	constexpr static handler_type type = handler_type::on_leave;

	using FunctionType = void(*)();

	on_leave_handler(FunctionType function) 
		: function_{ function }
	{}

	void operator()()
	{
		function_();
	}
	
private:
	FunctionType function_{};
};

template<typename Function>
auto on_leave(Function function)
{
	return on_leave_handler(function);
}