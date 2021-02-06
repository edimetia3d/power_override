cmake_minimum_required(VERSION 3.13)
project(PowerOverride)

execute_process(COMMAND git submodule update --init --recursive --depth 1
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}}
        )
add_subdirectory(third_party/spdlog)

add_subdirectory(public_inc)

add_subdirectory(src)

add_subdirectory(test)