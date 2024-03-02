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

# Get the Code
## Requirements: 
- C++14 required by GoogleTest
- [Cmake](https://cmake.org/)

## Running The Program
Here is a very basic, inefficient way to get it running ASAP ([source](http://google.github.io/googletest/quickstart-cmake.html)):
1. Clone this repository: `git clone https://github.com/campjake/Exception-Safe-Stack`
2. Build the project from the top level of the repository: `cmake -S . -B build`
    - You only need to do this once
3. Build targets for tests located in `tests/`: `cmake --build build`
    - You can do a partial build instead if you write new components.
4. Run the tests: `cd build && ctest`

# My Motivations
I am an undergraduate student studying Computer Science, so I learned about exception handling. It's not an overly difficult concept, that is, the fundamentals of exception handling are not difficult to read about, and then mimic to some extent.

However, I felt that my education didn't properly inform me that exception handling wasn't the end all be all of the topic. Before reading about Exception Safety in Herb Sutter's book (see [Reading Resources](#reading-resources)), I had never even heard of the different levels of Exception Safety. 

So, heeding the call, I created this repo to thoroughly document what I learned about the concept.

## Some Personal Notes and Questions to Readers
1. Is using smart pointers cheating? This problem predates Modern C++, so I'm wondering if I am missing the point here. I'll try to focus on Exception Safety and use whatever I have to ensure strong guarantees wherever I can. It was a great exercise for familiarizing myself with smart pointers more, and I think Modern C++ made this significantly easier.
2. Whenever you think you're safe, const qualifiers are waiting to drag you down to hell. I'm glad I wrote tests before writing source code.
3. This wasn't that different from a normal homework assignment on writing a stack class, but the perspective shift to focus on exception safety still helped me learn some things.
4. The logic behind `vsize_` and `vused_` didn't make sense until I checked Herb Sutter's solution. He used an array, and I used a Linked List. So whenever `vused_` was equal to `vsize_` a new array needed to be dynamically allocated, the elements needed to be copied (or moved) to the new array, and the old array needed to be deallocated. Move semantics helped out a lot here, and yes, this puzzle predates that, too. My result thus simulates some kind of weird amalgamation of a super limited free store. Had I understood sooner, I wouldn't have even used both variables, but I leave it for you, the reader, to learn from.

# Evaluation and Discussion
Is it Exception Safe and Exception Neutral? Yes. I inadvertently simplified the challenge further than expected by implementing this as a linked list, and using smart pointers, but I believe I passed the minimum threshold for this challenge. I have some more thoughts detailed in the following subsections.

## Default Construction
The default constructor doesn't actually allocate any memory, so we don't need to worry about an `std::bad_alloc` being thrown here. In fact, the default constructor for an `std::unique_ptr` is `noexcept`, so it will call `std::terminate` if an exception gets thrown here, somehow. 

## Copy Construction & Copy Assignment
Smart pointers really did some heavy lifting here. I immediately reached for `std::unique_ptr` because of this note from cppreference:
> `std::unique_ptr` is commonly used to manage the lifetime of objects, including:
> - providing exception safety to classes and functions that handle objects with dynamic lifetime, by guaranteeing deletion on both normal exit and exit through exception.

Why does it matter? You'll notice there are no explicit deallocations made in the functions `Erase()` or `Pop()`. It was easy to write, and (hopefully) it's easy to read. Thank you smart pointers!

You might be thinking, "Okay tough guy... you might be using smart pointers, but that doesn't mean you won't throw an exception!"

And you're right, but it's still Exception Safe and Exception Neutral. If an `std::bad_alloc` is thrown, it gets propogated up the call stack to the calling function. Objects in the current scope are destroyed, including our size counter, and any `std::unique_ptr`hanging around pointing to the free store will deallocate the memory. As Herb Sutter said, 
> "All that's left is raw memory, smoke, and ashes."

## Size
C'mon, you know that size_t is an alias for an unsigned integral, right? Those aren't classes, so they don't have member functions that could throw. I decided to tack on `noexcept`, please inform me if I have some unearned hubris here.

## Push & Pop
Once again, smart pointers to the rescue. Studying them saved me a lot of time here. Had I opted for a solution with an array, I think I would have required more work with some assertions and dynamic allocation and moving of resources. 

## Retrospective & Key Takeaways
My solution and the books solution are very different, and it highlights the importance of learning C++. It is an evolving language, and taking advantage of new mechanics can lead to cleaner code. Using `std::unique_ptr` eliminated most of the traps
set by the author, and the few that remained are commonly taught as bad practice (seriously, don't throw exceptions in a destructor. You should always guarantee that you can deallocate dynamic allocations of memory).

The repository probably wouldn't meet the minimum requirements of a robust testing environment. I'd change that, and I'd also try and rewrite this with a pImpl interface. If I ever come back to this, that will be the roadmap!

# Reading Resources
- Exceptional C++: 47 Engineering Puzzles, Programming Problems, and Solutions (Herb Sutter)
- Exception Handling: A False Sense of Security (Tom Cargill)
    - This article is actually a response to a 1993 article by David Reed, which you will find if you read this.

Thank you to Dr. Ray Klefstad for recommending me the book by Herb Sutter!
