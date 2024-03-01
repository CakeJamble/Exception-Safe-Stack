#include <gtest/gtest.h>
#include "../Stack.cpp"
#include <iostream>
#include <string.h>

TEST(DefaultCtor, BasicAssertions) {
    Stack<std::string> myStack;

    ASSERT_TRUE(myStack.isEmpty());
}
