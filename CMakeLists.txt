cmake_minimum_required(VERSION 3.13)
project(PowerHook)
set(CMAKE_VERBOSE_MAKEFILE on)

add_subdirectory(public_inc)

add_subdirectory(src)

add_subdirectory(test)