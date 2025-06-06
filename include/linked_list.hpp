#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef>

template <typename T> struct LinkedList {
private:
  struct Node {
    T data;
    Node *next;
  };

  Node *head;
  size_t size;

public:
  // Default constructor
  LinkedList() : head(nullptr), size(0) {}
  // Head constructor
  LinkedList(T data) : head(new Node{data, nullptr}), size(1) {}

  void push_front(const T &data) {}
  void push_back(const T &data) {}
  void pop_front(void) {}
  void pop_back(void) {}
};

#endif
