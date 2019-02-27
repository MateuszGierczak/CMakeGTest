#pragma once

#include <tuple>

struct multi_handler_base
{
	virtual ~multi_handler_base() = default;

	virtual bool handle_event(unsigned) = 0;
};

template<typename Handler, typename... Handlers>
struct multi_handler : multi_handler_base
{
	multi_handler(Handler handler, Handlers... handlers)
		: handlers{ std::make_tuple(handler, handlers...) }
	{}

	bool handle_event(unsigned) override
	{
		return call_handlers(handlers, 
							 std::index_sequence_for<Handler, Handlers...>());
	}

private:

	template<typename Tuple, std::size_t... Is>
	bool call_handlers(const Tuple& handlers, std::index_sequence<Is...>)
	{
		(std::get<Is>(handlers)(), ...);
		return true;
	}

	std::tuple<Handler, Handlers...> handlers{};
};