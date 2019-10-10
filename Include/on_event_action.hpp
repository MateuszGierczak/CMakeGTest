#pragma once

#include "event.hpp"
#include "action.hpp"
#include "event_type_traits.hpp"

struct fsm_base;

template<typename FsmClass>
FsmClass& get_fsm_from_base(fsm_base& fsm)
{
    static_assert(std::is_base_of_v<fsm_base, FsmClass>, "");
    return static_cast<FsmClass&>(fsm);
}

template<typename FsmClass, typename PayloadType>
struct on_event_action
{
    bool handle_event(const event& e, fsm_base& fsm)
    {
        if (event_type_traits<PayloadType>::id == e.id())
        {
            (get_fsm_from_base<FsmClass>(fsm).*function_)(e.payload<PayloadType>());
            return true;
        }
        return false;
    }

    using FunctionType = void (FsmClass::*)(const PayloadType&);

    FunctionType function_ {};
};

template<unsigned Index, typename FsmClass, typename PayloadType>
struct action<Index, on_event_action<FsmClass, PayloadType>>
{
    bool handle_event(const event& e, fsm_base& fsm)
    {
        return action_.handle_event(e, fsm);
    }

    on_event_action<FsmClass, PayloadType> action_ {};
};

template<typename FsmClass, typename PayloadType>
auto on_event(void (FsmClass::*function)(const PayloadType&))
{
    return on_event_action<FsmClass, PayloadType>{function};
}
