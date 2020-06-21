#pragma once

#include <functional>

#include "event.hpp"
#include "action.hpp"
#include "action_tag.hpp"
#include "event_type_traits.hpp"

namespace
{
    template<typename Payload, typename Function, typename Fsm>
    bool invoke_function_for_payload(Function function, Fsm& fsm, const event& e)
    {
        if(event_type_traits<Payload>::id == e.id())
        {
            std::invoke(function, fsm, e.payload<Payload>());
            return true;
        }
        return false;
    }
}

template<typename Function>
struct on_event_action;

template<typename Payload, typename Fsm>
struct on_event_action<void (Fsm::*)(const Payload&)>
{
    bool handle_event(const event& e, Fsm& fsm)
    {
        return invoke_function_for_payload<Payload>(function_, fsm, e);
    }

    void (Fsm::*function_)(const Payload&) {};
};

template<typename Payload, typename Fsm>
struct on_event_action<void (Fsm::*)(const Payload&) const>
{
    bool handle_event(const event& e, Fsm& fsm)
    {
        return invoke_function_for_payload<Payload>(function_, fsm, e);
    }

    void (Fsm::*function_)(const Payload&) const {}; 
};

template<typename Payload, typename Fsm>
struct on_event_action<void (Fsm::*)(const Payload&) const noexcept>
{
    bool handle_event(const event& e, Fsm& fsm)
    {
        return invoke_function_for_payload<Payload>(function_, fsm, e);
    }

    void (Fsm::*function_)(const Payload&) const noexcept {}; 
};

template<typename Payload, typename Fsm>
struct on_event_action<void (Fsm::*)(const Payload&) noexcept>
{
    bool handle_event(const event& e, Fsm& fsm)
    {
        return invoke_function_for_payload<Payload>(function_, fsm, e);
    }

    void (Fsm::*function_)(const Payload&) noexcept {}; 
};

template<unsigned Index, typename Function>
struct action<Index, on_event_action<Function>>
{
    constexpr static action_tag tag = action_tag::on_event;

    template<typename Fsm>
    bool handle_event(const event& e, Fsm& fsm)
    {
        return action_.handle_event(e, fsm);
    }

    on_event_action<Function> action_ {};
};

template<typename Function>
auto on_event(Function function)
{
    return on_event_action<Function>{function};
}
