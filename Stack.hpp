#ifndef STACK_HPP
#define STACK_HPP

#include <memory>

template <typename T> class Stack {
public:
  Stack();
  ~Stack();
  Stack(const Stack&);
  Stack& operator=(const Stack&);
  size_t Size() const;
  void   Push(const T&);
  T      Pop();               // if empty, throws exception
  bool   isEmpty();
private:
  std::unique_ptr<T> v_;      // ptr to a memory area big
  size_t vsize_;              //  enough for 'vsize_' T's
  size_t vused_;              // # of T's actually in use
};

#endif // STACK_HPP