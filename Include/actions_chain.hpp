#pragma once

#include "action.hpp"

struct event;

template <unsigned Index, typename Action, typename... Actions>
struct actions_chain : action<Index, Action>,
                       actions_chain<Index + 1, Actions...>
{
    using this_action = action<Index, Action>;
    using next_action = actions_chain<Index + 1, Actions...>;

    actions_chain(Action action, Actions... actions)
        : action<Index, Action>{action},
          actions_chain<Index + 1, Actions...>{actions...}
    {}

    template<typename Fsm>
    bool handle_event(const event &e, Fsm &fsm)
    {
        return this_action::handle_event(e, fsm) ||
               next_action::handle_event(e, fsm);
    }
};

template <unsigned Index, typename Action>
struct actions_chain<Index, Action> : action<Index, Action>
{
    using this_action = action<Index, Action>;

    actions_chain(Action action)
        : action<Index, Action>{action}
    {}

    template<typename Fsm>
    bool handle_event(const event &e, Fsm &fsm)
    {
        return this_action::handle_event(e, fsm);
    }
};
