cmake_minimum_required(3.11)

project(Stack)

# An OBJECT-library, used only to compile common sources once
add_library( stack_ObjLib OBJECT )

#Required include search-paths
target_include_directories( stack_ObjLib
    PRIVATE "src/Stack.cpp"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include/Stack.hpp"
)
target_compile_features(
    PUBLIC  cxx_noexcept
)

#[===[ 
    N/A since we are not using any external libraries (example included for educational purposes)
    Assuming we had a CMakeLists.txt for usage of the Boost library in a directory called '~/external/'
]===]
 # target_link_libraries( stack_ObjLib PUBLIC Boost::outcome )