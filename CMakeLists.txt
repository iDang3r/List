cmake_minimum_required(VERSION 3.14)
project(List)

set(CMAKE_CXX_STANDARD 17)

include_directories(/Users/alex/Desktop/my_libs)

add_executable(List main.cpp my_list.h)