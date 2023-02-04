# Version >=3.11 of CMake for installing GoogleTest
cmake_minimum_required(VERSION 3.11-3.18)

project(main)

add_executable(main main.cpp)

# tempControl.h (in classes) is required
target_link_libraries(main PRIVATE tempControl)

# Just in case, to tell the compiler to use C++20 features
target_compile_features(main PUBLIC cxx_std_20)