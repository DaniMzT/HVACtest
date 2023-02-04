# Version >=3.11 of CMake for installing GoogleTest
cmake_minimum_required(VERSION 3.11-3.18)

project(tempControl)

add_library(tempControl source/tempControl.cpp)

# PUBLIC needed to make both tempControl.h and classes library available in the whole project
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Just in case, to tell the compiler to use C++20 features
target_compile_features(tempControl PUBLIC cxx_std_20)