#pragma once

#include <array>
namespace inputs {

template <typename T, size_t size>
class IClient {
 public:
  using ClientType = std::array<T, size>;
  virtual const ClientType& getID() const = 0;
  virtual bool isID(const ClientType& anotherID) const = 0;
};

template <typename T, size_t size>
class Client : public IClient<T, size> {
 public:
  using ClientT = std::array<T, size>;

  Client(const ClientT& ID) : ID(ID) {}
  Client(const ClientT&& ID) : ID(std::move(ID)) {}

  inline const ClientT& getID() const override { return ID; }
  inline bool isID(const ClientT& anotherID) const override { return ID == anotherID; }

  inline bool operator==(const Client& anotherClient) { return ID == anotherClient.getID(); }

 private:
  ClientT ID;
};

}  // namespace inputs
