# The Problem
1. Make `Stack` exception safe. Stack objects will always be invariant regardless of any exceptions thrown during the execution of its member functions.
2. Make `Stack` exception neutral. If exceptions are thrown, they are propagated through to the caller, who will deal with them with the benefit of context with regards to the template parameter `T`.

```cpp
template <typename T> class Stack {
public:
  Stack();
  ~Stack();
  Stack(const Stack&);
  Stack& operator=(const Stack&);
  size_t Size() const;
  void   Push(const T&);
  T      Pop();               // if empty, throws exception
private:
  T*     v_;                  // ptr to a memory area big
  size_t vsize_;              //  enough for 'vsize_' T's
  size_t vused_;              // # of T's actually in use
};
```

# Motivations
I am an undergraduate student studying Computer Science, so I learned about exception handling. It's not an overly difficult concept, that is, the fundamentals of exception handling are not difficult to read about, and then mimic to some extent.

However, I felt that my education didn't properly inform me that exception handling wasn't the end all be all of writing good code. Before reading about Exception Safety in Herb Sutter's book (see [Reading Resources](#reading-resources)), I had never even heard of the different levels of Exception Safety. 

So, heeding the call, I created this repo to thoroughly document what I learned about the concept.

## Some Personal Notes and Questions to Readers
1. Is using smart pointers cheating? This problem predates Modern C++, so I'm wondering if I am missing the point here. I'll try to focus on Exception Safety and use whatever I have to ensure strong guarantees wherever I can.

# Reading Resources
- Exception C++: 47 Engineering Puzzles, Programming Problems, and Solutions (Herb Sutter)
- Exception Handling: A False Sense of Security (Tom Cargill)
    - This article is actually a response to a 1993 article by David Reed, which you will find if you read this.
