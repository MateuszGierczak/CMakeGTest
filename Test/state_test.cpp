#include <gtest/gtest.h>

#include "DummyEvent.hpp"
#include "UnexpectedEvent.hpp"
#include "fsm.hpp"
#include "on_event_action.hpp"

class UserEquipment : public fsm
{
    void function(const DummyEvent&) noexcept {}
    void function2(const UnexpectedEvent&) {}

    static state idle;
};

state UserEquipment::idle{"Idle",
                          on_event(&UserEquipment::function),
                          on_event(&UserEquipment::function2)};

struct state_test : ::testing::Test
{
    UserEquipment fsm;
};
