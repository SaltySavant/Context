cmake_minimum_required(VERSION 3.24)
project(Context)

set(CMAKE_CXX_STANDARD 20)

add_executable(Context test/test.cpp src/Context.cpp src/Context.h)
