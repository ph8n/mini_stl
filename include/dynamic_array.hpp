#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <stdexcept>

template <typename T> struct DynamicArray {
private:
  T *data;
  size_t capacity;
  size_t length;

public:
  // Default Constructor
  DynamicArray() : data(nullptr), capacity(0), length(0) {}
  // Fill Constructor
  DynamicArray(size_t n, const T &value = T())
      : data(new T[n]), capacity(n), length(n) {
    for (size_t i = 0; i < n; ++i) {
      data[i] = value;
    }
  }
  // Copy Constructor
  DynamicArray(const DynamicArray &other)
      : data(new T[other.capacity]), capacity(other.capacity),
        length(other.length) {
    for (size_t i = 0; i < other.length; ++i) {
      data[i] = other.data[i];
    }
  }

  // Deconstructor
  ~DynamicArray() { delete[] data; }

  // Classic operators on dynamic arrays
  void push_back(const T &value) {
    if (length == capacity) {
      T *new_data = new T[capacity == 0 ? 1 : capacity * 2];
      for (size_t i = 0; i < length; ++i) {
        new_data[i] = data[i];
      }
      delete[] data;
      data = new_data;
    }
    data[length] = value;
    length++;
  }

  void pop_back(void) {
    data[length - 1] = T();
    length--;

    if (length == capacity / 2) {
      T *new_data = new T[capacity / 2];
      for (size_t i = 0; i < length; ++i) {
        new_data[i] = data[i];
      }
      delete[] data;
      data = new_data;
      capacity /= 2;
    }
  }

  T at(size_t index) const {
    if (index < length && index >= 0) {
      return data[index];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }

  bool empty(void) const {
    if (length == 0) {
      return true;
    } else {
      return false;
    }
  }

  size_t size(void) const { return length; }

  T *begin(void) { return data; }

  T *end(void) { return data + length; }

  const T *cbegin(void) const { return data; }

  const T *cend(void) const { return data + length; }

  // overloaded operators
  T operator[](size_t index) const {
    if (index < length) {
      return data[index];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }
};

#endif
