#pragma once

#include <tuple>

template<typename T, typename... Ts>
struct multi_handler
{
	multi_handler(T t, Ts... ts)
		: handlers{ std::make_tuple(t, ts...) }
	{}

	void operator()()
	{
		call_handlers(handlers, std::index_sequence_for<T, Ts...>());
	}

private:

	template<typename Tuple, std::size_t... Is>
	void call_handlers(const Tuple& handlers, std::index_sequence<Is...>)
	{
		(std::get<Is>(handlers)(), ...);
	}

	std::tuple<T, Ts...> handlers{};
};