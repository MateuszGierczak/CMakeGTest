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

class UserEquipment : public fsm<UserEquipment>
{
public:
    UserEquipment(const char* name)
        : fsm(name, idle)
    {}

private:
    void function3(DummyEvent e)
    {
        std::cout << "Received dummy event" << '\n';
    }

    void function(const DummyEvent&)
    {
        std::cout << "Zlapane" << std::endl;
    }
    void function2(const UnexpectedEvent&)
    {
        std::cout << "Zlapane 2" << std::endl;
    }

    void unexpected(const event&) const
    {
        std::cout << "nieporzadane" << std::endl;
    }

    static state<UserEquipment> idle;
};

state<UserEquipment> UserEquipment::idle{"Idle",
                                         on_event(&UserEquipment::function),
                                         &UserEquipment::unexpected};

int main()
{
    UserEquipment ue ("UserEquipmentFsm");

    event e1 {UnexpectedEvent{}};
    event e2 {DummyEvent{}};

    ue.handle_event(e2);

    std::cout << ue.current_state_name() << '\n';
}
