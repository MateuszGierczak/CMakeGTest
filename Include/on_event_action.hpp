#pragma once

#include <functional>

#include "event.hpp"
#include "action.hpp"
#include "event_type_traits.hpp"

template<typename PayloadType, typename FunctionType>
struct on_event_action
{
    template<typename Fsm>
    bool handle_event(const event& e, Fsm& fsm)
    {
        if (event_type_traits<PayloadType>::id == e.id())
        {
            if constexpr(std::is_member_function_pointer_v<FunctionType>)
            {
                std::invoke(function_, fsm, e.payload<PayloadType>());
            }
            else
            {
                std::invoke(function_, e.payload<PayloadType>());
            }
            return true;
        }
        return false;
    }

    FunctionType function_{};
};

template<unsigned Index, typename FunctionType, typename PayloadType>
struct action<Index, on_event_action<PayloadType, FunctionType>>
{
    template<typename Fsm>
    bool handle_event(const event& e, Fsm& fsm)
    {
        return action_.handle_event(e, fsm);
    }

    on_event_action<PayloadType, FunctionType> action_ {};
};

template<typename PayloadType, typename FunctionType>
auto on_event(FunctionType function)
{
    return on_event_action<PayloadType, FunctionType>{function};
}
