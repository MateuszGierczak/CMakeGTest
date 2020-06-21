#pragma once

#include "event.hpp"
#include "state.hpp"

template<typename Derived>
struct fsm
{
    const char *name() const noexcept
    {
        return name_;
    }

    const char *current_state_name() const noexcept
    {
        return current_state_->name();
    }

    void state_transition(state<Derived>& next_state) noexcept
    {
        next_state_ = &next_state;
    }

    void handle_event(const event &e)
    {
        const bool was_event_processed = current_state_->handle_event(e, static_cast<Derived&>(*this));

        if (not was_event_processed)
        {
            handle_unexpected_event(e);
        }

        go_to_the_next_state();
    }

private:
    friend Derived;

    fsm(const char *name, state<Derived>& initial_state)
        : name_{name},
          current_state_{&initial_state}
    {}

    void go_to_the_next_state()
    {
        if (next_state_ != nullptr)
        {
            current_state_ = next_state_;
            next_state_ = nullptr;
        }
    }

    void handle_unexpected_event(const event &e)
    {
        std::cout << "Handle unexpected event with ID = " << e.id()
                  << ", in state " << current_state_name() << std::endl;
    }

    const char *name_{};

    state<Derived>* current_state_{};
    state<Derived>* next_state_{};
};
