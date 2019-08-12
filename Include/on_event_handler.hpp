#pragma once

#include "event.hpp"
#include "handler_base.hpp"

template<typename EventPayloadType>
struct on_event_handler : handler_base<handler_type::on_event>
{
	using FunctionType = void(*)(const EventPayloadType&);

	on_event_handler(FunctionType function) 
        : function_{ function }
	{}

	bool handle_event(const event& e) const
	{
		if (event_type_traits<EventPayloadType>::id == e.id())
		{
            function_(e.payload<EventPayloadType>());
            return true;
		}
		return false;
	}

private:
	FunctionType function_{};
};

template<typename ReturnType, typename EventPayloadType>
auto on_event(ReturnType (*function)(const EventPayloadType&))
{
	return on_event_handler<EventPayloadType>(function);
}