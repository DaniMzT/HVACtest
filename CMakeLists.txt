# version >=3.11 of CMake needed for installing GoogleTest
cmake_minimum_required(VERSION 3.11-3.18)

project(HVAC VERSION 0.1)

add_subdirectory(tempControl)   # look in classes subdirectory
add_subdirectory(apps)    # look in apps subdirectory