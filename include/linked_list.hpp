#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef>

template <typename T> struct Node {
private:
  T data;
  Node *next;

  Node() : data(), next(nullptr) {}
  Node(T data) : data(data), next(nullptr) {}
  Node(T data, Node *next) : data(data), next(next) {}
};

template <typename T> struct LinkedList {
private:
  Node<T> *head;

public:
  // Default constructor
  LinkedList() : head(nullptr) {}
  // Head constructor
  LinkedList(T data) : head(new Node{data, nullptr}) {}

  // Deconstructor
  ~LinkedList() {
    Node<T> *current = head;
    while (current) {
      Node<T> *next_node = current->next;
      delete current;
      current = next_node;
    }
  }

  void push_front(const T &data) {
    Node<T> *newHead = new Node<T>(data, head);
    head = newHead;
  }
  void push_back(const T &data) {
    Node<T> *current = head;
    while (current && current->next) {
      current = current->next;
    }
    current->next = new Node<T>(data);
  }
  void pop_front(void) {
    Node<T> *temp = head->next;
    delete head;
    head = temp;
  }
  void pop_back(void) {
    Node<T> *current = head;
    while (current && current->next) {
      current = current->next;
    }
    delete current;
  }
  void insert_at(size_t index, T value) {
    Node<T> *current = head;
    for (size_t i = 0; i < index - 1; ++i) {
      if (!current)
        return;
      current = current->next;
    }
    current->next = new Node<T>(value, current->next->next);
  }
  void remove_at(size_t index) {}
  T *find(T value) {}

  T *begin(void) {}
  T *end(void) {}
  T *cbegin(void) const {}
  T *cend(void) const {}
};

#endif
