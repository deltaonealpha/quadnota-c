cmake_minimum_required(VERSION 3.21)
project(backend C)

set(CMAKE_C_STANDARD 11)

add_executable(backend
        db.c
        test.c)
