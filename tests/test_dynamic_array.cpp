#define CATCH_CONFIG_MAIN
#include "dynamic_array.hpp"
#include <catch2/catch.hpp>

TEST_CASE("DynamicArray basic properties", "[DynamicArray]") {
  DynamicArray<int> arr;
  REQUIRE(arr.empty());
  REQUIRE(arr.size() == 0);
}

TEST_CASE("push_back and operator[]", "[DynamicArray]") {
  DynamicArray<int> arr;
  arr.push_back(10);
  REQUIRE(!arr.empty());
  REQUIRE(arr.size() == 1);
  REQUIRE(arr[0] == 10);

  for (int i = 0; i < 50; ++i)
    arr.push_back(i);
  REQUIRE(arr.size() == 51);
  REQUIRE(arr[50] == 49);
}

TEST_CASE("pop_back and shrink", "[DynamicArray]") {
  DynamicArray<int> arr;
  for (int i = 0; i < 16; ++i)
    arr.push_back(i);
  REQUIRE(arr.size() == 16);

  arr.pop_back();
  REQUIRE(arr.size() == 15);
  // capacity shrink is internal; we trust no UB
}

TEST_CASE("copy constructor", "[DynamicArray]") {
  DynamicArray<int> a;
  for (int i = 0; i < 5; ++i)
    a.push_back(i * 2);

  DynamicArray<int> b = a;
  REQUIRE(b.size() == a.size());
  for (size_t i = 0; i < b.size(); ++i)
    REQUIRE(b[i] == a[i]);
}

TEST_CASE("iterator support", "[DynamicArray]") {
  DynamicArray<int> arr;
  for (int i = 1; i <= 4; ++i)
    arr.push_back(i);

  int sum = 0;
  for (auto &v : arr)
    sum += v;
  REQUIRE(sum == 10);
}
