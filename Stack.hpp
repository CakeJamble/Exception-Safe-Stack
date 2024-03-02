#ifndef STACK_HPP
#define STACK_HPP

#include <memory>

template <typename T> struct Node {
    T data;
    std::unique_ptr<Node> next;

    Node() : next(nullptr) {}
    Node(const T& item) : data(item), next(nullptr)
    {}

    Node(T&& item) : data(std::move(item)), next(nullptr)
    {}

    ~Node(){}
};

template <typename T> class Stack {
public:
  Stack();
  ~Stack();
  Stack(const Stack&);
  Stack& operator=(const Stack& rhs);
  size_t Size() const noexcept;
  void   Push(const T&);
  T      Pop();                 // if empty, throws exception
  void   Erase();
  bool   isEmpty() noexcept;
  const Node<T>& Peek();        // if empty, throws exception
private:
  std::unique_ptr<Node<T>> v_;  // ptr to a memory area big
  size_t vsize_;                // enough for 'vsize_' T's
  size_t vused_;                // # of T's actually in use
};

#endif // STACK_HPP