cmake_minimum_required(VERSION 3.15)
project(add C)

set(CMAKE_C_STANDARD 99)

add_executable(add main.c LinkedList.h LinkedList.c)