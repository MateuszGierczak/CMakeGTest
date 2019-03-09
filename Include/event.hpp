#pragma once

#include <any>

struct bad_event_payload_cast
{};

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
			throw bad_event_payload_cast{};
		}
		return *payload;
	}

private:
	unsigned id_{};
	std::any payload_{};
};