#pragma once

#include "action.hpp"

struct event;

template<unsigned Index, typename Fsm>
struct action<Index, void (Fsm::*)(const event&)>
{
    bool handle_event(const event& e, Fsm& fsm)
    {
        std::invoke(function, fsm, e);
        return true;
    }

    void (Fsm::*function)(const event&) {};
};

template<unsigned Index, typename Fsm>
struct action<Index, void (Fsm::*)(const event&) const>
{
    bool handle_event(const event& e, Fsm& fsm)
    {
        std::invoke(function, fsm, e);
        return true;
    }

    void (Fsm::*function)(const event&) const {};
};

template<unsigned Index, typename Fsm>
struct action<Index, void (Fsm::*)(const event&) const noexcept>
{
    bool handle_event(const event& e, Fsm& fsm)
    {
        std::invoke(function, fsm, e);
        return true;
    }

    void (Fsm::*function)(const event&) const noexcept {};
};

template<unsigned Index, typename Fsm>
struct action<Index, void (Fsm::*)(const event&) noexcept>
{
    bool handle_event(const event& e, Fsm& fsm)
    {
        std::invoke(function, fsm, e);
        return true;
    }

    void (Fsm::*function)(const event&) noexcept {};
};