#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <iterator>
#include <stdexcept>

template <typename T> class DynamicArray {
public:
  // Memeber Types
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using difference_type = std::ptrdiff_t;

  // Iterator
  class iterator {
  public:
    // Member Types
    using iterator_category = std::random_access_iterator_tag;
    using value_type = DynamicArray::value_type;
    using difference_type = DynamicArray::difference_type;
    using pointer = DynamicArray::pointer;
    using reference = DynamicArray::reference;

    iterator(pointer ptr) : _ptr(ptr) {}

    reference operator*() const { return *_ptr; }
    pointer operator->() { return _ptr; }

    iterator &operator++() {
      ++_ptr;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const iterator &other) const { return _ptr == other._ptr; }
    bool operator!=(const iterator &other) const { return _ptr != other._ptr; }

  private:
    pointer _ptr;
  };

  class const_iterator {
  public:
    // Member Types
    using iterator_category = std::random_access_iterator_tag;
    using value_type = DynamicArray::value_type;
    using difference_type = DynamicArray::difference_type;
    using pointer = DynamicArray::const_pointer;
    using reference = DynamicArray::const_reference;

    const_iterator(pointer ptr = nullptr);

    const_iterator(const iterator &other);

    reference operator*() const { return *_ptr; }
    pointer operator->() const { return _ptr; }

    const_iterator &operator++() {
      ++_ptr;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const const_iterator &other) const {
      return _ptr == other._ptr;
    }
    bool operator!=(const const_iterator &other) const {
      return _ptr != other._ptr;
    }

  private:
    pointer _ptr;
  };

  // three
  DynamicArray() : _data(nullptr), _size(0), _capacity(0) {}
  ~DynamicArray() {
    clear();
    ::operator delete(_data);
  }
  DynamicArray(const DynamicArray &other);
  DynamicArray(DynamicArray &&other) noexcept;
  DynamicArray &operator=(DynamicArray &&other) noexcept;
  DynamicArray &operator=(const DynamicArray &other);

  // iterators
  iterator begin() { return _data; }
  iterator end() { return _data + _size; }
  const_iterator begin() const { return _data; }
  const_iterator end() const { return _data + _size; }
  const_iterator cbegin() const { return _data; }
  const_iterator cend() const { return _data + _size; }

  // capacity
  bool empty() const { return _size == 0; }
  size_type size() const { return _size; }
  size_type capacity() const { return _capacity; }
  void reserve(size_type new_capacity) {
    if (new_capacity <= _capacity)
      return;
    reallocate(new_capacity);
  }

  // element access
  reference operator[](size_type index) { return _data[index]; }
  const_reference operator[](size_type index) const { return _data[index]; }
  reference at(size_type index) {
    if (index >= _size || index < 0) {
      throw std::out_of_range("Out of bounds");
      return;
    }
    return _data[index];
  }
  const_reference at(size_type index) const {
    if (index >= _size || index < 0) {
      throw std::out_of_range("Out of bounds");
      return;
    }
    return _data[index];
  }
  reference front() { return _data[0]; }
  const_reference front() const { return _data[0]; }
  reference back() { return _data[_size - 1]; }
  const_reference back() const { return _data[_size - 1]; }

  // modifers
  void push_back(const T &data) {
    if (_size >= _capacity) {
      size_type new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
      reallocate(new_capacity);
    }
    new (&_data[_size]) T(data);
    _size++;
  }
  void insert(const size_type index, const T &data) {
    if (_size >= _capacity) {
    }
  }
  void pop_back() {
    if (_size > 0) {
      _size--;
      _data[_size].~T();
    }
  }
  void clear() {
    for (size_type i = 0; i < _size; i++) {
      _data[i].~T();
    }
    _size = 0;
  }

private:
  T *_data;
  size_t _capacity;
  size_t _size;

  void reallocate(size_type new_capacity) {
    if (new_capacity < _size)
      return;

    pointer new_data =
        static_cast<pointer>(::operator new(new_capacity * sizeof(T)));

    for (size_type i = 0; i < _size; i++) {
      new (&new_data[i]) T(std::move(_data[i]));
      _data[i].~T();
    }

    ::operator delete(_data);

    _data = new_data;
    _capacity = new_capacity;
  }
};

#endif
