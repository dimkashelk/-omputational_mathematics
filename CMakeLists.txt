cmake_minimum_required(VERSION 3.27)
project(computational_mathematics)

set(CMAKE_CXX_STANDARD 17)

add_executable(computational_mathematics
        second_lab/main.cpp
        second_lab/Decomp.cpp
        second_lab/Decomp.h
        second_lab/Solve.cpp
        second_lab/Solve.h
)
