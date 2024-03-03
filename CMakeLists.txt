cmake_minimum_required(VERSION 3.27)
project(computational_mathematics)

set(CMAKE_CXX_STANDARD 17)

add_executable(computational_mathematics
        first_lab/main.cpp
        first_lab/Langrage.h
        first_lab/Langrage.cpp
        first_lab/Spline.h
        first_lab/Spline.cpp
        first_lab/Quanc8.h
        first_lab/Quanc8.cpp
)
