cmake_minimum_required(VERSION 3.29)
project(threads-basic)

set(CMAKE_CXX_STANDARD 20)

add_executable(threads-basic
        cpp/main.cpp
        cpp/Matrix.cpp
        cpp/Matrix.h
)
