# version >=3.11 of CMake needed for installing GoogleTest
cmake_minimum_required(VERSION 3.11-3.18)

project(HVAC VERSION 0.1)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

enable_testing() #it tells CMake to generate the tests that we will later on create

include_directories(tempControl) #without this, tests will not be able to find the header files

add_subdirectory(tempControl)   # look in classes subdirectory
add_subdirectory(apps)    # look in apps subdirectory
add_subdirectory(GoogleTests)