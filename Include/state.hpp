#pragma once

#include <string_view>

#include "multi_handler.hpp"

struct state
{
	template<typename Handler, typename... Handlers>
	state(std::string_view name, 
		  Handler handler,
		  Handlers... handlers) 
		: name_{ name },
		  handlers_{ std::make_unique<multi_handler<Handler, Handlers...>>(handler, handlers...) }
	{}

	const char* name()
	{
		return name_.data();
	}

	void on_entry() {}
	void on_leave() {}

	bool handle_event(unsigned e) 
	{
		return handlers_->handle_event(e);
	}

private:
	std::string_view name_{};
	std::unique_ptr<multi_handler_base> handlers_{};
};