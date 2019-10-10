#pragma once

#include "event.hpp"
#include "state.hpp"

struct fsm_base
{
    virtual ~fsm_base() = default;

    virtual const char* name() const noexcept = 0;
    virtual const char* current_state_name() const noexcept = 0;

    virtual void handle_event(const event&) = 0;

    virtual void state_transition(state_base&) noexcept = 0;
};

struct fsm : fsm_base
{
    fsm(const char* name, state_base& initial_state)
        : name_{name},
          current_state_{initial_state}
    {}

    const char* name() const noexcept override
    {
        return name_;
    }

    const char* current_state_name() const noexcept override
    {
        return current_state_.name();
    }

    void state_transition(state_base& next_state) noexcept override
    {
        next_state_ = &next_state;
    }

    void handle_event(const event& e) override
    {
        const bool was_event_processed = current_state_.handle_event(e, *this);

        if(not was_event_processed)
        {
            handle_unexpected_event(e);
        }
    }

private:
    void handle_unexpected_event(const event& e)
    {
        std::cout << "Handle unexpected event with ID = " << e.id()
                  << ", in state " << current_state_name() << std::endl;
    }

    const char* name_ {};

    state_base& current_state_;
    state_base* next_state_ {};
};
