#pragma once

#include "actions_chain.hpp"

struct event;

template<typename Fsm>
struct actions_chain_wrapper_base
{
    virtual ~actions_chain_wrapper_base() = default;

    virtual bool handle_event(const event& e, Fsm& fsm) = 0;
};

template<typename Fsm, typename... Actions>
struct actions_chain_wrapper : actions_chain_wrapper_base<Fsm>,
                               actions_chain<0, Actions...>
{
    actions_chain_wrapper(Actions... actions)
        : actions_chain<0, Actions...>(actions...)
    {}

    bool handle_event(const event& e, Fsm& fsm)
    {
        return actions_chain<0, Actions...>::handle_event(e, fsm);
    }
};
