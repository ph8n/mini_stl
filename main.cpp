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

  std::cout << arr.size() << std::endl;
  std::cout << arr.empty() << std::endl;
  std::cout << arr.begin() << std::endl;
  std::cout << arr.end() << std::endl;
  return 0;
}
