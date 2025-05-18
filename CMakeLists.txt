cmake_minimum_required(VERSION 3.30)
project(DKR)

set(CMAKE_CXX_STANDARD 20)

add_executable(DKR main.cpp
        Radiostation.h
        Radiostation.cpp)
