# taken from https://google.github.io/googletest/quickstart-cmake.html.It is declared a dependency on GoogleTest which is downloaded from GitHub

cmake_minimum_required(VERSION 3.14)
project(HVAC_GTests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
#pretty much copies/downloads a different CMake project and makes it part of build
#FetchContent_ pulls the code from Google Tests’ git repo
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(HVAC_GTests HVAC_GTests.cpp)

target_link_libraries( HVAC_GTests
  tempControl
  gtest_main
)


