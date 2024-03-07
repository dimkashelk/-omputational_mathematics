cmake_minimum_required(VERSION 3.27)
project(third_lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(third_lab
        main.cpp
        ../common/Rkf45.cpp
        ../common/Rkf45.h
)
