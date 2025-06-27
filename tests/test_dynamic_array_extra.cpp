#define CATCH_CONFIG_MAIN
#include "dynamic_array.hpp"
#include <catch2/catch.hpp>
#include <stdexcept>

TEST_CASE("DynamicArray element access", "[DynamicArray]") {
  DynamicArray<int> arr;
  arr.push_back(10);
  arr.push_back(20);
  arr.push_back(30);

  SECTION("at() access") {
    REQUIRE(arr.at(0) == 10);
    REQUIRE(arr.at(1) == 20);
    REQUIRE(arr.at(2) == 30);
    REQUIRE_THROWS_AS(arr.at(3), std::out_of_range);
    REQUIRE_THROWS_AS(arr.at(-1), std::out_of_range);
  }

  SECTION("front() and back() access") {
    REQUIRE(arr.front() == 10);
    REQUIRE(arr.back() == 30);
  }

  SECTION("const access") {
    const DynamicArray<int>& const_arr = arr;
    REQUIRE(const_arr[1] == 20);
    REQUIRE(const_arr.at(1) == 20);
    REQUIRE(const_arr.front() == 10);
    REQUIRE(const_arr.back() == 30);
    REQUIRE_THROWS_AS(const_arr.at(3), std::out_of_range);
  }
}

TEST_CASE("DynamicArray capacity management", "[DynamicArray]") {
    DynamicArray<int> arr;
    REQUIRE(arr.capacity() == 0);

    arr.reserve(10);
    REQUIRE(arr.capacity() >= 10);
    REQUIRE(arr.size() == 0);

    arr.push_back(1);
    arr.push_back(2);
    size_t cap_before = arr.capacity();
    arr.reserve(5); // should not decrease capacity
    REQUIRE(arr.capacity() == cap_before);
    REQUIRE(arr.size() == 2);
    REQUIRE(arr[1] == 2);
}


TEST_CASE("DynamicArray clear", "[DynamicArray]") {
  DynamicArray<int> arr;
  arr.push_back(10);
  arr.push_back(20);
  arr.clear();
  REQUIRE(arr.empty());
  REQUIRE(arr.size() == 0);
  // Capacity is not guaranteed to be cleared
}

TEST_CASE("DynamicArray copy semantics", "[DynamicArray]") {
  DynamicArray<int> arr1;
  arr1.push_back(1);
  arr1.push_back(2);

  SECTION("Copy constructor") {
    DynamicArray<int> arr2(arr1);
    REQUIRE(arr2.size() == 2);
    REQUIRE(arr2[0] == 1);
    REQUIRE(arr2[1] == 2);

    // Check for deep copy
    arr2[0] = 5;
    REQUIRE(arr1[0] == 1);
    REQUIRE(arr2[0] == 5);
  }

  SECTION("Copy assignment operator") {
    DynamicArray<int> arr2;
    arr2.push_back(3);
    arr2 = arr1;
    REQUIRE(arr2.size() == 2);
    REQUIRE(arr2[0] == 1);
    REQUIRE(arr2[1] == 2);

    // Check for deep copy
    arr2[0] = 5;
    REQUIRE(arr1[0] == 1);
    REQUIRE(arr2[0] == 5);
  }
}

TEST_CASE("DynamicArray move semantics", "[DynamicArray]") {
  DynamicArray<int> arr1;
  arr1.push_back(1);
  arr1.push_back(2);

  SECTION("Move constructor") {
    DynamicArray<int> arr2(std::move(arr1));
    REQUIRE(arr2.size() == 2);
    REQUIRE(arr2[0] == 1);
    REQUIRE(arr2[1] == 2);
    REQUIRE(arr1.size() == 0); // Original should be empty
    REQUIRE(arr1.empty());
  }

  SECTION("Move assignment operator") {
    DynamicArray<int> arr2;
    arr2.push_back(3);
    arr2 = std::move(arr1);
    REQUIRE(arr2.size() == 2);
    REQUIRE(arr2[0] == 1);
    REQUIRE(arr2[1] == 2);
    REQUIRE(arr1.size() == 0); // Original should be empty
    REQUIRE(arr1.empty());
  }
}