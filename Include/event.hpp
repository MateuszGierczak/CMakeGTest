#pragma once

#include <any>
#include "event_payload_bad_cast.hpp"

struct event
{
	template<typename PayloadType>
	constexpr event(unsigned id, const PayloadType& payload) 
		: id_{id},
		  payload_{payload}
	{}

	auto id() const noexcept
	{
		return id_;
	}

	template<typename PayloadType>
	const PayloadType& payload()
	{
		PayloadType* payload = std::any_cast<PayloadType>(&payload_);

		if (payload == nullptr)
		{
            throw event_payload_bad_cast{};
		}
		return *payload;
	}

private:
	unsigned id_{};
	std::any payload_{};
};