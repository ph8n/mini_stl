#include "include/dynamic_array.hpp"
#include <iostream>

int main() {
  DynamicArray<int> arr(5, 10);
  for (int i = 0; i < 5; ++i) {
    arr.push_back(i);
  }
  arr.pop_back();

  for (int i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << " ";
  }
  return 0;
}
