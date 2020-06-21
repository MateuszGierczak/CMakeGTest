#pragma once

#include <typeinfo>

template<typename PayloadType>
struct event_payload_bad_cast : std::bad_cast
{
    const char* what() const noexcept
    {
        return message_.c_str();
    }

private:
    std::string message_ {std::string("Trying to cast event payload to wrong type ") +
                          std::string(event_type_traits<PayloadType>::name)};
};
