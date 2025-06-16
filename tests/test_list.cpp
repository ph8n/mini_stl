#define CATCH_CONFIG_MAIN
#include "list.hpp"
#include <catch2/catch.hpp>
#include <iterator>
#include <vector>

TEST_CASE("List basic properties", "[List]") {
  List<int> lst;
  REQUIRE(lst.empty());
  REQUIRE(lst.size() == 0);
}

TEST_CASE("push_back and iteration", "[List]") {
  List<int> lst;
  for (int i = 1; i <= 5; ++i)
    lst.push_back(i);
  REQUIRE(!lst.empty());
  REQUIRE(lst.size() == 5);

  std::vector<int> vals;
  for (auto &v : lst)
    vals.push_back(v);

  std::vector<int> expect = {1, 2, 3, 4, 5};
  REQUIRE(vals == expect);
}

TEST_CASE("push_front and iteration", "[List]") {
  List<int> lst;
  for (int i = 1; i <= 5; ++i)
    lst.push_front(i);
  REQUIRE(lst.size() == 5);

  std::vector<int> vals;
  for (auto &v : lst)
    vals.push_back(v);

  std::vector<int> expect = {5, 4, 3, 2, 1};
  REQUIRE(vals == expect);
}

TEST_CASE("insert at position", "[List]") {
  List<int> lst;
  lst.push_back(1);
  lst.push_back(3);
  auto it = std::next(lst.begin()); // points at '3'
  auto new_it = lst.insert(it, 2);  // insert '2' before '3'
  REQUIRE(*new_it == 2);
  REQUIRE(lst.size() == 3);

  std::vector<int> vals;
  for (auto &v : lst)
    vals.push_back(v);
  std::vector<int> expect = {1, 2, 3};
  REQUIRE(vals == expect);
}

TEST_CASE("erase elements", "[List]") {
  List<int> lst;
  for (int i = 1; i <= 4; ++i)
    lst.push_back(i); // [1,2,3,4]

  // erase head
  lst.erase(lst.begin()); // [2,3,4]

  // erase middle (element '3')
  auto it = std::next(lst.begin());
  lst.erase(it); // [2,4]

  // erase tail
  it = std::prev(lst.end());
  lst.erase(it); // [2]

  REQUIRE(lst.size() == 1);
  REQUIRE(*lst.begin() == 2);
}

TEST_CASE("bidirectional iterator operations", "[List]") {
  List<int> lst;
  for (int v : {10, 20, 30})
    lst.push_back(v);

  auto it = lst.end();
  --it;
  REQUIRE(*it == 30);
  --it;
  REQUIRE(*it == 20);
  ++it;
  REQUIRE(*it == 30);
}
