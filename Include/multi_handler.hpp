#pragma once

#include <tuple>

struct multi_handler_base
{
	virtual ~multi_handler_base() = default;

	virtual void on_entry() const = 0;
	virtual void on_leave() const = 0;
	virtual bool handle_event(unsigned) const = 0;
};

template<typename Handler, typename... Handlers>
struct multi_handler : multi_handler_base
{
	multi_handler(Handler handler, Handlers... handlers)
		: handlers_{ std::make_tuple(handler, handlers...) }
	{}

	void on_entry() const override
	{

	}

	void on_leave() const override
	{

	}

	bool handle_event(unsigned event) const override
	{
		return call_on_event_handlers(handlers_,
									  event
									  std::index_sequence_for<Handler, Handlers...>());
	}

private:

	template<typename Tuple, std::size_t... Is>
	bool call_on_event_handlers(const Tuple& handlers, unsigned, std::index_sequence<Is...>) const
	{
		(std::get<Is>(handlers)(), ...);
		return true;
	}

	std::tuple<Handler, Handlers...> handlers_{};
};