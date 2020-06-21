#pragma once

#include <memory>

#include "actions_chain_wrapper.hpp"

struct event;

template<typename Fsm>
struct state
{
    template<typename Action, typename... Actions>
    state(const char* name, Action action, Actions... actions)
        : name_(name),
          actions_chain_(std::make_unique<actions_chain_wrapper<Fsm, Action, Actions...>>(action, actions...))
    {}

    const char* name() const noexcept
    {
        return name_;
    }

    bool handle_event(const event& e, Fsm& fsm) const
    {
        return actions_chain_->handle_event(e, fsm);
    }

private:
    const char* name_{};
    std::unique_ptr<actions_chain_wrapper_base<Fsm>> actions_chain_ {};
};
