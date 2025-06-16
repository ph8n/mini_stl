#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <iterator>

template <typename T> struct DynamicArray {
private:
  T *_data;
  size_t _capacity;
  size_t _size;

public:
  // (1) Default Constructor
  DynamicArray() : _data(nullptr), _capacity(0), _size(0) {}
  // (2) Fill Constructor
  DynamicArray(size_t n, const T &value = T())
      : _data(new T[n]), _capacity(n), _size(n) {
    for (size_t i = 0; i < n; ++i) {
      _data[i] = value;
    }
  }
  // (3) Copy Constructor
  DynamicArray(const DynamicArray &other)
      : _data(new T[other._capacity]), _capacity(other._capacity),
        _size(other._size) {
    for (size_t i = 0; i < other._size; ++i) {
      _data[i] = other._data[i];
    }
  }

  // Deconstructor
  ~DynamicArray() { delete[] _data; }

  // Iterator
  struct Iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    Iterator(T *ptr) : current(ptr) {}

    reference operator*(void) const { return *current; }
    pointer operator->(void) const { return current; }

    Iterator &operator++(void) {
      ++current;
      return *this;
    }
    Iterator &operator--(void) {
      --current;
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp = *this;
      ++current;
      return temp;
    }

    Iterator operator--(int) {
      Iterator temp = *this;
      --current;
      return temp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.current == b.current;
    }

    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.current != b.current;
    }

  private:
    pointer current;
  };

  // Classic operators on dynamic arrays
  void push_back(const T &value) {
    if (_size == _capacity) {
      T *new_data = new T[_capacity == 0 ? 1 : _capacity * 2];
      for (size_t i = 0; i < _size; ++i) {
        new_data[i] = _data[i];
      }
      delete[] _data;
      _data = new_data;
    }
    _data[_size] = value;
    _size++;
  }

  void pop_back(void) {
    _data[_size - 1] = T();
    _size--;

    if (_size == _capacity / 2) {
      T *new_data = new T[_capacity / 2];
      for (size_t i = 0; i < _size; ++i) {
        new_data[i] = _data[i];
      }
      delete[] _data;
      _data = new_data;
      _capacity /= 2;
    }
  }

  bool empty(void) const {
    if (_size == 0) {
      return true;
    } else {
      return false;
    }
  }

  size_t size(void) const { return _size; }

  T &operator[](size_t index) { return _data[index]; }

  DynamicArray &operator=(DynamicArray &&other) noexcept {
    if (this != &other) {
      delete[] _data;
      _data = other._data;
      _capacity = other._capacity;
      _size = other._size;
      other._data = nullptr;
      other._capacity = 0;
      other._size = 0;
    }
  }

  Iterator begin() { return Iterator(_data); }
  Iterator end() { return Iterator(_data + _size); }
};

#endif
