#include "gtest/gtest.h"
#include <type_traits>
#include "client.hpp"
#include <memory>
#include <utility>
#include <tuple>

using namespace inputs;

namespace inputs_test
{

	template <class T, size_t size>
	class ClientTest : public testing::Test
	{
	};

	using testing::Types;

	// The list of types we want to test.
	typedef Types<std::pair<int8_t, std::integral_constant<std::size_t, 16>>,
								std::pair<uint8_t, std::integral_constant<std::size_t, 24>>>
			Implementations;

	TYPED_TEST_CASE(ClientTest, Implementations);

	TYPED_TEST(ClientTest, shouldReturnSetID)
	{
		typename TypeParam::first_type data_type;
		typename TypeParam::second_type size;
		// static constexpr std::size_t n = TypeParam::value;
		EXPECT_TRUE(true);
	}

} // namespace inputs_test