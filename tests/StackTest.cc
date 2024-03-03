#include <gtest/gtest.h>
#include "Stack.hpp"
#include <iostream>
#include <string.h>

TEST(DefaultCtor, BasicAssertions) {
    Stack<std::string> myStack;

    ASSERT_TRUE(myStack.isEmpty());
}

TEST(Size, BasicAssertions) {
    Stack<std::string> myStack;

    ASSERT_TRUE(myStack.Size() == 0);
}

TEST(Push, BasicAssertions) {
    Stack<std::string> myStack;
    
    std::string s("Push me on the stack!");
    myStack.Push(s);

    ASSERT_TRUE(myStack.Size() != 0);
}

TEST(SimplePop, BasicAssertions) {
    Stack<std::string> myStack;

    std::string s("Live fast, die young!");
    myStack.Push(s);
    std::string _ = myStack.Pop();

    ASSERT_TRUE(myStack.isEmpty());
}

TEST(PopException, BasicAssertions) {
    Stack<std::string> myStack;
    EXPECT_THROW(myStack.Pop(), std::runtime_error);
}

TEST(CpyCtor, BasicAssertions) {
    Stack<std::string> myStack;
    std::string s("Nothing in this world is original.");
    myStack.Push(s);

    Stack<std::string> yourStack(myStack);

    EXPECT_NE(&myStack, &yourStack);
}

TEST(CpyAssgn, BasicAssertions) {
    Stack<std::string> myStack;
    Stack<std::string> yourStack;

    std::string s("Hello, World!");
    myStack.Push(s);

    yourStack = myStack;

    EXPECT_NE(&myStack, &yourStack);
}