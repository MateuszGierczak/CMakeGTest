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
            std::invoke(function_, fsm, e.payload<PayloadType>());
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

template<typename Fsm, typename PayloadType>
auto on_event(void (Fsm::*function)(const PayloadType&))
{
    return on_event_action<PayloadType, decltype(function)>{function};
}

template<typename Fsm, typename PayloadType>
auto on_event(void (Fsm::*function)(const PayloadType&) const)
{
    return on_event_action<PayloadType, decltype(function)>{function};
}
