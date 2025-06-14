#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef>

template <typename T> struct Node {
private:
  T data;
  Node<T> *next;

public:
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
  LinkedList(T data) : head(new Node<T>(data, nullptr)) {}

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
    if (!head) {
      head = new Node<T>(data);
      return;
    }
    head = new Node<T>(data, head);
  }

  void push_back(const T &data) {
    if (!head) {
      head = new Node<T>(data);
      return;
    }
    Node<T> *curr = head;
    while (curr->next) {
      curr = curr->next;
    }
    curr->next = new Node<T>(data);
  }

  void pop_front(void) {
    if (!head) {
      return;
    }
    Node<T> *temp = head;
    head = head->next;
    delete temp;
  }

  void pop_back(void) {
    if (!head) {
      return;
    }
    if (!head->next) {
      delete head;
      head = nullptr;
      return;
    }
    Node<T> *curr = head;
    while (curr->next && curr->next->next) {
      curr = curr->next;
    }
    Node<T> *temp = curr->next;
    curr->next = nullptr;
    delete temp;
  }

  void insert_at(const size_t index, const T value) {
    if (index == 0) {
      push_front(value);
      return;
    }
    Node<T> *curr = head;
    for (size_t i = 0; curr && i < index - 1; i++) {
      curr = curr->next;
    }
    if (!curr) {
      return; // Index out of bounds
    }
    curr->next = new Node<T>(value, curr->next);
  }

  void remove_at(const size_t index) {
    if (!head)
      return;
    return;
    if (index == 0) {
      pop_front();
      return;
    }
    Node<T> *curr = head;
    for (size_t i = 0; curr->next && i < index - 1; i++) {
      curr = curr->next;
    }
    if (!curr || !curr->next) {
      return; // Index out of bounds
    }
    Node<T> *temp = curr->next;
    curr->next = temp->next;
    delete temp;
  }

  T *find(const T value) {
    if (!head) {
      return nullptr;
    }
    Node<T> *curr = head;
    while (curr) {
      if (curr->data == value) {
        return &curr->data;
      }
      curr = curr->next;
    }
    return nullptr;
  }

  T *begin(void) { return head; }

  T *end(void) { return nullptr; }

  T *cbegin(void) const { return head; }

  T *cend(void) const { return nullptr; }

  size_t size(void) const {
    size_t count = 0;
    Node<T> *curr = head;
    while (curr) {
      count++;
      curr = curr->next;
    }
    return count;
  }
};

#endif
