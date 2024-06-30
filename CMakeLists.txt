cmake_minimum_required(VERSION 3.27)
project(MATH)

set(CMAKE_CXX_STANDARD 20)
add_library(Function STATIC Number.h Function.cpp Function.h)
add_library(Math STATIC Math.h)
add_library(Set STATIC Set.cpp Set.h)
target_link_libraries(Math STATIC Function Set)

add_executable(test main.cpp)
target_link_libraries(test Function)
