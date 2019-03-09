#pragma once

#include <tuple>

#include "handler_type.hpp"

struct event;

struct multi_handler_base
{
	virtual ~multi_handler_base() = default;

	virtual void on_entry() const = 0;
	virtual void on_leave() const = 0;
	virtual bool handle_event(const event&) const = 0;
};

template<typename Handler, typename... Handlers>
struct multi_handler : multi_handler_base
{
	multi_handler(Handler handler, Handlers... handlers)
		: handlers_{ std::make_tuple(handler, handlers...) }
	{}

	void on_entry() const override
	{
		call_on_entry_handlers(handlers_,
							   std::index_sequence_for<Handler, Handlers...>());
	}

	void on_leave() const override
	{
		call_on_leave_handlers(handlers_,
							   std::index_sequence_for<Handler, Handlers...>());
	}

	bool handle_event(const event& event) const override
	{
		bool was_event_consumed
			= call_on_event_handlers(handlers_,
									 event,
									 std::index_sequence_for<Handler, Handlers...>());
		return was_event_consumed;
	}

private:

	template<typename Tuple, std::size_t... Is>
	bool call_on_event_handlers(const Tuple& handlers,
								const event& event,
								std::index_sequence<Is...>) const
	{
		return (call_on_event_handler(std::get<Is>(handlers), event) || ...);;
	}

	template<typename Handler>
	bool call_on_event_handler(const Handler& handler, const event& event) const
	{
		if constexpr (Handler::type == handler_type::on_event)
		{
			return handler(event);
		}
		return false;
	}

	template<typename Tuple, std::size_t... Is>
	void call_on_entry_handlers(const Tuple& handlers,
								std::index_sequence<Is...>) const
	{
		(call_on_entry_handler(std::get<Is>(handlers)), ...);
	}

	template<typename Handler>
	void call_on_entry_handler(const Handler& handler) const
	{
		if constexpr (Handler::type == handler_type::on_entry)
		{
			handler();
		}
	}

	template<typename Tuple, std::size_t... Is>
	void call_on_leave_handlers(const Tuple& handlers,
								std::index_sequence<Is...>) const
	{
		(call_on_leave_handler(std::get<Is>(handlers)), ...);
	}

	template<typename Handler>
	void call_on_leave_handler(const Handler& handler) const
	{
		if constexpr (Handler::type == handler_type::on_leave)
		{
			handler();
		}
	}

	std::tuple<Handler, Handlers...> handlers_{};
};