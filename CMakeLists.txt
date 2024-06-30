cmake_minimum_required(VERSION 3.28)
project(Maman_14 C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_executable(Maman_14 main.c
        cpu.h
        assembler_main.c
        assembler_stage_0.c
        assembler_stage_0.h)
