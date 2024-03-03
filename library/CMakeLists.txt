cmake_minimum_required(VERSION 3.14)

project(StackLibrary)

# An OBJECT-library, used only to compile common sources once
add_library(StackLibrary INTERFACE)     
target_sources( StackLibrary
    INTERFACE   "${CMAKE_CURRENT_SOURCE_DIR}/include/Stack.tpp"
    INTERFACE   "${CMAKE_CURRENT_SOURCE_DIR}/include/Stack.hpp"
)

#Required include search-paths
target_include_directories( StackLibrary
    INTERFACE  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features( StackLibrary
    INTERFACE cxx_std_14
)