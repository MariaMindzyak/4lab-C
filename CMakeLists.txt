cmake_minimum_required(VERSION 3.25)
project(ab4a C)

set(CMAKE_C_STANDARD 99)

add_executable(ab4a main.c tree.c tree.h dialog.c dialog.h menu.h)
