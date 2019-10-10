#pragma once

#include <memory>

#include "actions_chain_wrapper.hpp"

struct event;
struct fsm_base;

struct state_base
{
    virtual ~state_base() = default;

    virtual const char* name() const noexcept = 0;
    virtual bool handle_event(const event&, fsm_base&) const = 0;
};

struct state : state_base
{
    template<typename Action, typename... Actions>
    state(const char* name, Action action, Actions... actions)
        : name_(name),
          actions_chain_(std::make_unique<actions_chain_wrapper<Action, Actions...>>(action, actions...))
    {}

    const char* name() const noexcept override
    {
        return name_;
    }

    bool handle_event(const event& e, fsm_base& fsm) const override
    {
        return actions_chain_->handle_event(e, fsm);
    }

private:
    const char* name_{};
    std::unique_ptr<actions_chain_wrapper_base> actions_chain_ {};
};
