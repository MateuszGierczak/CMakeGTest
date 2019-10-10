#pragma once

#include "actions_chain.hpp"

struct event;
struct fsm_base;

struct actions_chain_wrapper_base
{
    virtual ~actions_chain_wrapper_base() = default;

    virtual bool handle_event(const event& e, fsm_base& fsm) = 0;
};

template<typename... Actions>
struct actions_chain_wrapper : actions_chain_wrapper_base,
                               actions_chain<0, Actions...>
{
    actions_chain_wrapper(Actions... actions)
        : actions_chain<0, Actions...>(actions...)
    {}

    bool handle_event(const event& e, fsm_base& fsm)
    {
        return actions_chain<0, Actions...>::handle_event(e, fsm);
    }
};
