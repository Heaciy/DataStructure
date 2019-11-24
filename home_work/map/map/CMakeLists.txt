cmake_minimum_required(VERSION 3.15)
project(map C)

set(CMAKE_C_STANDARD 99)

add_executable(map main.c BiTree.h DungeonBuilder.h BiTree.c DungeonBuilder.c)