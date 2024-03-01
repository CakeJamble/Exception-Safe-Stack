#include "Stack.hpp"

/**
 * Stack Constructor
 * Preconditions:   N/A
 * Postconditions:  Creates a valid stack with the following member variables:
 *      v_      : Allocates memory on free store
 *      vsize_  : Size of space allocated
 *      vused_  : # of T's actually in use
*/
template <typename T>
Stack<T>::Stack()
:   v_(std::make_unique<T>()),
    vsize_(0),
    vused_(0)
{}

/**
 * Stack Constructor
 * Preconditions:   N/A
 * Postconditions:  Creates a valid stack with the following member variables:
 *      v_      : Allocates memory on free store
 *      vsize_  : Size of space allocated
 *      vused_  : # of T's actually in use
*/
template <typename T>
Stack<T>::~Stack(){}

template <typename T>
bool Stack<T>::isEmpty() {
    return vsize_ == 0;
}

template <typename T>
size_t Stack<T>::Size() const {
    return vsize_;
}