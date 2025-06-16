#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <iterator>

template <typename T> class List {
private:
  struct Node {
    T value;
    Node *prev;
    Node *next;
  };

  Node *head;
  Node *tail;
  size_t _size;

public:
  List() : head(nullptr), tail(nullptr), _size(0) {}

  ~List() {
    Node *curr = head;
    while (curr) {
      Node *next = curr->next;
      delete curr;
      curr = next;
    }
  }

  bool empty() const { return _size == 0; }
  size_t size() const { return _size; }

  // bidirectional iterator:
  class Iterator {
    friend class List<T>;

  private:
    Node *cur;
    List *parent;

    Iterator(Node *n, List *p) : cur(n), parent(p) {}

  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    reference operator*() const { return cur->value; }
    pointer operator->() const { return &cur->value; }

    Iterator &operator++() {
      cur = cur->next;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++*this;
      return tmp;
    }

    Iterator &operator--() {
      if (cur)
        cur = cur->prev;
      else
        cur = parent->tail;
      return *this;
    }
    Iterator operator--(int) {
      Iterator tmp = *this;
      --*this;
      return tmp;
    }

    friend bool operator==(Iterator const &a, Iterator const &b) {
      return a.cur == b.cur;
    }
    friend bool operator!=(Iterator const &a, Iterator const &b) {
      return a.cur != b.cur;
    }
  };

  Iterator begin() { return Iterator(head, this); }
  Iterator end() { return Iterator(nullptr, this); }

  void push_front(const T &value) {
    Node *n = new Node{value, nullptr, head};
    if (head)
      head->prev = n;
    else
      tail = n;
    head = n;
    ++_size;
  }

  void push_back(const T &value) {
    Node *n = new Node{value, tail, nullptr};
    if (tail)
      tail->next = n;
    else
      head = n;
    tail = n;
    ++_size;
  }

  Iterator insert(Iterator pos, const T &value) {
    if (pos.cur == nullptr) {
      // insert at end
      push_back(value);
      return Iterator(tail, this);
    }
    if (pos.cur == head) {
      push_front(value);
      return Iterator(head, this);
    }
    // middle
    Node *curr = pos.cur;
    Node *n = new Node{value, curr->prev, curr};
    curr->prev->next = n;
    curr->prev = n;
    ++_size;
    return Iterator(n, this);
  }

  Iterator erase(Iterator pos) {
    Node *curr = pos.cur;
    if (!curr)
      return end(); // nothing to do on end()

    Iterator ret(curr->next, this);

    if (curr->prev)
      curr->prev->next = curr->next;
    else
      head = curr->next;

    if (curr->next)
      curr->next->prev = curr->prev;
    else
      tail = curr->prev;

    delete curr;
    --_size;
    return ret;
  }
};

#endif // LINKED_LIST_HPP
