#include <iostream>

#include "event_type_traits.hpp"
#include "fsm.hpp"
#include "on_event_action.hpp"
#include "on_unexpected_event_action.hpp"

struct DummyEvent
{
    unsigned value{};
};

template<>
struct event_type_traits<DummyEvent>
{
    constexpr static unsigned id = 1u;
    constexpr static const char* name = "DummyEvent";
};

struct UnexpectedEvent
{ };

template<>
struct event_type_traits<UnexpectedEvent>
{
    constexpr static unsigned id = 2u;
    constexpr static const char* name = "UnexpectedEvent";
};

class UserEquipment : public fsm
{
public:
    UserEquipment(const char* name)
        : fsm(name, idle)
    {}

private:
    void function(const DummyEvent&) noexcept
    {
        std::cout << "Zlapane" << std::endl;
    }
    void function2(const UnexpectedEvent&)
    {
        std::cout << "Zlapane 2" << std::endl;
    }

    void unexpected(const event&)
    {
        std::cout << "nieporzadane" << std::endl;
    }

    static state idle;
};

state UserEquipment::idle{"Idle",
                          on_event(&UserEquipment::function)};

int main()
{
    UserEquipment ue ("UserEquipmentFsm");

    event e {UnexpectedEvent{}};

    ue.handle_event(e);
}
