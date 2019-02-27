#include <gtest/gtest.h>

#include "state.hpp"

namespace
{
	constexpr std::string_view STATE_NAME = "TESTABLE";
}

unsigned value = 0;

struct state_test : ::testing::Test
{
	void TearDown() { value = 0; }

	static void callable() { value++; }

	state sut{ STATE_NAME,
			   &state_test::callable };
};

TEST_F(state_test, should_get_proper_state_name)
{
	ASSERT_STREQ(STATE_NAME.data(), sut.name());
}