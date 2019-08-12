#pragma once

#include <any>

#include "event_type_traits.hpp"
#include "event_payload_bad_cast.hpp"

struct event
{
	template<typename PayloadType>
	constexpr explicit event(const PayloadType& payload) 
		: id_{event_type_traits<PayloadType>::id},
		  payload_{payload}
	{}

	auto id() const noexcept
	{
		return id_;
	}

	template<typename PayloadType>
	const PayloadType& payload() const
	{
		const PayloadType* payload = std::any_cast<PayloadType>(&payload_);

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