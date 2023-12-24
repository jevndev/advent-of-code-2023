cmake_minimum_required(VERSION 3.12)
project("Advent Of Code 2023")

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB FOLDER_GLOB LIST_DIRECTORIES true "day_*")

foreach(item ${FOLDER_GLOB})
    if(IS_DIRECTORY ${item})
        add_subdirectory(${item})
        message(ITEM=${item})
    endif()
endforeach()