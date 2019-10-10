#pragma once

#include "action.hpp"

struct event;
struct fsm_base;

template<typename Class>
struct on_unexpected_event_action
{
    bool handle_event(const event& e, fsm_base& fsm)
    {
        return true;
    }

    using FunctionType = void(Class::*)(const event&);

    FunctionType funtion_{};
};

template<unsigned Index, typename Class>
struct action<Index, on_unexpected_event_action<Class>>
{
    bool handle_event(const event& e, fsm_base& fsm)
    {
        return action_.handle_event(e, fsm);
    }

    on_unexpected_event_action<Class> action_ {};
};

template<typename Class>
auto on_unexpected_event(void (Class::*function)(const event&))
{
    return on_unexpected_event_action<Class>{function};
}
