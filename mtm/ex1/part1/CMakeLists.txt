cmake_minimum_required(VERSION 3.17)
project(part1 C)

set(CMAKE_C_STANDARD 99)

add_executable(part1 amount_set_str.c amount_set_str.h Tests.c Tests.h main_tests.c)

