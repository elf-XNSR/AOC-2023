cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 20)
project(AdventOfCode)

file(GLOB SOURCES
    *.hpp
    *.cpp
)

add_executable(main ${SOURCES})
