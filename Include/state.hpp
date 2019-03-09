#pragma once

#include <string_view>

#include "multi_handler.hpp"

struct state_base
{
	virtual ~state_base() = default;

	virtual std::string_view name() const noexcept = 0;
	virtual void on_entry() const = 0;
	virtual void on_leave() const = 0;
	virtual bool handle_event(const event&) const = 0;
};

struct state : state_base
{
	template<typename Handler, typename... Handlers>
	state(std::string_view name, 
		  Handler handler,
		  Handlers... handlers) 
		: name_{ name },
		  handlers_{ std::make_unique<multi_handler<Handler, Handlers...>>(handler, handlers...) }
	{}

	std::string_view name() const noexcept override
	{
		return name_;
	}

	void on_entry() const override
	{
		handlers_->on_entry();
	}

	void on_leave() const override
	{
		handlers_->on_leave();
	}

	bool handle_event(const event& event) const override
	{
		return handlers_->handle_event(event);
	}

private:
	std::string_view name_{};
	std::unique_ptr<multi_handler_base> handlers_{};
};