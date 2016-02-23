cmake_minimum_required(VERSION 3.3)
project(CSCI2100_PA2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES 2.19.c )
add_executable(Q3  2.19.c)
add_executable(Q2  2.16.c)
add_executable(Q1  2.3.c)

add_executable(Q3V2 Q3V2.c)
add_executable(Q3V3 Q3V3.c)