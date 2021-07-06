#include "gtest/gtest.h"
#include "client/Client.hpp"
#include <memory>
#include <utility>
#include <tuple>
#include <experimental/array>

using namespace inputs;

namespace inputs_test {

template <typename Tup>
class ClientTest : public testing::Test {
  using T = typename std::tuple_element_t<0, Tup>;
  static constexpr std::size_t size = std::tuple_element_t<1, Tup>::value;
  using ClientT = typename Client<T, size>::ClientT;  // ClientT = std::array<T, size>

 protected:
  ClientTest() : id(ClientT{1}), client(std::make_unique<Client<T, size>>(id)) {}
  ~ClientTest() override {}

  void setClient(const ClientT& id) { client.reset(new Client<T, size>(id)); }

  ClientT id;
  std::unique_ptr<Client<T, size>> client;
};

typedef testing::Types<std::tuple<std::int8_t, std::integral_constant<std::size_t, 16>>,
                       std::tuple<std::uint8_t, std::integral_constant<std::size_t, 24>>>
    Implementations;

TYPED_TEST_CASE(ClientTest, Implementations);

TYPED_TEST(ClientTest, ShouldEqualToConstructorID) {
  EXPECT_EQ(this->client->getID(), this->id);
}

TYPED_TEST(ClientTest, ReturnTrueForConstructorID) {
  EXPECT_TRUE(this->client->isID(this->id));
}

TYPED_TEST(ClientTest, ReturnTrueForSameClientID) {
  using dataType = typename std::tuple_element<0, decltype(TypeParam())>::type;
  static constexpr std::size_t size = std::tuple_element_t<1, decltype(TypeParam())>::value;
  using ClientT = typename Client<dataType, size>::ClientT;  // std::array

  ClientT new_id{15};
  this->setClient(new_id);
  EXPECT_EQ(this->client->getID(), new_id);
  EXPECT_TRUE(this->client->isID(new_id));
}

TYPED_TEST(ClientTest, ReturnTrueForSameClient) {
  using dataType = typename std::tuple_element<0, decltype(TypeParam())>::type;
  static constexpr std::size_t size = std::tuple_element_t<1, decltype(TypeParam())>::value;
  using ClientT = typename Client<dataType, size>::ClientT;  // std::array

  ClientT new_id{15};
  Client<dataType, size> new_client(new_id);
  this->setClient(new_id);

  EXPECT_TRUE(*(this->client) == new_client);
}

}  // namespace inputs_test
