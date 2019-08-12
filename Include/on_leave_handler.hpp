#pragma once

#include "handler_base.hpp"

struct on_leave_handler : handler_base<handler_type::on_leave>
{
	using FunctionType = void(*)();

	on_leave_handler(FunctionType function) 
		: function_{ function }
	{}

	void on_leave() const
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