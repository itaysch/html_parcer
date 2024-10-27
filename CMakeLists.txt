cmake_minimum_required(VERSION 3.29)
project(html_parcer C)

set(CMAKE_C_STANDARD 17)

add_executable(html_parcer
        "stack.h"
        "vector.h"
        "tree.h"
        tree.c
        main.c
        vector.c
        stack.c
)
include_directories(${PROJECT_SOURCE_DIR})