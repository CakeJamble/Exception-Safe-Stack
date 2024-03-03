cmake_minimum_required(3.11)

project(Stack)

# An OBJECT-library, used only to compile common sources once
add_library(stack_ObjLib OBJECT 
            DESCRIPTION "Internal Stack Library" )
target_sources( stack_ObjLib
    PRIVATE "src/Stack.cpp"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include/Stack.hpp"
)

#Required include search-paths
target_include_directories( stack_ObjLib
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features(
    PUBLIC  cxx_noexcept
)