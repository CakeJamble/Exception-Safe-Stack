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
:   v_(std::make_unique<Node<T>>()),
    vsize_(0),
    vused_(0)
{}

/**
 * Stack Destructor
 * Preconditions:   N/A
 * Postconditions:  N/A
*/
template <typename T>
Stack<T>::~Stack(){}


/**
 * Stack Operator= Override
 * Preconditions    : rhs is a valid Stack that is not this
 * Postconditions   : This will be a deep copy of the rhs parameter
 *              If an exception is thrown when Erase() calls Pop(),
 *              it is propogated up to the caller of operator=().
*/
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs) {
    if(this != &rhs) {
        Erase();
        v_ = std::make_unique<Node<T>>();
        Node<T>* curr = rhs.v_.get();         // Raw ptr, no ownership modeled

        for(int i = 0; i < rhs.Size(); ++i) {
            const T elem = curr->data;
            Push(elem);
            curr = curr->next.get();
        }
    }

    return *this;
}

/**
 * Stack Peek
 * Preconditions    : N/A
 * Postconditions   : Returns a raw ptr with no ownership of data at address
*/
template <typename T>
const Node<T>& Stack<T>::Peek() {
    if(!v_) {
        throw std::runtime_error("Empty Stack!!!");
    }
    return v_.get();
}

/**
 * Stack isEmpty
 * Preconditions    : N/A
 * Postconditions   : Returns true if vsize_ is 0, else false
*/
template <typename T>
bool Stack<T>::isEmpty() noexcept {
    return vsize_ == 0;
}

/**
 * Stack Size
 * Preconditions    : N/A
 * Postconditions   : Returns an int, the # of Nodes in the Stack
*/
template <typename T>
size_t Stack<T>::Size() const noexcept {
    return vsize_;
}

/**
 * Stack Push
 * Preconditions    : An item to push onto the stack
 * Postconditions   : Pushes an item onto the stack &
 *                      increments the vsize_ data member.
*/
template <typename T>
void Stack<T>::Push(const T& item) {
    auto newNode = std::make_unique<Node<T>>(item);

    if(v_) {
        newNode->next = std::move(v_);  // newNode->next assumes ownership of previously first node
    }
    v_ = std::move(newNode);            // Transfer ownership to v_
    ++vsize_;
}

/**
 * Stack Pop
 * Preconditions    : A non-empty stack
 * Postconditions   : Returns the element popped,
 *                      throws a runtime_error if empty
*/
template <typename T>
T Stack<T>::Pop() {
    if(isEmpty()) {
        throw std::runtime_error("Empty Stack!!!");
    }

    T val = v_->data;
    v_ = std::move(v_->next);   // Ownership transferred
    --vsize_;

    return val;
}

/**
 * Stack Erase
 * Preconditions    : A non-empty stack
 * Postconditions   : Results in an empty Stack,
 *                      exceptions thrown in Pop are
 *                      propogated up to the caller.
*/
template <typename T>
void Stack<T>::Erase() {
    while(!isEmpty()) {
        T _ = Pop();
    }
}
