#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template <typename T> struct DynamicArray {
private:
  T *data;
  size_t capacity;
  size_t _size;

public:
  // (1) Default Constructor
  DynamicArray() : data(nullptr), capacity(0), _size(0) {}
  // (2) Fill Constructor
  DynamicArray(size_t n, const T &value = T())
      : data(new T[n]), capacity(n), _size(n) {
    for (size_t i = 0; i < n; ++i) {
      data[i] = value;
    }
  }
  // (3) Copy Constructor
  DynamicArray(const DynamicArray &other)
      : data(new T[other.capacity]), capacity(other.capacity),
        _size(other._size) {
    for (size_t i = 0; i < other._size; ++i) {
      data[i] = other.data[i];
    }
  }

  // Deconstructor
  ~DynamicArray() { delete[] data; }

  // Classic operators on dynamic arrays
  void push_back(const T &value) {
    if (_size == capacity) {
      T *new_data = new T[capacity == 0 ? 1 : capacity * 2];
      for (size_t i = 0; i < _size; ++i) {
        new_data[i] = data[i];
      }
      delete[] data;
      data = new_data;
    }
    data[_size] = value;
    _size++;
  }

  void pop_back(void) {
    data[_size - 1] = T();
    _size--;

    if (_size == capacity / 2) {
      T *new_data = new T[capacity / 2];
      for (size_t i = 0; i < _size; ++i) {
        new_data[i] = data[i];
      }
      delete[] data;
      data = new_data;
      capacity /= 2;
    }
  }

  T at(size_t index) const {
    if (index < _size && index >= 0) {
      return data[index];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }

  bool empty(void) const {
    if (_size == 0) {
      return true;
    } else {
      return false;
    }
  }

  size_t size(void) const { return size; }

  T *begin(void) { return data; }

  T *end(void) { return data + _size; }

  const T *cbegin(void) const { return data; }

  const T *cend(void) const { return data + _size; }

  // overloaded operators
  T operator[](size_t index) const {
    if (index < _size) {
      return data[index];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }
};

#endif
