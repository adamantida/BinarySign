cmake_minimum_required(VERSION 3.28)
project(BinarySign)

set(CMAKE_CXX_STANDARD 20)
add_library(base64 base64.cpp)
add_executable(BinarySign main.cpp base64)
