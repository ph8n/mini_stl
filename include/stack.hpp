#ifndef STACK_HPP
#define STACK_HPP

#include "dynamic_array.hpp"
#include "linked_list.hpp"

template <typename T> struct Stack_DynamicArray {
private:
  DynamicArray<T> *arr;
  size_t top;

public:
  Stack_DynamicArray() : arr(new DynamicArray<T>()), top(-1) {}

  Stack_DynamicArray(int capacity) {
    arr = new DynamicArray<T>(capacity);
    top = -1;
  }

  ~Stack_DynamicArray() { delete arr; }

  void push(int value) {
    if (top + 1 >= arr->capacity) {
      arr->resize(arr->capacity * 2);
    }
    arr->data[++top] = value;
  }

  T pop() {
    if (top < 0) {
      throw std::out_of_range("Stack underflow");
    }
    return arr->data[top--];
  }

  T peek(int index) const {
    if (index < 0 || index > top) {
      throw std::out_of_range("Index out of range");
    }
    return arr->data[index];
  }

  bool empty() const { return top < 0; }

  T peek(void) const {
    if (top < 0) {
      throw std::out_of_range("Stack is empty");
    }
    return arr->data[top];
  }

  size_t size() const { return top + 1; }
};

template <typename T> struct Stack_Linked {
private:
  LinkedList<T> *list;

public:
  void push(const T value) { list->push_front(value); }
  T pop(void) { list->pop_front(); }
  T peek(void) const { list->front(); }
  bool empty(void) const { return list->empty(); }
  size_t size(void) const { return list->size(); }
};

#endif
