cmake_minimum_required(VERSION 3.27)
project(C_Console_Template C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Console_Template main.c
        common/color.h
        common/util.c
        ui.h
        common/color.c
        ui.c)
